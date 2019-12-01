/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotMap.h"
#include <WPILib.h>
#include "Commands/ZeroDrive.h"
#include "Commands/TestTurn.h"
#include "Commands/TestDrive.h"
#include "Commands/TurnLock.h"

class OI {
	public:
		static OI* GetInstance();
		Joystick* gamepad;
		JoystickButton* zero;
		JoystickButton* l_btn_10;
		JoystickButton* r_btn_10;
		JoystickButton* turnLock;
	private:
		OI();
		static OI* m_instance;
};
