#include "Drivetrain.h"

#include "../RobotMap.h"
#include "../Commands/TeleopDrive.h"

Drivetrain::Drivetrain() : Subsystem("Drivetrain") {
	ahrs = std::make_unique<AHRS> ( SerialPort::kMXP );
	for (int i = 0; i<4;i++){
		SpeedEncoders[i] = std::make_unique<frc::Encoder> ( ENCODER_SPEED_A[i], ENCODER_SPEED_B[i] );
		PositionEncoders[i] = std::make_unique<frc::AnalogInput> ( ENCODER_POSITION[i] );
		DriveVictors[i] = std::make_unique<frc::VictorSP> ( MOTOR_DRIVE[i] );
		TurnVictors[i] = std::make_unique<frc::VictorSP> ( MOTOR_TURN[i] );
		PositionPID[i] = std::make_unique<frc::PIDController> ( PID_POS_P, PID_POS_I, PID_POS_D, PID_POS_F, PositionEncoders[i].get(), TurnVictors[i].get() );
		PositionPID[i]->SetInputRange(0, 5);
		PositionPID[i]->SetOutputRange(-1, 1);
		PositionPID[i]->SetContinuous(true);
	}
}

void Drivetrain::InitDefaultCommand() {
	SetDefaultCommand(new TeleopDrive());
}

std::vector<double> Drivetrain::GetWheelPos(){
	std::vector<double> positions;
	for (int i =0; i<4;i++){
		positions.push_back(PositionEncoders[i]->GetVoltage()*(360.0/5.0));
	}
	return positions;
}

double Drivetrain::GetAngle(){
	return ahrs->GetYaw();
}

