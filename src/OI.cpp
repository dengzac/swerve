#include "OI.h"

#include <WPILib.h>

OI::OI() {
	leftStick = std::make_unique<frc::Joystick> ( 0 );
    rightStick = std::make_unique<frc::Joystick> ( 1 );
}

std::pair<double, double> OI::GetLeftJoystick(){
	return std::make_pair(leftStick->GetX(), leftStick->GetY());
}

std::pair<double, double> OI::GetRightJoystick(){
	return std::make_pair(rightStick->GetX(), rightStick->GetY());
}