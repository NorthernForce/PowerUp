#include "Robot.h"
#include "Vision.h" // haha yeah right.

#include "Commands/CreateAutonomous/CreateCrossAutoLine.h"
#include "Commands/CreateAutonomous/CreateLeftOnlyScale.h"
#include "Commands/CreateAutonomous/CreateLeftOnlySwitch.h"
#include "Commands/CreateAutonomous/CreateLeftPrioritizeScale.h"
#include "Commands/CreateAutonomous/CreateLeftPrioritizeSwitch.h"
#include "Commands/CreateAutonomous/CreateRightOnlyScale.h"
#include "Commands/CreateAutonomous/CreateRightOnlySwitch.h"
#include "Commands/CreateAutonomous/CreateRightPrioritizeScale.h"
#include "Commands/CreateAutonomous/CreateRightPrioritizeSwitch.h"
#include "Commands/CreateAutonomous/CreateCenterSwitch.h"
#include "Commands/CreateAutonomous/DONOTHING.h"

#include "Commands/ShiftGearbox.h"

std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<DriveTrainShifter> Robot::driveTrainShifter;
std::shared_ptr<FieldPositioningSystem> Robot::fieldPositioningSystem;
std::shared_ptr<Gripper> Robot::gripper;
std::shared_ptr<GripperIntake> Robot::gripperIntake;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<Elevator> Robot::elevator;
std::shared_ptr<Arm> Robot::arm;
std::shared_ptr<Gimbal> Robot::gimbal;
std::shared_ptr<UltrasonicSensor> Robot::ultrasonicSensor;

namespace {
	class AutonomousCommandBuilder : frc::Command {
	public:
		using Builder = std::function<frc::Command*()>;
		AutonomousCommandBuilder(const char* name, const Builder& builder) :
			frc::Command(name),
			m_builder(builder) {
			SetRunWhenDisabled(true);
			Requires(m_autonomousSubsystem);
			frc::SmartDashboard::PutData(name, this);
		}

		void Initialize() override {
			m_lastSelected = this;
			char message[200];
			sprintf(message, "Autonomous mode %s selected", GetName().c_str());
			DriverStation::ReportError(message);
		}

		bool IsFinished() override {
			return false;
		}

		static Command* GetAutonomousCommand() {
			if (m_lastSelected) {
				return m_lastSelected->m_builder();
			}
			//TODO: add message
			return nullptr;
		}

	private:
		static frc::Subsystem* m_autonomousSubsystem;
		static AutonomousCommandBuilder* m_lastSelected;
		Builder m_builder;
	};

	frc::Subsystem* AutonomousCommandBuilder::m_autonomousSubsystem = new frc::Subsystem("Autonomous subsystem");
	AutonomousCommandBuilder* AutonomousCommandBuilder::m_lastSelected = nullptr;
}

Robot* Robot::robot = nullptr;

Robot::Robot() {
	robot = this;
}

