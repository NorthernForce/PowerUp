#ifndef OI_H
#define OI_H

#include "frc/WPILib.h"

class OI {
private:
	std::shared_ptr<frc::Joystick> manipulatorJoystick;
	std::shared_ptr<frc::XboxController> driverController;
public:
	OI();
	const std::shared_ptr<frc::Joystick>& getManipulatorJoystick();
	const std::shared_ptr<frc::XboxController>& getDriverController();
};

#endif //OI_H
