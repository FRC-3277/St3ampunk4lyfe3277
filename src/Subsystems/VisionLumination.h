#ifndef VisionLumination_H
#define VisionLumination_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class VisionLumination : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<Relay> visionSpike;

public:
	VisionLumination();
	void InitDefaultCommand();

	void VisionOn();
	void VisionOff();
};

#endif  // VisionLumination_H