void Robot::RobotInit() {
	RobotMap::init();
    driveTrain.reset(new DriveTrain());
    driveTrainShifter.reset(new DriveTrainShifter());
    fieldPositioningSystem.reset(new FieldPositioningSystem());
    gripper.reset(new Gripper());
    gripperIntake.reset(new GripperIntake());
    elevator.reset(new Elevator());
    arm.reset(new Arm());
	oi.reset(new OI());
	driveTrainShifter->Shift(DriveTrainShifter::Gear::Low);

    autonomousChooser.AddDefault("1) Cross the Auto-Line", new CreateCrossAutoLine());
    autonomousChooser.AddObject("2) Left: Prioritize Scale", new CreateLeftPrioritizeScale());
    autonomousChooser.AddObject("3) Right: Prioritize Scale", new CreateRightPrioritizeScale());
    autonomousChooser.AddObject("4) Left: Only Scale", new CreateLeftOnlyScale());
    autonomousChooser.AddObject("5) Right: Only Scale", new CreateRightOnlyScale());
    autonomousChooser.AddObject("6) Left: Prioritize Switch", new CreateLeftPrioritizeSwitch());
    autonomousChooser.AddObject("7) Right: Prioritize Switch", new CreateRightPrioritizeSwitch());
    autonomousChooser.AddObject("8) Left: Only Switch (Not working)", new CreateLeftOnlySwitch());
    autonomousChooser.AddObject("9) Right: Only Switch (Not Working)", new CreateRightOnlySwitch());
    autonomousChooser.AddObject("10) Center: Switch (Untested)", new CreateCenterSwitch());
    autonomousChooser.AddObject("11) Do nothing", new DONOTHING());

   	frc::SmartDashboard::PutData("Autonomous Modes", &autonomousChooser);

	//gimbal.reset(new Gimbal(0, 1));
//	gimbal->SetPan(100);
//	gimbal->SetTilt(200);
//	ultrasonicSensor.reset(new UltrasonicSensor(0, 0, 0));
//	cs::UsbCamera camera0 = CameraServer::GetInstance()->StartAutomaticCapture(0);
//	if (!camera0.IsConnected()) {
//		CameraServer::GetInstance()->RemoveCamera(camera0.GetName());
//	}
	CameraServer::GetInstance()->StartAutomaticCapture();

	frc::Scheduler::GetInstance()->AddCommand(new ShiftGearbox(ShiftGearbox::Gear::Low));

//	std::thread visionThread(VisionThread);
//	visionThread.detach();
}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit() {
	//TODO: go to home pos for arm

	RobotMap::bothEncodersBroke = false;
}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();

	frc::SmartDashboard::PutNumber("Left Encoder Positon (Talon 1):", Robot::driveTrain->GetPositionLeft());
	frc::SmartDashboard::PutNumber("Right Encoder Positon (Talon 2):", Robot::driveTrain->GetPositionRight());
}

void Robot::AutonomousInit() {
	driveTrain->SetSafetyEnabled(false);
	//TODO: get autonomous command chooser working
//	autonomousCommand = AutonomousCommandBuilder::GetAutonomousCommand();
//	if (autonomousCommand != nullptr)
//	{
//		char message[200];
//		sprintf(message, "Running autonomous mode %s", autonomousCommand->GetName().c_str());
//		autonomousCommand->Start();
//		DriverStation::ReportError(message);
//	}
//	else
//	{
//		DriverStation::ReportError("No autonomous mode selected");
//	}

//	autonomousCommand = new AutonomousLeft();
//	autonomousCommand = new AutonomousCenter();
//	autonomousCommand = new AutonomousRight();
	autonomousCommand.reset(autonomousChooser.GetSelected());

//	Wait(10);

	char message[200];
	sprintf(message, "Running autonomous mode %s", autonomousCommand->GetName().c_str());
	if(autonomousCommand.get() != nullptr) {
		autonomousCommand->Start();
	}
	DriverStation::ReportError(message);
}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();

	frc::SmartDashboard::PutNumber("Left Encoder Positon (Talon 1):", Robot::driveTrain->GetPositionLeft());
	frc::SmartDashboard::PutNumber("Right Encoder Positon (Talon 2):", Robot::driveTrain->GetPositionRight());

	if (RobotMap::bothEncodersBroke) {
		autonomousCommand->Cancel();
	}
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand != nullptr) {
		autonomousCommand->Cancel();
	}
}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();

	frc::SmartDashboard::PutNumber("Left Encoder Positon (Talon 1):", Robot::driveTrain->GetPositionLeft());
	frc::SmartDashboard::PutNumber("Right Encoder Positon (Talon 2):", Robot::driveTrain->GetPositionRight());
//	printf("elevator pos: %i\n", RobotMap::elevatorTalonSRX9->GetSensorCollection().GetQuadraturePosition());
}

START_ROBOT_CLASS(Robot);
