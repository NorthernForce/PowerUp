#include "RobotMap.h"
#include "ctre/Phoenix.h"

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
	//TODO: move away from ".reset", use make_shared\
	//Low priority
    driveTrainTalonSRX1.reset(new WPI_TalonSRX(1));
    driveTrainTalonSRX3.reset(new WPI_TalonSRX(3));
    driveTrainTalonSRX5.reset(new WPI_TalonSRX(5));
    driveTrainTalonSRX2.reset(new WPI_TalonSRX(2));
    driveTrainTalonSRX4.reset(new WPI_TalonSRX(4));
    driveTrainTalonSRX6.reset(new WPI_TalonSRX(6));
    //TODO: move to drive train
    driveTrainRobotDrive.reset(new frc::RobotDrive(driveTrainTalonSRX1, driveTrainTalonSRX2));
    driveTrainRobotDrive->SetSafetyEnabled(true);
	driveTrainRobotDrive->SetExpiration(0.1);
	driveTrainRobotDrive->SetSensitivity(0.5);
	driveTrainRobotDrive->SetMaxOutput(1.0);
	elevatorTalonSRX9.reset(new WPI_TalonSRX(9));
	elevatorTalonSRX7.reset(new WPI_TalonSRX(7));
	armTalonSRX8.reset(new WPI_TalonSRX(8));
    gripperIntakeTalonSRX11.reset(new WPI_TalonSRX(11));
    compressor.reset(new frc::Compressor());
    driveTrainShifterDS.reset(new DoubleSolenoid(2, 3));
    gripperSolenoid.reset(new frc::Solenoid(7));
    elevatorBrake.reset(new frc::Solenoid(0));
    driveTrainTalonSRX1->ConfigOpenloopRamp(0.75, 10);
    driveTrainTalonSRX1->SetInverted(false);
    driveTrainTalonSRX1->SetNeutralMode(NeutralMode::Coast);
    driveTrainTalonSRX3->Follow(*driveTrainTalonSRX1);
    driveTrainTalonSRX3->SetInverted(false);
    driveTrainTalonSRX3->SetNeutralMode(NeutralMode::Coast);
    driveTrainTalonSRX5->Follow(*driveTrainTalonSRX1);
    driveTrainTalonSRX5->SetInverted(true);
    driveTrainTalonSRX5->SetNeutralMode(NeutralMode::Coast);
    driveTrainTalonSRX2->ConfigOpenloopRamp(0.75, 10);
    driveTrainTalonSRX2->SetInverted(true);
    driveTrainTalonSRX2->SetNeutralMode(NeutralMode::Coast);
    driveTrainTalonSRX4->Follow(*driveTrainTalonSRX2);
    driveTrainTalonSRX4->SetInverted(true);
    driveTrainTalonSRX4->SetNeutralMode(NeutralMode::Coast);
    driveTrainTalonSRX6->Follow(*driveTrainTalonSRX2);
    driveTrainTalonSRX6->SetInverted(false);
    driveTrainTalonSRX6->SetNeutralMode(NeutralMode::Coast);
    compressor->SetClosedLoopControl(true);
    ahrs = std::make_unique<AHRS>(frc::SPI::Port::kMXP);
}
