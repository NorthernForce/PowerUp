#ifndef OPENGRIPPER_H
#define OPENGRIPPER_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 */
class OpenGripper: public frc::TimedCommand {
public:

	OpenGripper();

	void Initialize() override;
	void Execute() override;
	void End() override;
	void Interrupted() override;

private:
	const double timeToOpen { 0.5 };
};

#endif
