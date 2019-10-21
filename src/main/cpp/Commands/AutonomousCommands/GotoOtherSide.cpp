// #include "GotoOtherSide.h"

// #include "DriverStation.h"
// #include "Utilities/FieldOrientation.h"
// #include "Utilities/RobotNavigation.h"
// #include "Commands/AutonomousDriveWithEncoders.h"
// #include "Commands/AutonomousTurnWithGyro.h"
// #include "Commands/AutonomousWait.h"
// #include "Commands/PositionArm.h"
// #include "Commands/CloseGripper.h"

// GotoOtherSide::GotoOtherSide() {
// 	const auto& ds = DriverStation::GetInstance();
// 	const auto& message = ds.GetGameSpecificMessage();
// 	const FieldOrientation orientation(message);

// 	AddSequential(new CloseGripper());
// 	AddSequential(new PositionArm(PositionArm::Position::ScaleFront));
// 	AddSequential(new AutonomousDriveForward(5500, -0.8));
// //	if (orientation.GetScalePos() == Position::Right)
// //		AddSequential(new AutonomousTurnWithGyro(-90, 0.35));
// //	else
// //		AddSequential(new AutonomousTurnWithGyro(90, 0.35));
// //	AddSequential(new AutonomousDriveForward(6000, -0.8));
// 	AddSequential(new AutonomousWait(500));
// 	AddSequential(new CloseGripper());
// }
