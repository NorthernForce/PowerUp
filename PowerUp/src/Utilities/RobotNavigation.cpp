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
    // When not turning we use the same profile for both left and right sides
	if (angleDegrees == 0) {
		const auto profile = CreateComplexProfile(distance, startVelocity, finalVelocity, maxVelocity, timeToMaxSpeed);
		return RobotTrajectory { profile, profile };
	}

    // Determine the inside and outside travel distances
    const auto outsideDistance = distance + std::abs(angleDegrees) / 360 * M_PI * wheelTrack;
    const auto insideDistance = distance - std::abs(angleDegrees) / 360 * M_PI * wheelTrack;

    // Determine the approx average velocity and the duration of the two profiles
    // Note each profile will comprise of 4 equal duration sections, each a multiple of 10ms, so the whole
    // profile must be a multiple of 40ms
    const auto avgVelocity = startVelocity == 0 && finalVelocity == 0 ? maxVelocity / 2 : (startVelocity + finalVelocity) / 2;
    const auto duration = RoundProfileDuration(outsideDistance / avgVelocity, TrajectoryDuration::TrajectoryDuration_40ms);

    // Determine the outside target velocity midway through the turn
    const auto outsideTargetVelocity = 2 * outsideDistance / duration - (startVelocity + finalVelocity) / 2;
    auto outsideProfile = CombineProfiles({
        CreateSimpleProfile((startVelocity + outsideTargetVelocity) * duration / 4, startVelocity, outsideTargetVelocity),
        CreateSimpleProfile((outsideTargetVelocity + finalVelocity) * duration / 4, outsideTargetVelocity, finalVelocity)
    });

    // Determine the inside target velocity midway through the turn
    const auto insideTargetVelocity = 2 * insideDistance / duration - (startVelocity + finalVelocity) / 2;
    auto insideProfile = CombineProfiles({
        CreateSimpleProfile((startVelocity + insideTargetVelocity) * duration / 4, startVelocity, insideTargetVelocity),
        CreateSimpleProfile((insideTargetVelocity + finalVelocity) * duration / 4, insideTargetVelocity, finalVelocity)
    });

    // Verify the profiles seem reasonable
    assert(std::abs(insideProfile.m_duration - outsideProfile.m_duration) < 1e-3);
    assert(std::abs(insideProfile.m_distance - insideDistance) < 1e-3);
    assert(std::abs(outsideProfile.m_distance - outsideDistance) < 1e-3);

    if (angleDegrees > 0) {
        return { std::move(outsideProfile), std::move(insideProfile) };
    } else {
        return{ std::move(insideProfile), std::move(outsideProfile) };
    }
}
