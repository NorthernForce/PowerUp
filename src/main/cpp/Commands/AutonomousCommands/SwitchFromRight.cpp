// #include "SwitchFromRight.h"

// #include "frc/DriverStation.h"
// #include "Utilities/FieldOrientation.h"
// #include "Utilities/RobotNavigation.h"
// #include "Commands/AutonomousDriveForward.h"
// #include "Commands/AutonomousDriveWithEncoders.h"
// #include "Commands/AutonomousTurnWithGyro.h"
// #include "Commands/AutonomousWait.h"
// #include "Commands/PositionArm.h"
// #include "Commands/CloseGripper.h"
// #include "Commands/OpenGripper.h"
// #include "Commands/ShiftGearbox.h"

// SwitchFromRight::SwitchFromRight() {
// 	AddSequential(new CloseGripper());
// 	AddSequential(new PositionArm(PositionArm::Position::Switch));
// 	AddSequential(new AutonomousDriveForward(3900, -0.8));
// 	AddSequential(new AutonomousTurnWithGyro(90, 0.35));
// 	AddSequential(new AutonomousDriveForward(1800, -0.6));
// 	AddSequential(new AutonomousWait(500));
// 	AddSequential(new OpenGripper());
// 	AddSequential(new AutonomousWait(500));
// 	AddSequential(new AutonomousDriveForward(-1400, -0.6));
// 	AddSequential(new PositionArm(PositionArm::Position::Pickup));
// 	AddSequential(new CloseGripper());
// }
