#include "Commands/CommandGroupBuilder.h"

frc::CommandGroup* BuildSequential(const std::initializer_list<frc::Command*> items)
{
	frc::CommandGroup* group = new frc::CommandGroup;
	for (auto item : items)
	{
		group->AddSequential(item);
	}
	return group;
}

frc::CommandGroup* BuildParallel(const std::initializer_list<frc::Command*> items)
{
	frc::CommandGroup* group = new frc::CommandGroup;
	for (auto item : items)
	{
		group->AddParallel(item);
	}
	return group;
}
