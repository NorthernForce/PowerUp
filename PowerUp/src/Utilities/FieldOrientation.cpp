#include "FieldOrientation.h"
#include "DriverStation.h"

Position FieldOrientation::m_startingRobotPos = {};
CoordinateAndHeading FieldOrientation::m_startingRobotCoord = {};

// See https://wpilib.screenstepslive.com/s/currentCS/m/getting_started/l/826278-2018-game-data-details for details
FieldOrientation::FieldOrientation(const std::string& message)
{
	auto getPosition = [&message](size_t index)
	{
		return toupper(message[index]) == 'L' ? Position::Left : Position::Right;
	};

	m_initialized = message.length() >= 2;
	if (m_initialized)
	{
		m_switchPos = getPosition(0);
		m_scalePos = getPosition(1);
	}
}

void FieldOrientation::SetStartingRobotCoordinate(Position pos, CoordinateAndHeading coord)
{
    m_startingRobotPos = pos;
    m_startingRobotCoord = coord;
}

CoordinateAndHeading FieldOrientation::GetSwitchCoordinate() const
{
	constexpr double xSwitch = 1.67;
	constexpr double ySwitch = 4.29;
	constexpr double hSwitch = 90;
	if(GetSwitchPos() == Position::Left)
	{
		return { xSwitch, ySwitch, hSwitch };
	}
	else
	{
		return { FieldWidth - xSwitch, ySwitch, -hSwitch };
	}
}

CoordinateAndHeading FieldOrientation::GetScaleCoordinate() const
{
	constexpr double xScale = 1.99;
	constexpr double yScale = 7.13;
	constexpr double hScale = 0;
	if(GetSwitchPos() == Position::Left)
	{
		return { xScale, yScale, hScale };
	}
	else
	{
		return { FieldWidth - xScale, yScale, hScale };
	}
}

CoordinateAndHeading FieldOrientation::GetCubeCoordinate(Position position) const
{
	constexpr double xCube = 2.31;
	constexpr double yCube = 5.79;
	constexpr double hCube = 180;
	if(GetSwitchPos() == Position::Left)
	{
		return { xCube, yCube, hCube };
	}
	else
	{
		return { FieldWidth - xCube, yCube, hCube };
	}
}
