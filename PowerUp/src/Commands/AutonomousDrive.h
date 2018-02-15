#ifndef AUTONOMOUSDRIVE_H
#define AUTONOMOUSDRIVE_H

#include "Commands/Subsystem.h"
#include "Utilities/RobotNavigation.h"
#include "../Robot.h"

class AutonomousDrive: public frc::Command
{
public:
	AutonomousDrive(const RobotNavigation& navigation, const RobotNavigation::Position start, const RobotNavigation::Position finish);

	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	const RobotNavigation m_navigation;
	const RobotNavigation::Position m_start;
	const RobotNavigation::Position m_finish;
};

#endif
