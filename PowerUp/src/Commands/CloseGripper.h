#ifndef CLOSEGRIPPER_H
#define CLOSEGRIPPER_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 */
class CloseGripper: public frc::TimedCommand {
public:

	CloseGripper();

	void Initialize() override;
	void Execute() override;
	void End() override;
	void Interrupted() override;

private:
	constexpr static double timeToClose { 0.5 };
};

#endif
