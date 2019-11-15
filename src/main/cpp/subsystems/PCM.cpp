/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/PCM.h"

PCM::PCM() : Subsystem("PCM")
{
  m_compressor.reset(new frc::Compressor);
  UseCompressor(false);
}

void PCM::InitDefaultCommand() {}

void PCM::UseCompressor(bool useCompressor)
{
  m_compressor->SetClosedLoopControl(useCompressor);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
