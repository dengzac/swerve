#ifndef TELEOP_DRIVE_H
#define TELEOP_DRIVE_H

#include "../CommandBase.h"
#include <cmath>

class TeleopDrive: public CommandBase {
public:
	TeleopDrive();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	double wheelbase = 0;
	double trackwidth = 0;
	double diagonallength = sqrt(wheelbase*wheelbase + trackwidth*trackwidth)/2;
	double MoveAngleToRange(double angle);
};

#endif  // TELEOP_DRIVE_H
