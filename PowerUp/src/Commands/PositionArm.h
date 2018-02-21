#ifndef POSITIONARM_H
#define POSITIONARM_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

#include <map>

/**
 *
 *
 * @author ExampleAuthor
 */
class PositionArm: public frc::Command
{
public:
	enum class Position
	{
		Retracted,	// Starting position with arm in robot frame perimeter
		Pickup,		// Positioned to pick up
		Switch,		// Positioned to score on switch
		ScaleFront,	// Positioned to score on scale in front of the robot
		ScaleRear,	// Positioned to score on scale behind robot
		Climb		// Positioned to climb
	};

	PositionArm(Position setpoint);

	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	struct PositionSetpoints;
	static const std::map<Position, PositionSetpoints> m_setpoints;
	const std::shared_ptr<Elevator> m_elevator;
	const std::shared_ptr<Arm> m_arm;
	Position m_position;
};

#endif
