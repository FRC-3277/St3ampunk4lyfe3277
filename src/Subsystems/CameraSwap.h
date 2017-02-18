#ifndef CameraSwap_H
#define CameraSwap_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "./RobotMap.h"
#include "LumberJack.h"

class CameraSwap : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	CameraSwap();
	void InitDefaultCommand();

	bool SwapCamera = true;

	void SwapCameraView();
	void GetCamera();
};

#endif  // CameraSwap_H
