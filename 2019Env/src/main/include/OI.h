/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotMap.h"
#include <frc/WPILib.h>
#include <frc/Joystick.h>

using namespace frc;

class OI {
	public:
		static OI* GetInstance();
		Joystick* stickL;
		Joystick* stickR;
		Joystick* gamepad;
	private:
		OI();
		static OI* m_instance;
};
