#ifndef FIELDORIENTATION_H
#define FIELDORIENTATION_H

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

class FieldOrientation
{
public:
	constexpr static double FieldWidth = 8.23; // Meters
	constexpr static double StartCoordX = 1.2; // Meters from side
	constexpr static double StartCoordY = 0.5; // Meters from back wall
	constexpr static double StartCoordHeading = 0; // Degrees

	FieldOrientation();
	FieldOrientation(const FieldOrientation&) = default;

	bool IsInitialized() const { return m_initialized; }

	Position GetSwitchPos() const { return m_switchPos; }
	Position GetScalePos() const { return m_scalePos; }
	Position GetStartingRobotPos() const { return m_startingRobotPos; }

	CoordinateAndHeading GetSwitchCoordinate() const;
	CoordinateAndHeading GetScaleCoordinate() const;

	static CoordinateAndHeading GetStartingRobotCoordinate() { return m_startingRobotCoord; }
	static void SetStartingRobotCoordinate(CoordinateAndHeading coord);

private:
	bool m_initialized;
	Position m_switchPos;
	Position m_scalePos;
	Position m_startingRobotPos;
	static CoordinateAndHeading m_startingRobotCoord;
};

FieldOrientation GetFieldOrientation();

#endif
