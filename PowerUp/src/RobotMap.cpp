// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "ctre/Phoenix.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<WPI_TalonSRX> RobotMap::driveTrainTalonSRX1;
std::shared_ptr<WPI_TalonSRX> RobotMap::driveTrainTalonSRX3;
std::shared_ptr<WPI_TalonSRX> RobotMap::driveTrainTalonSRX5;
std::shared_ptr<WPI_TalonSRX> RobotMap::driveTrainTalonSRX2;
std::shared_ptr<WPI_TalonSRX> RobotMap::driveTrainTalonSRX4;
std::shared_ptr<WPI_TalonSRX> RobotMap::driveTrainTalonSRX6;
std::shared_ptr<WPI_TalonSRX> RobotMap::elevatorTalonSRX7;
std::shared_ptr<WPI_TalonSRX> RobotMap::elevatorTalonSRX9;
std::shared_ptr<WPI_TalonSRX> RobotMap::armTalonSRX8;
std::shared_ptr<WPI_TalonSRX> RobotMap::gripperIntakeTalonSRX10;
std::shared_ptr<frc::RobotDrive> RobotMap::driveTrainRobotDrive;
std::shared_ptr<frc::Compressor> RobotMap::compressor;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::driveTrainShifterDS;
std::shared_ptr<frc::Solenoid> RobotMap::gripperSolenoid;
std::shared_ptr<frc::Solenoid> RobotMap::elevatorBrake;
std::shared_ptr<AHRS> RobotMap::ahrs;

void RobotMap::init() {
    driveTrainTalonSRX1.reset(new WPI_TalonSRX(1));
    driveTrainTalonSRX3.reset(new WPI_TalonSRX(3));
    driveTrainTalonSRX5.reset(new WPI_TalonSRX(5));

    driveTrainTalonSRX2.reset(new WPI_TalonSRX(2));
    driveTrainTalonSRX4.reset(new WPI_TalonSRX(4));
    driveTrainTalonSRX6.reset(new WPI_TalonSRX(6));
    
    driveTrainRobotDrive.reset(new frc::RobotDrive(driveTrainTalonSRX1, driveTrainTalonSRX2));
    
    driveTrainRobotDrive->SetSafetyEnabled(true);
	driveTrainRobotDrive->SetExpiration(0.1);
	driveTrainRobotDrive->SetSensitivity(0.5);
	driveTrainRobotDrive->SetMaxOutput(1.0);
    
	elevatorTalonSRX9.reset(new WPI_TalonSRX(9));
	elevatorTalonSRX7.reset(new WPI_TalonSRX(7));

	armTalonSRX8.reset(new WPI_TalonSRX(8));

    gripperIntakeTalonSRX10.reset(new WPI_TalonSRX(10));

    compressor.reset(new Compressor(20));

    driveTrainShifterDS.reset(new DoubleSolenoid(3, 2));

    gripperSolenoid.reset(new frc::Solenoid(7));

    elevatorBrake.reset(new frc::Solenoid(0));

    driveTrainTalonSRX1->ConfigOpenloopRamp(1, 10);
    driveTrainTalonSRX1->SetInverted(false);
    driveTrainTalonSRX3->Follow(*driveTrainTalonSRX1);
    driveTrainTalonSRX3->SetInverted(false);
    driveTrainTalonSRX5->Follow(*driveTrainTalonSRX1);
    driveTrainTalonSRX5->SetInverted(true);

    driveTrainTalonSRX2->ConfigOpenloopRamp(1, 10);
    driveTrainTalonSRX2->SetInverted(true);
    driveTrainTalonSRX4->Follow(*driveTrainTalonSRX2);
    driveTrainTalonSRX4->SetInverted(true);
    driveTrainTalonSRX6->Follow(*driveTrainTalonSRX2);
    driveTrainTalonSRX6->SetInverted(false);

    //elevatorTalonSRX7->Follow(*elevatorTalonSRX9);

    armTalonSRX8 = std::make_unique<WPI_TalonSRX>(8);

    compressor->SetClosedLoopControl(true);

    ahrs = std::make_unique<AHRS>(frc::SPI::Port::kMXP);
}
