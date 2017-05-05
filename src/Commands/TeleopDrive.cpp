#include "TeleopDrive.h"

TeleopDrive::TeleopDrive() {
	Requires(CommandBase::drivetrain.get());
}

void TeleopDrive::Initialize() {

}

void TeleopDrive::Execute() {
	double PI = 3.14159265359;
	std::pair<double, double> joystickPos = CommandBase::oi->GetLeftJoystick();
	double drivetrainangle = CommandBase::drivetrain->GetAngle() * PI/180.0;
	std::pair<double, double> translateVector = std::make_pair(joystickPos.first*cos(drivetrainangle) - joystickPos.second*sin(drivetrainangle),
															   joystickPos.first*sin(drivetrainangle) + joystickPos.second*cos(drivetrainangle));
	double rotate = CommandBase::oi->GetRightJoystick().first;
	std::vector<double> wheelPos = CommandBase::drivetrain->GetWheelPos();
	double velocities[] = {translateVector.first - rotate*wheelbase/2.0, translateVector.first + rotate*wheelbase/2.0,
						   translateVector.second - rotate*trackwidth/2.0, translateVector.second + rotate*trackwidth/2.0};
	//double wheelVectors[4][2] = {{velocities[1], velocities[2]}, {velocities[1], velocities[3]}, {velocities[0], velocities[3]}, {velocities[0], velocities[2]}};
	double wheelVelocities[4] = {sqrt(velocities[1]*velocities[1] + velocities[2]*velocities[2]), sqrt(velocities[1]*velocities[1] + velocities[3]*velocities[3]), sqrt(velocities[0]*velocities[0] + velocities[3]*velocities[3]), sqrt(velocities[0]*velocities[0] + velocities[2]*velocities[2])};
	double wheelAngles[4] = {atan2(velocities[1], velocities[2])*180/PI, atan2(velocities[1], velocities[3])*180/PI, atan2(velocities[0], velocities[3])*180/PI, atan2(velocities[0], velocities[2])*180/PI};
	double setpoints[4], largest = -1;
	for (int i = 0; i<4;i++){
		frc::SmartDashboard::PutNumber("Velocity" + std::to_string(i+1), wheelVelocities[i]);
		frc::SmartDashboard::PutNumber("Angle" + std::to_string(i+1), wheelAngles[i]);
		frc::SmartDashboard::PutNumber("Position" + std::to_string(i+1), wheelPos[i]);
		
		wheelAngles[i] = MoveAngleToRange(-wheelAngles[i] + 90);
		double dist = -AngleDistance(wheelPos[i], wheelAngles[i]);
		setpoints[i] = MoveAngleToRange(wheelPos[i] + dist);
		if (std::fabs(setpoints[i]-wheelAngles[i]) > 1){
			wheelVelocities[i]*=-1; // If closest point is not in correct direction, reverse
		}
		largest = std::max(largest, std::fabs(wheelVelocities[i]));
		frc::SmartDashboard::PutNumber("Setpoint" + std::to_string(i+1), setpoints[i]);
		frc::SmartDashboard::PutBoolean("Reversed" + std::to_string(i+1), wheelVelocities[i] < 0);
	}
	for (int i = 0; i<4;i++){
		if (largest>1){
			wheelVelocities[i]/=largest;
		}
		CommandBase::drivetrain->PositionPID[i]->SetSetpoint(setpoints[i] * 5.0/360.0); // Convert degrees to volts
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
	double PI = 3.14159265;
	return atan(sin(a*PI/180.0 - b*PI/180.0)/ cos(a*PI/180.0 - b*PI/180.0))*180.0/PI;
}
