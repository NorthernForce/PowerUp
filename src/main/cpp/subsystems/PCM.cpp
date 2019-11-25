/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/PCM.h"
#include "Robot.h"
#include "RobotMap.h"

PCM::PCM() :
 Subsystem("PCM") {
    m_compressor.reset(new frc::Compressor(RobotMap::PCM::k_pcm_id));
    UseCompressor(true);
}

void PCM::UseCompressor(bool useCompressor) {
    m_compressor->SetClosedLoopControl(useCompressor);
}

void PCM::InitDefaultCommand() {}

// Put methods for controlling this subsystem
// here. Call these from Commands.
