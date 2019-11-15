#include <frc/WPILib.h>
#include "ctre/Phoenix.h"

/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

    /* Drive Talons */
    std::shared_ptr<WPI_TalonSRX> k_primaryTalonLeft;
    std::shared_ptr<WPI_TalonSRX> k_primaryTalonRight;
    std::shared_ptr<WPI_TalonSRX> k_followerTalon1Left;
    std::shared_ptr<WPI_TalonSRX> k_followerTalon1Right;
    std::shared_ptr<WPI_TalonSRX> k_followerTalon2Left;
    std::shared_ptr<WPI_TalonSRX> k_followerTalon2Right;

    /* Arm assembly Talons */
    std::shared_ptr<WPI_TalonSRX> k_elevatorTalon;
    std::shared_ptr<WPI_TalonSRX> k_armTalon; // unused for now

    /* Drive Talon IDs */
    const static int k_leftPrimaryTalon_id = 1;
    const static int k_rightPrimaryTalon_id = 2;
    const static int k_leftFollowerTalon1_id = 3;
    const static int k_rightFollowerTalon1_id = 4;
    const static int k_leftFollowerTalon2_id = 5;
    const static int k_rightFollowerTalon2_id = 6;

    /* Arm Talon IDs */
    const static int k_armTalon_id = 8;
    const static int k_elevatorTalon_id = 9;

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int kLeftMotor = 1;
// constexpr int kRightMotor = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int kRangeFinderPort = 1;
// constexpr int kRangeFinderModule = 1;
