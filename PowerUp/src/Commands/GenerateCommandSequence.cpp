#include "GenerateCommandSequence.h"]
#include "Commands/PositionArm.h"
#include "Commands/RunIntakeWheels.h"
#include "Commands/StopIntakeWheels.h"
#include "Commands/RaiseGripperIntake.h"
#include "Commands/LowerGripperIntake.h"


namespace {
	frc::CommandGroup* PickupTransition() {
		frc::CommandGroup* const sequence = new frc::CommandGroup;

		sequence->AddSequential(new PositionArm(PositionArm::Position::Switch));
		sequence->AddSequential(new LowerGripperIntake());
		sequence->AddSequential(new PositionArm(PositionArm::Position::Pickup));

		return sequence;


	}
	frc::CommandGroup* PositionArmSequence(PositionArm::Position pos) {
		frc::CommandGroup* const sequence = new frc::CommandGroup;

		sequence->AddSequential(new PositionArm(pos));
		sequence->AddSequential(new RaiseGripperIntake());
	}

}
