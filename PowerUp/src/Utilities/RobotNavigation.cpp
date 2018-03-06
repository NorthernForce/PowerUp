#include "RobotNavigation.h"

namespace {
	RobotNavigation::RobotTrajectory CombineTrajectories(const std::vector<RobotNavigation::RobotTrajectory>& items) {
		std::vector<Profile> leftProfiles;
		std::vector<Profile> rightProfiles;
		for (const auto& item : items) {
			leftProfiles.push_back(item.m_left);
			rightProfiles.push_back(item.m_right);
		}
		return RobotNavigation::RobotTrajectory({
			CombineProfiles(std::move(leftProfiles)),
			CombineProfiles(std::move(rightProfiles))
		});
	}
}

RobotNavigation::RobotNavigation(const FieldOrientation& orientation) : m_fieldOrientation(orientation) {
}

RobotNavigation::RobotTrajectory RobotNavigation::CreatePath(const Position from, const Position to) const {
	if (from == Position::StartingPos && to == Position::ScoreOnSwitch) {
		return CreatePathFromStartToSwitch();
	} else if (from == Position::StartingPos && to == Position::ScoreOnScale) {
		return CreatePathFromStartToScale();
	}
	else {
		return {};
	}
}

RobotNavigation::RobotTrajectory RobotNavigation::CreatePathFromStartToSwitch() const {
	const auto vector = m_fieldOrientation.GetSwitchCoordinate() - m_fieldOrientation.GetStartingRobotCoordinate();
	return CombineTrajectories({
		CreateProfile(vector.y, 0, 0, 0),
		CreateProfile(0, 0, 0, vector.heading),
		CreateProfile(vector.x, 0, 0, 0),
	});
}

RobotNavigation::RobotTrajectory RobotNavigation::CreatePathFromStartToScale() const {
	//const auto vector = m_fieldOrientation.GetScaleCoordinate() - m_fieldOrientation.GetStartingRobotCoordinate();
	const auto firstTurn = 4.29;
	if (m_fieldOrientation.GetStartingRobotPos() == m_fieldOrientation.GetScalePos()) {
		const auto angle = m_fieldOrientation.GetScalePos() == ::Position::Left ? 26.46 : -26.46;
		return CombineTrajectories({
			CreateProfile(firstTurn, 0, maxVelocity, 0),
			CreateProfile(0.5, maxVelocity, maxVelocity, angle),
			CreateProfile(0.5, maxVelocity, maxVelocity, -angle),
			CreateProfile(0.5, maxVelocity, 0, 0),
		});
	} else {
		return CombineTrajectories({
			CreateProfile(firstTurn, 0, maxVelocity, 0),
			CreateProfile(0.5, maxVelocity, maxVelocity, 20),
			CreateProfile(0.5, maxVelocity, maxVelocity, -20),
			CreateProfile(0.5, maxVelocity, 0, 0),
		});
	}
}

/**
 * Creates a profile to move the robot along a specified path
 */
RobotNavigation::RobotTrajectory RobotNavigation::CreateProfile(const double distance, const double startVelocity, const double finalVelocity, const double angleDegrees) {
	if (angleDegrees == 0) {
		const auto profile = CreateComplexProfile(distance, startVelocity, finalVelocity, maxVelocity, timeToMaxSpeed);
		return RobotTrajectory { profile, profile };
	}
    const auto outsideDistance = distance + std::abs(angleDegrees) / 360 * M_PI * wheelTrack;
    const auto outsideProfile = CreateComplexProfile(outsideDistance, startVelocity, finalVelocity, maxVelocity, timeToMaxSpeed);
    // There is probably a better way to calculate the target velocity for the inside wheels than this
    const auto insideDistance = distance - std::abs(angleDegrees) / 360 * M_PI * wheelTrack;
    auto vMax = maxVelocity;
    auto vMin = 0.0;
    while (true) {
        const auto insideProfile = CreateComplexProfile(insideDistance, startVelocity, finalVelocity, (vMax + vMin) / 2, timeToMaxSpeed);
        if (std::abs(insideProfile.m_duration - outsideProfile.m_duration) < 0.01) {
            if (angleDegrees > 0) {
                return { outsideProfile, insideProfile };
            } else {
                return{ insideProfile, outsideProfile };
            }
        }
        if (insideProfile.m_duration > outsideProfile.m_duration) {
            vMin = (vMax + vMin) / 2;
        }
        else {
            vMax = (vMax + vMin) / 2;
        }
    }
}
