#ifndef COMMANDGROUPBUILDER_H
#define COMMANDGROUPBUILDER_H

#include "Commands/CommandGroup.h"

frc::CommandGroup* BuildSequential(const std::initializer_list<frc::Command*> items);
frc::CommandGroup* BuildParallel(const std::initializer_list<frc::Command*> items);

#endif
