// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ScoreTwice.h"
#include "DriverStation.h"
#include "Robot.h"

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR


ScoreTwice::ScoreTwice(): ConditionalCommand(new ScoreOnSwitchThenScale, new ScoreOnScaleThenSwitch) {
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// See https://wpilib.screenstepslive.com/s/currentCS/m/getting_started/l/826278-2018-game-data-details for details
bool ScoreTwice::Condition(){
	const auto& ds = DriverStation::GetInstance();
	const auto& message = ds.GetGameSpecificMessage();
	const auto& currentPos = Robot::fieldPositioningSystem->GetPosition();
	const auto switchPos = message.length() > 1 ? message[0] : 0;
	const auto scalePos = message.length() > 2 ? message[1] : 0;

	// When the switch and scale are on the same side we go for the scale first
	if(switchPos == scalePos) {
		return false;
	}

	// When the robot is on the left and the switch is on the left (and scale on the right) - start with the switch
	if(currentPos.x < 2 && switchPos == 'L' ) {
		return true;
	}

	// When the robot is on the right and the switch is on the right (and scale on the left) - start with the switch
	if(currentPos.x > 2 && switchPos == 'R' ) {
		return true;
	}

	// Start with the scale and then go for the switch
	return false;
}
