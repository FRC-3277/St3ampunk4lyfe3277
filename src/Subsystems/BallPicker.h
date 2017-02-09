#ifndef BALLPICKER_H
#define BALLPICKER_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class BallPicker: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<CANTalon> pickerTalon;

public:
	BallPicker();
	void InitDefaultCommand();

	void FuelRiserBeltOn();
	void FuelRiserBeltOff();
};

#endif
