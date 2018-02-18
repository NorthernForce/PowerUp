/*
 * DriveTrainShifter.h
 *
 *  Created on: Feb 15, 2018
 *      Author: Seiya
 */

#ifndef SRC_SUBSYSTEMS_DRIVETRAINSHIFTER_H_
#define SRC_SUBSYSTEMS_DRIVETRAINSHIFTER_H_
#include "Commands/Subsystem.h"
#include "WPILib.h"


//Constants for high speed, low speed through the PCM


//Instanteate Double Solenoid objects


//Shift between high speed and low speed


//Setup function

class DriveTrainShifter: public frc::Subsystem {
private:
	std::shared_ptr<frc::DoubleSolenoid>doubleSolenoidLeft;
	std::shared_ptr<frc::DoubleSolenoid>doubleSolenoidRight;


public:
	DriveTrainShifter();
	void InitDefaultCommand() override;
	void Periodic() override;
};



#endif /* SRC_SUBSYSTEMS_DRIVETRAINSHIFTER_H_ */
