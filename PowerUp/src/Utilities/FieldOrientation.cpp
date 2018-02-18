#include "Utilities/FieldOrientation.h"
#include "DriverStation.h"
#include "Robot.h"

CoordinateAndHeading FieldOrientation::m_startingRobotCoord = {};

// See https://wpilib.screenstepslive.com/s/currentCS/m/getting_started/l/826278-2018-game-data-details for details
FieldOrientation::FieldOrientation()
{
	const auto& ds = DriverStation::GetInstance();
	const auto& message = ds.GetGameSpecificMessage();

	auto getPosition = [&message](size_t index)
	{
		return toupper(message[index]) == 'L' ? Position::Left : Position::Right;
	};

	m_initialized = message.length() >= 2;
	if (m_initialized)
	{
		m_switchPos = getPosition(0);
		m_scalePos = getPosition(1);

		// We need to pull this from the dashboard
		m_startingRobotPos = Position::Center;
	}
}

void FieldOrientation::SetStartingRobotCoordinate(CoordinateAndHeading coord)
{
	m_startingRobotCoord = coord;
}

