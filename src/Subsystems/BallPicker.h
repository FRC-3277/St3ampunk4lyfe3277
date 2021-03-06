#ifndef BALLPICKER_H
#define BALLPICKER_H
#include "./LumberJack.h"
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "./RobotMap.h"

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
	std::shared_ptr<LumberJack> lumberJack;

	// Localized versions of talon calibration and encoder
	const float FULL_SPEED_FROM_TALONS=	RobotMap::FULL_SPEED_FROM_TALONS_BASE;
	const float TALON_FTERM_L = 		RobotMap::TALON_FTERM_L_BASE;
	const float TALON_PTERM_L = 		RobotMap::TALON_PTERM_L_BASE;
	const float TALON_ITERM_L = 		RobotMap::TALON_ITERM_L_BASE;
	const float TALON_DTERM_L = 		RobotMap::TALON_DTERM_L_BASE;
	const float TALON_FTERM_R = 		RobotMap::TALON_FTERM_R_BASE;
	const float TALON_PTERM_R = 		RobotMap::TALON_PTERM_R_BASE;
	const float TALON_ITERM_R = 		RobotMap::TALON_ITERM_R_BASE;
	const float TALON_DTERM_R = 		RobotMap::TALON_DTERM_R_BASE;
	const float TALON_MAXRAMP =			RobotMap::TALON_MAXRAMP_BASE;
	const float TALON_IZONE	=			RobotMap::TALON_IZONE_BASE;
	const float TALON_COUNTS_PER_REV =	RobotMap::TALON_COUNTS_PER_REV_BASE;
	const float REVS_PER_FOOT = 		RobotMap::REVS_PER_FOOT_BASE;
	const double METERS_PER_COUNT = 	RobotMap::METERS_PER_COUNT_BASE;


public:
	BallPicker();
	void InitDefaultCommand();

	void FuelRiserBeltOn();
	void FuelRiserBeltOff();
	void AutonomousPicker();
};

#endif
