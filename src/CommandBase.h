#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <memory>
#include <string>

#include <Commands/Command.h>

#include "OI.h"
#include "Subsystems/Drivetrain.h"

class CommandBase: public Command {
public:
	CommandBase(const std::string& name);
	CommandBase() = default;
	void Init();
	
	// Create a single static instance of all of your subsystems
	static std::unique_ptr<Drivetrain> drivetrain;
	static std::unique_ptr<OI> oi;
};

#endif  // COMMAND_BASE_H
