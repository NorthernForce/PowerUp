#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "AHRS.h"

class RobotMap {
public:
	static std::shared_ptr<WPI_TalonSRX> driveTrainTalonSRX1;
	static std::shared_ptr<WPI_TalonSRX> driveTrainTalonSRX3;
	static std::shared_ptr<WPI_TalonSRX> driveTrainTalonSRX5;
	static std::shared_ptr<WPI_TalonSRX> driveTrainTalonSRX2;
	static std::shared_ptr<WPI_TalonSRX> driveTrainTalonSRX4;
	static std::shared_ptr<WPI_TalonSRX> driveTrainTalonSRX6;
	static std::shared_ptr<WPI_TalonSRX> elevatorTalonSRX7;
	static std::shared_ptr<WPI_TalonSRX> elevatorTalonSRX9;
	static std::shared_ptr<WPI_TalonSRX> armTalonSRX8;
	static std::shared_ptr<WPI_TalonSRX> gripperIntakeTalonSRX11;
	static std::shared_ptr<frc::RobotDrive> driveTrainRobotDrive;
	static std::shared_ptr<frc::Compressor> compressor;
	static std::shared_ptr<frc::DoubleSolenoid> driveTrainShifterDS;
	static std::shared_ptr<frc::Solenoid> gripperSolenoid;
	static std::shared_ptr<frc::Solenoid> elevatorBrake;
	static std::shared_ptr<AHRS> ahrs;
	static void init();
};
#endif
