/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/ZeroDrive.h"

ZeroDrive::ZeroDrive() {
	Requires(SwerveDrive::getInstance());
}

// Called just before this Command runs the first time
void ZeroDrive::Initialize() 
{
	SwerveDrive::getInstance()->rotateWheels(.2);
}

// Called repeatedly when this Command is scheduled to run
void ZeroDrive::Execute() 
{
	SwerveDrive* SwerveDrive = SwerveDrive::getInstance();
	SwerveDrive->setZero();	
}

// Make this return true when this Command no longer needs to run execute()
bool ZeroDrive::IsFinished() { return SwerveDrive::getInstance()->isZeroed(); }

// Called once after isFinished returns true
void ZeroDrive::End() {
	SwerveDrive::getInstance()->DrivePolar(0,0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ZeroDrive::Interrupted() {
	End();
}
