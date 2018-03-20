#ifndef GenerateCommandSequence_H
#define GenerateCommandSequence_H

#include <Commands/CommandGroup.h>
#include"Commands/PositionArm.h"

frc::CommandGroup* GenerateCommandSequence();
frc::CommandGroup* PositionArmSequence(PositionArm::Position pos);


#endif  // GenerateCommandSequence_H
