// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef ROBOTMAP_H
#define ROBOTMAP_H

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "WPILib.h"
#include "ctre/Phoenix.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Subsystems/Ultrasonic.h"

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
class RobotMap {
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static std::shared_ptr<WPI_TalonSRX> driveTrainTalonSRX1;
	static std::shared_ptr<WPI_TalonSRX> driveTrainTalonSRX3;
	static std::shared_ptr<WPI_TalonSRX> driveTrainTalonSRX5;
	static std::shared_ptr<frc::SpeedControllerGroup> driveTrainSpeedControllerGroupLeft;
	static std::shared_ptr<WPI_TalonSRX> driveTrainTalonSRX2;
	static std::shared_ptr<WPI_TalonSRX> driveTrainTalonSRX4;
	static std::shared_ptr<WPI_TalonSRX> driveTrainTalonSRX6;
	static std::shared_ptr<frc::SpeedControllerGroup> driveTrainSpeedControllerGroupRight;
	static std::shared_ptr<frc::RobotDrive> driveTrainRobotDrive;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	static void init();
};
#endif
