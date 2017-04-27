#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include <Commands/Subsystem.h>

class Drivetrain: public Subsystem {
public:
	Drivetrain();
	void InitDefaultCommand() override;

private:

};

#endif  // DRIVETRAIN_H
