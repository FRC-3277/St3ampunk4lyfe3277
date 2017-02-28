// Borrowed from https://www.chiefdelphi.com/forums/showthread.php?t=143688
#include "WPILib.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include "CameraSwap.h"
#include "../RobotMap.h"
#include "../Commands/OperatorInputCameraSwitch.h"

CameraSwap::CameraSwap() : Subsystem("CameraSwap") {
	cameraForward = CameraServer::GetInstance()->StartAutomaticCapture(deviceIdCameraForward);
	cameraReverse = CameraServer::GetInstance()->StartAutomaticCapture(deviceIdCameraReverse);
	//Start low resolution to save on bandwidth.
	cameraForward.SetResolution(lowResolutionX, lowResolutionY);
	cameraReverse.SetResolution(lowResolutionX, lowResolutionY);
	cameraForward.SetFPS(framesPerSec);
	cameraReverse.SetFPS(framesPerSec);
}

void CameraSwap::InitDefaultCommand() {
}

// little to no value.
void CameraSwap::SwapCameraView() {

	if (swapCamera) {
		swapCamera = false;
	}
	else if (!swapCamera) {
		swapCamera = true;
	}
}

void CameraSwap::GetCamera() {
	cvSinkForward = CameraServer::GetInstance()->GetVideo("USB Camera Forward");
	cvSinkReverse = CameraServer::GetInstance()->GetVideo("USB Camera Reverse");
	cvSource = CameraServer::GetInstance()->PutVideo("Current View", highResolutionX, highResolutionY);

		while(true) {
			if (swapCamera) {
				if(swapCameraOneTimeAction)
				{
					swapCameraOneTimeAction = false;
					//Lower the opposite camera to save on bandwidth
					cameraReverse.SetResolution(lowResolutionX, lowResolutionY);
					//Raise current camera resolution
					cameraForward.SetResolution(highResolutionX, highResolutionY);
				}
				cvSinkForward.GrabFrame(source);
				//This is temporary awaiting addition of OpenCV manipulation
				output = source;
				//cvtColor(sourceForward, outputForward, cv::COLOR_BGR2GRAY);
			}
			else if (!swapCamera) {
				if(swapCameraOneTimeAction)
				{
					swapCameraOneTimeAction = false;
					//Lower the opposite camera to save on bandwidth
					cameraForward.SetResolution(lowResolutionX, lowResolutionY);
					//Raise current camera resolution
					cameraReverse.SetResolution(highResolutionX, highResolutionY);
				}
				cvSinkReverse.GrabFrame(source);
				output = source;
				//cvtColor(sourceForward, outputForward, cv::COLOR_BGR2GRAY);

			}

			cvSource.PutFrame(output);
		}
}

void CameraSwap::SetJustSwappedOneTimeAction()
{
	swapCameraOneTimeAction = true;
}
