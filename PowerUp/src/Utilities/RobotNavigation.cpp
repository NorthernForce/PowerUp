#include "Utilities/RobotNavigation.h"

RobotNavigation::RobotNavigation(const FieldOrientation& orientation) :
		m_fieldOrientation(orientation)
{
}

RobotNavigation::DriveProfile RobotNavigation::CreateProfile(const Position from, const Position to)
{
	return { };
}
