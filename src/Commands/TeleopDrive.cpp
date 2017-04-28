#include "TeleopDrive.h"

TeleopDrive::TeleopDrive() {
	Requires(CommandBase::drivetrain.get());
}

void TeleopDrive::Initialize() {

}

void TeleopDrive::Execute() {
	double PI = 3.14159265359;
	std::pair<double, double> translateVector = CommandBase::oi->GetLeftJoystick();
	double rotate = CommandBase::oi->GetRightJoystick().first;
	double velocities[] = {translateVector.x - rotate*wheelbase/2.0, translateVector.x + rotate*wheelbase/2.0,
						   translateVector.y - rotate*trackwidth/2.0, translateVector.y + rotate*trackwidth/2.0};
	double wheelVectors[4][2] = {{velocities[1], velocities[2]}, {velocities[1], velocities[3]}, {velocities[0], velocities[3]}, {velocities[0], velocities[2]}};
	double wheelVelocities[4] = {sqrt(velocities[1]*velocities[1] + velocities[2]*velocities[2]), {sqrt(velocities[1]*velocities[1] + velocities[3]*velocities[3])}, {sqrt(velocities[0]*velocities[0] + velocities[3]*velocities[3])}, {sqrt(velocities[0]*velocities[0] + velocities[2]*velocities[2])}};
	double wheelAngles[4] = {atan2(velocities[1], velocities[2])*180/PI, atan2(velocities[1], velocities[3])*180/PI, atan2(velocities[0], velocities[3])*180/PI, atan2(velocities[0], velocities[2])*180/PI};
	
}

bool TeleopDrive::IsFinished() {
	return false;
}

void TeleopDrive::End() {

}

void TeleopDrive::Interrupted() {

}
