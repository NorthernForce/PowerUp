//Not currently being used

#include "ctre/Phoenix.h"
#include "PCM.h"
#include "../RobotMap.h"

PCM::PCM() : frc::Subsystem("PCM") {
	//TODO: fix name
    pCM = RobotMap::compressor;
}

void PCM::InitDefaultCommand() {
}

void PCM::Periodic() {
}
