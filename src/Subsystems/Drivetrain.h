#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include <Commands/Subsystem.h>
#include "navx-mxp/AHRS.h"

class Drivetrain: public Subsystem {
public:
	Drivetrain();
	void InitDefaultCommand() override;
	std::vector<double> GetWheelPos();
private:
	std::unique_ptr<frc::Encoder> SpeedEncoders[4];
	std::unique_ptr<frc::AnalogInput> PositionEncoders[4];
	std::unique_ptr<frc::VictorSP> DriveVictors[4];
	std::unique_ptr<frc::VictorSP> TurnVictors[4];
	
	std::unique_ptr<AHRS> ahrs;
};

#endif  // DRIVETRAIN_H
