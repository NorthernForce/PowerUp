

#include "Commands/DriveWithJoystick.h"
#include "DriveTrain.h"
#include "../RobotMap.h"
#include "ctre/Phoenix.h"

DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain")
{
    talonSRX1 = RobotMap::driveTrainTalonSRX1;
    talonSRX2 = RobotMap::driveTrainTalonSRX2;
    robotDrive = RobotMap::driveTrainRobotDrive;

    talonSRX1->ConfigSelectedFeedbackSensor(QuadEncoder, 0, 10);
    talonSRX2->ConfigSelectedFeedbackSensor(QuadEncoder, 0, 10);
}

void DriveTrain::InitDefaultCommand()
{
    SetDefaultCommand(new DriveWithJoystick());
}

double DriveTrain::GetSpeed()
{
	return ( talonSRX1->Get() + talonSRX2->Get() ) / 2.0;
}

void DriveTrain::Periodic()
{
}
