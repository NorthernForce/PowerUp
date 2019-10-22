//Not currently being used

#ifndef PCM_H
#define PCM_H
#include "frc/commands/Subsystem.h"
#include "frc/WPILib.h"

class PCM: public frc::Subsystem {
private:
	//TODO: fix name
	std::shared_ptr<frc::Compressor> pCM;
public:
	PCM();
	void InitDefaultCommand() override;
	void Periodic() override;
};

#endif //PCM_H
