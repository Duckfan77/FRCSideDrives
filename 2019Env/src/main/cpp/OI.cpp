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
	gamepad = new Joystick(CONTROLLER_GAMEPAD);
	zero = new JoystickButton(gamepad, 8);      //Start
	turnLock = new JoystickButton(gamepad, 6);  //R Bumper
	//l_btn_10 = new JoystickButton(gamepad, 10);
	//r_btn_10 = new JoystickButton(gamepad, 10);

	zero->WhenPressed(new ZeroDrive());
	//l_btn_10->ToggleWhenPressed(new TestTurn());
	//r_btn_10->ToggleWhenPressed(new TestDrive());
	turnLock->ToggleWhenPressed(new TurnLock());
}
