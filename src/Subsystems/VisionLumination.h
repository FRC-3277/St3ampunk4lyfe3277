#ifndef VisionLumination_H
#define VisionLumination_H

#include "./LumberJack.h"
#include "Commands/Subsystem.h"
#include "WPILib.h"

class VisionLumination : public Subsystem {
private:
	std::shared_ptr<Relay> visionSpike;
	std::shared_ptr<LumberJack> lumberJack;

public:
	VisionLumination();
	void InitDefaultCommand();

	void VisionOn();
	void VisionOff();
};

#endif  // VisionLumination_H
