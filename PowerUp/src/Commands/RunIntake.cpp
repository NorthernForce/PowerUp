//Currently not being used

#include "RunIntake.h"

RunIntake::RunIntake(): frc::Command() {
	Requires(Robot::gripperIntake.get());
}
void RunIntake::Initialize() {
	Robot::gripperIntake->Enable();
}

void RunIntake::Execute() {
}

bool RunIntake::IsFinished() {
	return Robot::gripper->IsClosed();
}

void RunIntake::End() {
	Robot::gripperIntake->Disable();
}

void RunIntake::Interrupted() {
}
