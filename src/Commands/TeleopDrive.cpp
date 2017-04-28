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
	std::vector<double> wheelPos = CommandBase::drivetrain->GetWheelPos();
	double velocities[] = {translateVector.first - rotate*wheelbase/2.0, translateVector.first + rotate*wheelbase/2.0,
						   translateVector.second - rotate*trackwidth/2.0, translateVector.second + rotate*trackwidth/2.0};
	double wheelVectors[4][2] = {{velocities[1], velocities[2]}, {velocities[1], velocities[3]}, {velocities[0], velocities[3]}, {velocities[0], velocities[2]}};
	double wheelVelocities[4] = {sqrt(velocities[1]*velocities[1] + velocities[2]*velocities[2]), {sqrt(velocities[1]*velocities[1] + velocities[3]*velocities[3])}, {sqrt(velocities[0]*velocities[0] + velocities[3]*velocities[3])}, {sqrt(velocities[0]*velocities[0] + velocities[2]*velocities[2])}};
	double wheelAngles[4] = {atan2(velocities[1], velocities[2])*180/PI, atan2(velocities[1], velocities[3])*180/PI, atan2(velocities[0], velocities[3])*180/PI, atan2(velocities[0], velocities[2])*180/PI};
	for (int i = 0; i<4;i++){
		frc::SmartDashboard::PutNumber("Velocity" + std::to_string(i+1), wheelVelocities[i]);
		frc::SmartDashboard::PutNumber("Angle" + std::to_string(i+1), wheelAngles[i]);
		frc::SmartDashboard::PutNumber("Position" + std::to_string(i+1), wheelPos[i]);
		double directDist, flipDist;
		double setpoint1, setpoint2, setpoint;
		bool reversed = false;
		wheelAngles[i] = MoveAngleToRange(-wheelAngles[i]);
		if (wheelPos[i] > wheelAngles[i]){
			directDist = wheelPos[i] - wheelAngles[i];
			flipDist = MoveAngleToRange(wheelAngles[i]+180) - wheelPos[i];
			setpoint1 = wheelAngles[i];
			setpoint2 = MoveAngleToRange(wheelAngles[i]+180);
		}
		else {
			directDist = wheelAngles[i] - wheelPos[i];
			flipDist = wheelPos[i] - MoveAngleToRange(wheelAngles+180);
			setpoint1 = wheelAngles[i];
			setpoint2 = MoveAngleToRange(wheelAngles[i]+180);
		}
		if (directDist < flipDist){
			setpoint = setpoint1;
			reversed = false;
		}
		else {
			setpoint = setpoint2;
			reversed = true;
		}
		frc::SmartDashboard::PutNumber("Setpoint" + std::to_string(i+1), setpoint);
		frc::SmartDashboard::putBoolean("Reversed" + std::to_string(i+1), reversed);
	}
}

bool TeleopDrive::IsFinished() {
	return false;
}

void TeleopDrive::End() {

}

void TeleopDrive::Interrupted() {

}

double TeleopDrive::MoveAngleToRange(double angle){
	while (angle<0){
		angle += 360;
	}
	while (angle>=360){
		angle -= 360;
	}
	return angle;
}

double TeleopDrive::AngleDistance(double a, double b){
	double PI = 3.14159265
	return atan2(sin(a*PI/180.0 - b*PI/180.0), cos(a*PI/180.0 - b*PI/180.0));
}
