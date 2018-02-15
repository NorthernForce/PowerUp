#ifndef STARTFIELDPOSITIONINGSYSTEM_H
#define STARTFIELDPOSITIONINGSYSTEM_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class StartFieldPositioningSystem: public frc::Command
{
public:
	StartFieldPositioningSystem();

	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif
