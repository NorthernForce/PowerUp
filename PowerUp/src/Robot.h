// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef _ROBOT_H
#define _ROBOT_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/AutonomousLeft.h"
#include "Commands/AutonomousCenter.h"
#include "Commands/AutonomousRight.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/DriveTrainShifter.h"
#include "Subsystems/FieldPositioningSystem.h"
#include "Subsystems/Gripper.h"
#include "Subsystems/GripperIntake.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

#include "Subsystems/Arm.h"
#include "Subsystems/Elevator.h"
#include "OI.h"

#include "Subsystems/Gimbal.h"
#include "Subsystems/UltrasonicSensor.h"

class Robot : public frc::TimedRobot {
public:
	static Robot* robot;
	frc::Command* autonomousCommand = nullptr;
	static std::unique_ptr<OI> oi;
	frc::LiveWindow *lw = frc::LiveWindow::GetInstance();
	frc::SendableChooser<frc::Command*> chooser;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static std::shared_ptr<DriveTrain> driveTrain;
	static std::shared_ptr<DriveTrainShifter> driveTrainShifter;
	static std::shared_ptr<FieldPositioningSystem> fieldPositioningSystem;
	static std::shared_ptr<Gripper> gripper;
	static std::shared_ptr<GripperIntake> gripperIntake;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	static std::shared_ptr<Elevator> elevator;
	static std::shared_ptr<Arm> arm;

	static std::shared_ptr<Gimbal> gimbal;
	static std::shared_ptr<UltrasonicSensor> ultrasonicSensor;

	Robot();
	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
};
#endif
