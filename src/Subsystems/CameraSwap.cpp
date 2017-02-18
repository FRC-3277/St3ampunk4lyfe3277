#include "CameraSwap.h"
#include "../RobotMap.h"

CameraSwap::CameraSwap() : Subsystem("CameraSwap") {

}

void CameraSwap::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void CameraSwap::SwapCameraView() {

	if (SwapCamera) {
		SwapCamera = false;
	}
	else if (!SwapCamera) {
		SwapCamera = true;
	}
}

void CameraSwap::GetCamera() {
	if (SwapCamera) {
		//cs::UsbCamera cam0 = CameraServer::GetInstance()->StartAutomaticCapture(0);
	}
	else if (!SwapCamera) {
		//cs::UsbCamera cam1 = CameraServer::GetInstance()->StartAutomaticCapture(1);
	}
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
