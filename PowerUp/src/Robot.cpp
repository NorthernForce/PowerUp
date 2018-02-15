// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"

#include "WPILib.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

volatile float visionAngle = 0;
volatile float visionMovement = 0;

#include "Subsystems/Ultrasonic.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<DriveTrain> Robot::driveTrain;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

// TODO: the reflective tape appears very green, so take advantage
//       of that vs the blue and red lights.
static void VisionThread()
    {
		UltrasonicSensor* ultra = new UltrasonicSensor(0, 0, 0);

        cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();

        // some notes on changing camera settings:
        //    - UsbCamera class methods (SetExposureManual()...) do not seem to work
        //    - this url, http://172.22.11.2:1181/, has a great list of settings that work from that url
        //    - v4l-utils must be installed (opkg install v4l-utils)
        //    - run v4l2-ctl -L to check current values, ranges, defaults, etc
        //    - the lifecam exposure settings range from 5 to 20,000 but only allow some random numbers in between
        system("v4l2-ctl -c exposure_auto=1");
        system("v4l2-ctl -c exposure_absolute=39");

        cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
        cs::CvSource outputStreamStd = CameraServer::GetInstance()->PutVideo("Reflective Tape", 640, 480);

        cv::Mat source;
        cv::Mat output;
        while (true) {
            cvSink.GrabFrame(source);
            output = source;

            cv::Mat channels[3];
            cv::split(source, channels);

            output = channels[1];

			cv::threshold(output, output, 235, 255, 0);

			std::vector<std::vector<cv::Point> > contours;
			cv::findContours(output, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

			output = source;

			if (contours.size() > 0) {
				// gets the largest contour (and the moments)
				std::vector<cv::Moments> moments(contours.size());
				int j = 0;
				for (unsigned int i = 0; i < contours.size(); i++) {
					moments[i] = cv::moments(contours[i]);

					if (moments[i].m00 > moments[j].m00) {
						j = i;
					}
				}

				// only continue if the largest contour is large
				if (moments[j].m00 > source.cols*source.rows/72) {
					cv::drawContours(output, contours, j, cv::Scalar(0, 0, 255), 1);

					cv::Point center = cv::Point(moments[j].m10/moments[j].m00, moments[j].m01/moments[j].m00);
					cv::circle(output, center, 2, cv::Scalar(255, 0, 0), 1);

					// this may not be needed ... not used for anything
					// NOTE: maybe use the aspect ratio of the sides to determine the angle.
					cv::Rect rect = cv::boundingRect(contours[j]);
					cv::rectangle(output, cv::Point(rect.x, rect.y), cv::Point(rect.x+rect.width, rect.y+rect.height), cv::Scalar(0, 255, 0), 1);

					// calculating the angle
					visionAngle = (float)(center.x-source.cols/2)/(float)(source.cols*1.25);
					// creates a y-intercept (the robot doesn't really move at 0.2)
					if (visionAngle > 0) {
						visionAngle += 0.35;
					}
					else if (visionAngle < 0) {
						visionAngle -= 0.35;
					}

					// calculating the movement
					if (visionAngle > -0.45 && visionAngle < 0.45) {
						double distance = ultra->GetRangeInFeet();
						if (distance > 4) {
							visionMovement = distance*-0.1-0.2;
							if (visionMovement < -0.55) {
								visionMovement = -0.55;
							}
						}
						else if (distance < 2) {
							visionMovement = 0.5;
						}
						else {
							visionMovement = 0;
						}
					}
					// this means we must turn first, but there is a target spotted
					else {
						visionMovement = 0;
					}
				}
				// if there are no large contours
				else {
					visionAngle = 0;
					visionMovement = 0;
				}
			}
			// if no contours at all
			else {
				visionAngle = 0;
				visionMovement = 0;
			}

			printf("visionAngle: %f visionMovement: %f\n", visionAngle, visionMovement);
			fflush(stdout);

			// this will be dark(ish) ... maybe increase brightness?
            outputStreamStd.PutFrame(output);
        }
    }


void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    driveTrain.reset(new DriveTrain());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	// Add commands to Autonomous Sendable Chooser
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

	CameraServer::GetInstance()->StartAutomaticCapture();
	chooser.AddDefault("Autonomous Command", new AutonomousCommand());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	frc::SmartDashboard::PutData("Auto Modes", &chooser);

	std::thread visionThread(VisionThread);
	visionThread.detach();
}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	autonomousCommand = chooser.GetSelected();
	if (autonomousCommand != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
	const auto& joystick = oi->getDriverJoystick();
//	RobotMap::driveTrainRobotDrive->ArcadeDrive(joystick->GetX(), joystick->GetY(), true);

//	printf("joystick: %f\n", joystick->GetX());

//	if (joystick->GetY() > 0.5) {
		RobotMap::driveTrainRobotDrive->ArcadeDrive(visionAngle, visionMovement, true);
//	}
}

START_ROBOT_CLASS(Robot);

