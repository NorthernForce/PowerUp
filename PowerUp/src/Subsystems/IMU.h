/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Subsystem.h>
#include <AHRS.h>
#include <RobotMap.h>

class IMU : public frc::Subsystem, public frc::PIDOutput
{

  private:
	//Constants for PIDF Controller
	double m_AngleRate;
	double m_SetAngle;
	constexpr static double kToleranceDegrees = 2.0f;

	std::shared_ptr<AHRS> m_ahrs;

	double kP = 0.03f;
	double kI = 0.00f;
	double kD = 0.00f;
	double kF = 0.00f;

	std::shared_ptr<frc::PIDController> m_TurnControl;

	void PIDWrite(float output)
	{
		m_AngleRate = output;
	}



  public:
	IMU();
	void InitDefaultCommand() override;
	double GetAngle();
	void SetAngle(double degAngle);
	void SetAngleOffset(double degAngle);
	void TurnTo(double angleDeg);
	void EnableTurn();
	void DisableTurn();
	void ExecuteTurn();



};
