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
	}
}

void Drivetrain::InitDefaultCommand() {
	SetDefaultCommand(new TeleopDrive());
}


