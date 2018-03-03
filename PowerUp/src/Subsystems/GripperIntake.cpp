//Not being used currently

#include "ctre/Phoenix.h"
#include "GripperIntake.h"
#include "../RobotMap.h"

GripperIntake::GripperIntake() : frc::Subsystem("GripperIntake") {
    talonSRX11 = RobotMap::gripperIntakeTalonSRX11;
}

void GripperIntake::InitDefaultCommand() {
}

void GripperIntake::Periodic() {
}


void GripperIntake::Enable() {
	talonSRX11->Set(0.5);
}

void GripperIntake::Disable() {
	talonSRX11->StopMotor();
}
