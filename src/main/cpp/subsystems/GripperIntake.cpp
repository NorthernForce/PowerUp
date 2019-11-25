/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/GripperIntake.h"
#include "RobotMap.h"

GripperIntake::GripperIntake() :
 Subsystem("GripperIntake") {
    m_gripperIntakeSolenoid.reset(new frc::Solenoid(RobotMap::PCM::k_gripperIntakeSolenoid_id));
    m_gripperIntakeTalon.reset(new WPI_TalonSRX(RobotMap::ArmAssemblyTalons::k_gripperIntakeTalon_id));
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

void GripperIntake::SetIntake(State state) {
	if (state == State::Raised)
		m_gripperIntakeSolenoid->Set(false);
	else
		m_gripperIntakeSolenoid->Set(true);
}

bool GripperIntake::IsDown() {
	return m_gripperIntakeSolenoid->Get();
}

bool GripperIntake::IsRunning() {
	return isRunning;
}

void GripperIntake::InitDefaultCommand() {}

// Put methods for controlling this subsystem
// here. Call these from Commands.
