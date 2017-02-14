#include "VisionLumination.h"
#include "../RobotMap.h"

VisionLumination::VisionLumination() : Subsystem("ExampleSubsystem") {
	visionSpike = RobotMap::visionSpike;
	lumberJack.reset(new LumberJack());
}

void VisionLumination::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void VisionLumination::VisionOn()
{

	visionSpike->Set(Relay::kOn);
}

void VisionLumination::VisionOff()
{
	visionSpike->Set(Relay::kOff);
}
