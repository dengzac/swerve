#include "CommandBase.h"

#include <Commands/Scheduler.h>

#include "Subsystems/Drivetrain.h"

// Initialize a single static instance of all of your subsystems. The following
// line should be repeated for each subsystem in the project.
std::unique_ptr<Drivetrain> CommandBase::drivetrain = NULL;

std::unique_ptr<OI> CommandBase::oi = NULL;

CommandBase::CommandBase(const std::string &name) : Command(name) {

}

void CommandBase::Init(){
	CommandBase::drivetrain = std::make_unique<Drivetrain>();
	CommandBase::oi = std::make_unique<OI>();
}
