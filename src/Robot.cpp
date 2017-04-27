#include <memory>

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include "Commands/ExampleCommand.h"
#include "CommandBase.h"

class Robot: public IterativeRobot {
public:
	void RobotInit() override {

	}


	void DisabledInit() override {

	}

	void DisabledPeriodic() override {
		Scheduler::GetInstance()->Run();
	}

	void AutonomousInit() override {

	}

	void AutonomousPeriodic() override {
		Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		if (autonomousCommand != nullptr) {
			autonomousCommand->Cancel();
		}
	}

	void TeleopPeriodic() override {
		Scheduler::GetInstance()->Run();
	}

	void TestPeriodic() override {
		LiveWindow::GetInstance()->Run();
	}

private:
	std::unique_ptr<Command> autonomousCommand;
};

START_ROBOT_CLASS(Robot)
