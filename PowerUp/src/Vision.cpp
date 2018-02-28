/*
 * Vision.cpp
 *
 *  Created on: Feb 27, 2018
 *      Author: ryan
 */

#include "Vision.h"
#include "Robot.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

volatile bool vtLookForLights = true;
volatile bool vtLookForBlue = true;

volatile bool vtFound = false;
volatile double vtOffsetX = 0;
volatile double vtOffsetY = 0;
volatile bool vtMostIsBlue = true;

void VisionThread() {
	cs::UsbCamera camera1 = CameraServer::GetInstance()->StartAutomaticCapture(1);
	if (!camera1.IsConnected()) {
		CameraServer::GetInstance()->RemoveCamera(camera1.GetName());
	}
	else {
		cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo(camera1);
		cs::CvSource outputStreamStd = CameraServer::GetInstance()->PutVideo("Autonomous Cam", 640, 480);

		system("v4l2-ctl -d 1 -c white_balance_temperature_auto=0");

		cv::Mat source = cv::Mat(160, 120, CV_8UC3);
		cv::Mat output = cv::Mat(160, 120, CV_8UC3);
		cv::Mat temp = cv::Mat(160, 120, CV_8UC3);

		while (true) {
			if (vtLookForLights) {
				system("v4l2-ctl -d 1 -c exposure_auto=1,exposure_absolute=0");
			}
			while (vtLookForLights) {
	//			printf("ultrasonic: %f gimbal: %i\n", Robot::ultrasonicSensor->GetRangeInFeet(), Robot::gimbal->GetPan());
	//			fflush(stdout);

				cvSink.GrabFrame(source);

				cv::cvtColor(source, output, CV_BGR2GRAY);
				cv::cvtColor(output, output, CV_GRAY2BGR);

				cv::blur(source, temp, cv::Size(5, 5));

				cv::cvtColor(temp, temp, CV_BGR2HLS);

				cv::Mat hlsChannels[3];
				cv::split(temp, hlsChannels);

				cv::threshold(hlsChannels[1], hlsChannels[1], 225, 255, 0);

				std::vector<std::vector<cv::Point>> contours;
				cv::findContours(hlsChannels[1], contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

				if (contours.size() > 0) {
					double totalBlue = 0;
					double totalRed = 0;

					double sizes[contours.size()];
					cv::Point centers[contours.size()];

					int mostLeft = -1;
					int mostRight = -1;

					for (unsigned int i = 0; i < contours.size(); i++) {
						cv::Moments moments = cv::moments(contours[i]);

						if (moments.m00 > 1) {
							sizes[i] = moments.m00;
							centers[i] = cv::Point(moments.m10/moments.m00, moments.m01/moments.m00);

							int hue, sat;
							if (contours[i][0].x != 0 && contours[i][0].y != 0) {
								hue = hlsChannels[0].at<uchar>(contours[i][0].y, contours[i][0].x);
								sat = hlsChannels[2].at<uchar>(contours[i][0].y, contours[i][0].x);
							}
							else {
								hue = hlsChannels[0].at<uchar>(contours[i][1].y, contours[i][1].x);
								sat = hlsChannels[2].at<uchar>(contours[i][1].y, contours[i][1].x);
							}

							// blue
							if (vtLookForBlue && hue > 70 && hue < 130 && sat > 150) {
								totalBlue += moments.m00;

								if (mostLeft == -1 && mostRight == -1) {
									mostLeft = i;
									mostRight = i;
								}
								else if (centers[i].x < centers[mostLeft].x) {
									mostLeft = i;
								}
								else if (centers[i].x > centers[mostRight].x) {
									mostRight = i;
								}

								cv::drawContours(output, contours, i, cv::Scalar(255, 0, 0), 1);
							}
							// red
							else if (!vtLookForBlue && (hue > 155 || hue < 35) && sat > 150) {
								totalRed += moments.m00;

								if (mostLeft == -1 && mostRight == -1) {
									mostLeft = i;
									mostRight = i;
								}
								else if (centers[i].x < centers[mostLeft].x) {
									mostLeft = i;
								}
								else if (centers[i].x > centers[mostRight].x) {
									mostRight = i;
								}

								cv::drawContours(output, contours, i, cv::Scalar(0, 0, 255), 1);
							}
						}
					}

					vtFound = true;
					vtOffsetX = ((float)(centers[mostLeft].x + centers[mostRight].x) / 2 - source.cols) / (float)(source.cols * 0.5);
					vtOffsetY = ((float)(centers[mostLeft].y + centers[mostRight].y) / 2 - source.rows) / (float)(source.rows * 0.5);
					vtMostIsBlue = (totalBlue > totalRed) ? true : false;

					cv::line(output, centers[mostLeft], centers[mostRight], cv::Scalar(0, 255, 0), 2);
				}
				else {
					vtFound = false;
				}

				outputStreamStd.PutFrame(output);
			}



			if (!vtLookForLights) {
				system("v4l2-ctl -d 1 -c exposure_auto=3");
			}
			while (!vtLookForLights) {
				cvSink.GrabFrame(source);

				cv::cvtColor(source, output, CV_BGR2GRAY);
				cv::cvtColor(output, output, CV_GRAY2BGR);

				cv::blur(source, temp, cv::Size(5, 5));

				cv::cvtColor(temp, temp, CV_BGR2HSV);

				cv::Mat hsvChannels[3];
				cv::split(temp, hsvChannels);

				cv::inRange(hsvChannels[0], 15, 40, hsvChannels[0]);
				cv::threshold(hsvChannels[1], hsvChannels[1], 170, 255, CV_THRESH_BINARY_INV);
				cv::threshold(hsvChannels[2], hsvChannels[2], 160, 255, CV_THRESH_BINARY_INV);

				temp = hsvChannels[0] - hsvChannels[1] - hsvChannels[2];

				cv::erode(temp, temp, cv::Mat(), cv::Point(-1, -1), 3);
				cv::dilate(temp, temp, cv::Mat(), cv::Point(-1, -1), 6);

				std::vector<std::vector<cv::Point>> contours;
				cv::findContours(temp, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

				if (contours.size() > 0) {
					int largest = 0;
					double mass = 0;
					cv::Point center;

					for (unsigned int i = 0; i < contours.size(); i++) {
						cv::Moments moments = cv::moments(contours[i]);

						if (moments.m00 > mass) {
							largest = i;
							mass = moments.m00;
							center = cv::Point(moments.m10/moments.m00, moments.m01/moments.m00);
						}

						cv::drawContours(output, contours, i, cv::Scalar(0, 0, 100), 1);
					}

					if (mass > 500) {
						vtFound = true;
						vtOffsetX = (float)(center.x - source.cols) / (float)(source.cols * 0.5);
						vtOffsetY = (float)(center.y - source.rows) / (float)(source.rows * 0.5);
					}
					else {
						vtFound = false;
					}
					cv::drawContours(output, contours, largest, cv::Scalar(0, 0, 255), 1);
				}
				else {
					vtFound = false;
				}

				outputStreamStd.PutFrame(output);
			}
		}
	}
}
