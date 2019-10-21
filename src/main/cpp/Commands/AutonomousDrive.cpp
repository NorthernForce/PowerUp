// #include <Commands/AutonomousDrive.h>
// #include "Utilities/LogFileName.h"

// AutonomousDrive::AutonomousDrive(const RobotNavigation::RobotTrajectory& path) :
// 	frc::Command("Autonomous Drive"),
// 	m_path(path)
// {
// 	Requires(Robot::driveTrain.get());
// }

// void AutonomousDrive::Initialize()
// {
// 	Robot::driveTrain->SetSafetyEnabled(false);
// 	Robot::driveTrain->EnableVoltageCompensation(true);
// 	Robot::driveTrain->InitializeMotionProfile(m_path.m_left.m_generator, m_path.m_right.m_generator);
// }

// bool AutonomousDrive::IsFinished()
// {
// 	return Robot::driveTrain->IsMotionProfileFinished();
// }

// void AutonomousDrive::End()
// {
// 	Robot::driveTrain->TerminateMotionProfile();
// 	WritePathToFile();
// 	Robot::driveTrain->EnableVoltageCompensation(false);
// }

// void AutonomousDrive::Interrupted()
// {
// 	Robot::driveTrain->TerminateMotionProfile();
// 	WritePathToFile();
// 	Robot::driveTrain->EnableVoltageCompensation(false);
// }

// void AutonomousDrive::WritePathToFile()
// {
// 	Profile left = m_path.m_left;
// 	Profile right = m_path.m_right;

// 	std::ofstream os(GetLogFileName(GetName().c_str()));
// 	os << "Left Time,Left Position,Left Velocity,Right Time,Right Position,Right Velocity\n";
//     int t1 = 0;
//     int t2 = 0;
//     ProfilePoint p1 = {};
//     ProfilePoint p2 = {};
//     while (true)
//     {
//         if (!p1.m_last) p1 = left();
//         if (!p2.m_last) p2 = right();
//         t1 = t1 + p1.m_duration;
//         t2 = t2 + p2.m_duration;
//         os << t1 << "," << p1.m_position << "," << p1.m_velocity << "," <<
//         	  t2 << "," << p2.m_position << "," << p2.m_velocity << "\n";

//         if (p1.m_last && p2.m_last)
//             break;
//     }
//     os.close();
// }
