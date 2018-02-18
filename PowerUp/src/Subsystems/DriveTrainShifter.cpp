/*
 * DriveTrainShifter.cpp
 *
 *  Created on: Feb 15, 2018
 *      Author: Seiya
 */




#include <RobotMap.h>

#include "DriveTrainShifter.h"




DriveTrainShifter::DriveTrainShifter() : frc::Subsystem("DriveTrainShifter") {
	doubleSolenoidLeft = RobotMap::driveTrainShifterDoubleSolenoidLeft;
	doubleSolenoidRight = RobotMap::driveTrainShifterDoubleSolenoidRight;


}

void DriveTrainShifter::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());



}

void DriveTrainShifter::Periodic() {
    // Put code here to be run every loop

}
