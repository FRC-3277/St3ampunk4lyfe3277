#ifndef CameraSwap_H
#define CameraSwap_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "./RobotMap.h"
#include "LumberJack.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

class CameraSwap : public Subsystem {
private:
	cs::UsbCamera cameraForward, cameraReverse;
	cs::CvSink cvSinkForward, cvSinkReverse;
	cs::CvSource cvSource;
	cv::Mat source, output;
	int deviceIdCameraForward = 0;
	int deviceIdCameraReverse = 1;
	int highResolutionX = 640;
	int highResolutionY = 480;
	int lowResolutionX = 320;
	int lowResolutionY = 240;
	int framesPerSec = 20;

	bool swapCamera = true;
	bool swapCameraOneTimeAction = false;

public:
	CameraSwap();
	void InitDefaultCommand();

	void SwapCameraView();
	void GetCamera();
	void SetJustSwappedOneTimeAction();
};

#endif  // CameraSwap_H
