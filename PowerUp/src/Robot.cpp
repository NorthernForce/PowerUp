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

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<DriveTrain> Robot::driveTrain;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION


static void VisionThread()
    {
        cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
//        int c = 16;
        camera.SetResolution(640, 480);
        cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
        cs::CvSource outputStreamStd = CameraServer::GetInstance()->PutVideo("Gray", 640, 480);
        cv::Mat source;
        cv::Mat output;
        while(true) {
            cvSink.GrabFrame(source);
            output = source;

            cv::Mat channels[3];
            cv::split(source, channels);

            output = channels[1];

			cv::threshold(output, output, 250, 255, 0);

			std::vector<std::vector<cv::Point> > contours;
			cv::findContours(output, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

			output = source;

//			if (contours.size() == 0) {
//				visionAngle = 0;
//			}

			std::vector<cv::Moments> moments(contours.size());
			for (unsigned int i = 0; i < contours.size(); i++) {
				moments[i] = cv::moments(contours[i]);

//				if (moments[i].m00 < source.cols*10) {
				if (moments[i].m00 < source.cols*(source.rows/96)) {
					contours.erase(contours.begin() + i);
					moments.erase(moments.begin() + i);
					i--;
				}
				else {
					cv::drawContours(output, contours, i, cv::Scalar(0, 0, 255), 1);

					cv::Point center = cv::Point(moments[i].m10/moments[i].m00, moments[i].m01/moments[i].m00);
					cv::circle(output, center, 2, cv::Scalar(255, 0, 0), 1);

					cv::Rect rect = cv::boundingRect(contours[i]);
					cv::rectangle(output, cv::Point(rect.x, rect.y), cv::Point(rect.x+rect.width, rect.y+rect.height), cv::Scalar(0, 255, 0), 1);

//					/// printing
//					if (center.x < c*20)
//						printf("contour: %i   x: turn left (%ipx)    ", i, center.x-c*20);
//					else if (center.x > c*20)
//						printf("contour: %i   x: turn right (%ipx)   ", i, center.x-c*20);
//					else
//						printf("contour: %i   x: your centered       ", i);
//
//					if (center.y < c*15)
//						printf("y: look up (%ipx)\n", center.y-c*15);
//					else if (center.y > c*15)
//						printf("y: look down (%ipx)\n", center.y-c*15);
//					else
//						printf("y: your centered");
//
//					fflush(stdout);

//					visionAngle = center.x;

					if (center.x > source.cols*0.49 && center.x < source.cols*0.51) {
						visionAngle = 0;
					}
					else {
						visionAngle = (float)(center.x-source.cols/2)/(float)(source.cols*0.75);
					}

					printf("visionAngle: %f\n",  visionAngle);
					fflush(stdout);
				}
			}

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


	/// auto turning
//	int c = 16;
//	if (joystick->GetRawButtonPressed(1)) {
//		// left
//		if (visionAngle < c*18) {
//				printf("center.x: %f    dec: %f\n", visionAngle, (float)(visionAngle-c*20)/(float)(c*20));
//			RobotMap::driveTrainRobotDrive->ArcadeDrive((float)(visionAngle-c*20)/(float)(c*20), 0, true);
//		}
//		// right
//		else if (visionAngle > c*22) {
//			RobotMap::driveTrainRobotDrive->ArcadeDrive((float)(visionAngle-c*20)/(float)(c*10), 0, true);
//			fflush(stdout);
//		}
//	}
//	printf("visionAngle %f\n", visionAngle);
//	fflush(stdout);

//	if (joystick->GetRawButtonPressed(1)) {
		RobotMap::driveTrainRobotDrive->ArcadeDrive(visionAngle, 0, true);
//	}
}

START_ROBOT_CLASS(Robot);

