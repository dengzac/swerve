#ifndef OI_H
#define OI_H

#include <Joystick.h>
class OI {
public:
	OI();
	std::pair<double, double> GetLeftJoystick();
	std::pair<double, double> GetRightJoystick();
private:
	std::unique_ptr<frc::Joystick> leftStick;
    std::unique_ptr<frc::Joystick> rightStick;
};

#endif  // OI_H
