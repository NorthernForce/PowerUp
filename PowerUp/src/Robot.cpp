// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"
#include "Commands/ShiftGearbox.h"

#include "Vision.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<DriveTrainShifter> Robot::driveTrainShifter;
std::shared_ptr<FieldPositioningSystem> Robot::fieldPositioningSystem;
std::shared_ptr<Gripper> Robot::gripper;
std::shared_ptr<GripperIntake> Robot::gripperIntake;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

std::shared_ptr<Elevator> Robot::elevator;
std::shared_ptr<Arm> Robot::arm;

std::shared_ptr<Gimbal> Robot::gimbal;
std::shared_ptr<UltrasonicSensor> Robot::ultrasonicSensor;

namespace
{
	class AutonomousCommandBuilder : frc::Command
	{
	public:
		using Builder = std::function<frc::Command*()>;
		AutonomousCommandBuilder(const char* name, const Builder& builder) :
			frc::Command(name),
			m_builder(builder)
		{
			SetRunWhenDisabled(true);
			Requires(m_autonomousSubsystem);
			frc::SmartDashboard::PutData(name, this);
		}

		void Initialize() override
		{
			m_selected = this;
		}

		bool IsFinished() override
		{
			return false;
		}

		static Command* GetAutonomousCommand()
		{
			if(m_selected)
			{
				return m_selected->m_builder();
			}

			return nullptr;
		}

		void Interrupted()
		{
			m_selected = nullptr;
		}


	private:
		static frc::Subsystem* m_autonomousSubsystem;
		static AutonomousCommandBuilder* m_selected;
		Builder m_builder;
	};

	frc::Subsystem* AutonomousCommandBuilder::m_autonomousSubsystem = new frc::Subsystem("Autonomous subsystem");
	AutonomousCommandBuilder* AutonomousCommandBuilder::m_selected = nullptr;
}

Robot* Robot::robot = nullptr;

Robot::Robot() {
	robot = this;
}

void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    driveTrain.reset(new DriveTrain());
    driveTrainShifter.reset(new DriveTrainShifter());
    fieldPositioningSystem.reset(new FieldPositioningSystem());
    gripper.reset(new Gripper());
    gripperIntake.reset(new GripperIntake());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
    elevator.reset(new Elevator());
    arm.reset(new Arm());
	oi.reset(new OI());

    new AutonomousCommandBuilder("Autonomous Mode Left", [](){ return new AutonomousLeft(); });
    new AutonomousCommandBuilder("Autonomous Mode Center", [](){ return new AutonomousCenter(); });
    new AutonomousCommandBuilder("Autonomous Mode Right", [](){ return new AutonomousRight(); });


//	auto* const lw = LiveWindow::GetInstance();
//	lw->Add(arm);
//	lw->Add(gripper);
//	lw->Add(RobotMap::gripperSolenoid);

	gimbal.reset(new Gimbal(0, 1));
//	gimbal->SetPan(100);
//	gimbal->SetTilt(200);
//	ultrasonicSensor.reset(new UltrasonicSensor(0, 0, 0));

	cs::UsbCamera camera0 = CameraServer::GetInstance()->StartAutomaticCapture(0);
	if (!camera0.IsConnected()) {
		CameraServer::GetInstance()->RemoveCamera(camera0.GetName());
	}

	frc::Scheduler::GetInstance()->AddCommand(new ShiftGearbox(ShiftGearbox::Gear::Low));

	std::thread visionThread(VisionThread);
	visionThread.detach();
}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit() {

}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	autonomousCommand = AutonomousCommandBuilder::GetAutonomousCommand();
	if (autonomousCommand != nullptr)
	{
		char message[200];
		sprintf(message, "Running autonomous mode %s", autonomousCommand->GetName().c_str());
		autonomousCommand->Start();
		DriverStation::ReportError("No autonomous mode selected");
	}
	else
	{
		DriverStation::ReportError("No autonomous mode selected");
	}
}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

START_ROBOT_CLASS(Robot);

