/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <WPILib.h>

OI* OI::m_instance = NULL;

OI* OI::GetInstance()
{
	if(!m_instance)
		m_instance=new OI();
	return m_instance;
}

OI::OI() {
	stickL = new Joystick(CONTROLLER_STICK_L);
	stickR = new Joystick(CONTROLLER_STICK_R);
	gamepad = new Joystick(CONTROLLER_GAMEPAD);
	zero = new JoystickButton(stickL, 3);
	l_btn_10 = new JoystickButton(stickL, 10);
	r_btn_10 = new JoystickButton(stickR, 10);

	zero->WhenPressed(new ZeroDrive());
	l_btn_10->WhenPressed(new TestTurn());
	l_btn_10->WhenReleased(new FieldDrive());
}
