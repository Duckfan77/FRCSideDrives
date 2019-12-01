/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/RobotDrive.h"

cDrive::RobotDrive::RobotDrive() : frc::Command(){
	Requires(SwerveDrive::getInstance());
	OI::GetInstance();
}

// Called just before this Command runs the first time
void cDrive::RobotDrive::Initialize()
{
	SwerveDrive::getInstance()->setTurnLock(false);
}

// Called repeatedly when this Command is scheduled to run
void cDrive::RobotDrive::Execute()
{
	//Verify Axis Numbers
	double driveX = -OI::GetInstance()->gamepad->GetRawAxis(0);
	double driveY = OI::GetInstance()->gamepad->GetRawAxis(1);
	double rotate = -OI::GetInstance()->gamepad->GetRawAxis(4);
	SwerveDrive::getInstance()->DriveCartesian(driveX, driveY, rotate, true);
}

// Make this return true when this Command no longer needs to run execute()
bool cDrive::RobotDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void cDrive::RobotDrive::End() 
{
	SwerveDrive::getInstance()->DriveCartesian(0,0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void cDrive::RobotDrive::Interrupted() 
{
	End();
}
