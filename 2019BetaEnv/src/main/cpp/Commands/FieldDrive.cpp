/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/FieldDrive.h"
#include <iostream>

FieldDrive::FieldDrive() {
	Requires(SwerveDrive::getInstance());
}

// Called just before this Command runs the first time
void FieldDrive::Initialize() {std::cout<<"FieldDriveStarting"<<std::endl;}

// Called repeatedly when this Command is scheduled to run
void FieldDrive::Execute() 
{
	//Verify Axis Numbers
	double driveX = -OI::GetInstance()->stickL->GetRawAxis(0);
	double driveY = -OI::GetInstance()->stickL->GetRawAxis(1);
	double rotate = -OI::GetInstance()->stickR->GetRawAxis(0);
	//std::cout<<driveX<<" "<<driveY<<" "<<rotate<<std::endl;
	
	SwerveDrive::getInstance()->DriveFieldCartesian(driveX, driveY, rotate, true);
}

// Make this return true when this Command no longer needs to run execute()
bool FieldDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void FieldDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FieldDrive::Interrupted() {End();}
