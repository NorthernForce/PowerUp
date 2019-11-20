/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include "Robot.h"
#include <map>

class PositionArm : public frc::Command {
 public:
  	enum class Position {
		Retracted,	// Starting position
		Pickup,		// Pick up position
		Switch,		// Score on switch
		ScaleFront,	// Score on scale in front of robot
		ScaleRear,	// Score on scale behind robot
		ClimbSet, // Climb position
		ClimbExecute // Climbs
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
