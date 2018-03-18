//Not being used currently

#include "ctre/Phoenix.h"
#include "GripperIntake.h"
#include "../RobotMap.h"

GripperIntake::GripperIntake() : frc::Subsystem("GripperIntake") ,
	m_gripperIntakeTalon(RobotMap::gripperIntakeTalonSRX11),
    m_gripperIntakeSolenoid(RobotMap::gripperIntakeSolenoid)

	{
    isRunning = false;
}

void GripperIntake::RunIntakeWheels() {
	m_gripperIntakeTalon->Set(0.5);
	isRunning = true;
}

void GripperIntake::StopIntakeWheels() {
	m_gripperIntakeTalon->StopMotor();
	isRunning = false;
}

void GripperIntake::LowerIntake() {
	m_gripperIntakeSolenoid->Set(true);
}

void GripperIntake::RaiseIntake() {
	m_gripperIntakeSolenoid->Set(false);
}

bool GripperIntake::IsDown() {
	return m_gripperIntakeSolenoid->Get();
}

bool GripperIntake::IsRunning() {
	return isRunning;
}

