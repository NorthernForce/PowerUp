#ifndef FIELDORIENTATION_H
#define FIELDORIENTATION_H

#include <string>

enum class Position
{
	Left,
	Center,
	Right
};

struct CoordinateAndHeading
{
	double x, y, heading; // Meters and degrees
};

inline CoordinateAndHeading operator- (const CoordinateAndHeading& lhs, const CoordinateAndHeading& rhs)
{
	return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.heading - rhs.heading };
}

class FieldOrientation
{
public:
	constexpr static double FieldWidth = 8.23; // Meters
	constexpr static double StartCoordX = 1.2; // Meters from side
	constexpr static double StartCoordY = 0.5; // Meters from back wall
	constexpr static double StartCoordHeading = 0; // Degrees

	FieldOrientation(const std::string& message);
	FieldOrientation(const FieldOrientation&) = default;

	bool IsInitialized() const { return m_initialized; }

	Position GetSwitchPos() const { return m_switchPos; }
	Position GetScalePos() const { return m_scalePos; }
	Position GetStartingRobotPos() const { return m_startingRobotPos; }

	CoordinateAndHeading GetSwitchCoordinate() const;
	CoordinateAndHeading GetScaleCoordinate() const;
	CoordinateAndHeading GetCubeCoordinate(Position position) const;

	static CoordinateAndHeading GetStartingRobotCoordinate() { return m_startingRobotCoord; }
	static void SetStartingRobotCoordinate(Position pos, CoordinateAndHeading coord);

private:
	bool m_initialized;
	Position m_switchPos;
	Position m_scalePos;
	static Position m_startingRobotPos;
	static CoordinateAndHeading m_startingRobotCoord;
};

FieldOrientation GetFieldOrientation();

#endif
