// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
// #define M_PI 3.14159265358979323846 // pi
#include "frc/commands/Subsystem.h"
#include "Utilities/MotionProfile.h"
#include "Utilities/TalonTelemetry.h"
#include "frc/WPILib.h"

class DriveTrain: public frc::Subsystem {
public:
	DriveTrain();
	double GetSpeed();
	int GetPosition();
	void SetSpeed(double speed);
	void InitDefaultCommand() override;
	void Periodic() override;
	void ArcadeDrive(double moveValue, double rotateValue, bool squaredInputsf);
	void SetSafetyEnabled(bool enabled);
	void InitializeMotionProfile(const ProfileGenerator& left, const ProfileGenerator& right);
	void TerminateMotionProfile();
	void SetOutput(double speed);
	bool IsMotionProfileFinished() const;
	void EnableVoltageCompensation(bool enabled);

	int GetPositionLeft();
	int GetPositionRight();
	void SetBrake();
	void SetCoast();

	constexpr static double wheelCircumference = 4 * 0.0254 * M_PI; // Meters
	constexpr static double lowGgearRatio = 15.0 / 1.0;
	constexpr static double lowGgearEncoderRatio = lowGgearRatio * (12.0 / 30.0);
	constexpr static double highGgearRatio = 4.12 / 1.0;
	constexpr static double highGgearEncoderRatio = highGgearRatio * (12.0 / 30.0);
#ifdef PRACTICE_BOT
	constexpr static double sensorUnitsPerRev = 128 * 4; // The TalonSRX counts 4 edges per encoder count, the quadrature encoder has 128 counts per revolution
#else
	constexpr static double sensorUnitsPerRev = 256 * 4; // The TalonSRX counts 4 edges per encoder count, the quadrature encoder has 256 counts per revolution
#endif
	constexpr static double nativeUnitsPerMeterLowGear = 1 / wheelCircumference * lowGgearEncoderRatio * sensorUnitsPerRev; // Approx. 19249 for 256 count per rev, 9624 for 128 count per rev
	constexpr static double nativeUnitsPerMeterHighGear = 1 / wheelCircumference * highGgearEncoderRatio * sensorUnitsPerRev;

    constexpr static double maxNativeUnitsPer100ms = 2950 * sensorUnitsPerRev / 1024; // measured at 11v on comp bot with 1024 native units per rev
    constexpr static double maxVelocityLowGear = 10 * maxNativeUnitsPer100ms / nativeUnitsPerMeterLowGear; // Approx. 1.51 Meters per second
	constexpr static double feedForwardGain = 1023 / maxNativeUnitsPer100ms;

private:
	void ConfigureTalon(WPI_TalonSRX& talon);

	constexpr static int slotIdx = 0;
	constexpr static int pidIdx = 0;
	constexpr static int timeoutMs = 10;

	const std::shared_ptr<WPI_TalonSRX> m_talonSRX1;
	const std::shared_ptr<WPI_TalonSRX> m_talonSRX2;
	const std::shared_ptr<frc::RobotDrive> m_robotDrive;
	MotionProfile m_leftProfile;
	MotionProfile m_rightProfile;
	TalonTelemetry m_leftTelemetry;
	TalonTelemetry m_rightTelemetry;
	frc::Command* m_driveWithJoystick = nullptr;
};

#endif
