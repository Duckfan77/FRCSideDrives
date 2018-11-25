/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/TestDrive.h"

TestDrive::TestDrive() {
  // Use Requires() here to declare subsystem dependencies
  Requires(SwerveDrive::getInstance());
}

// Called just before this Command runs the first time
void TestDrive::Initialize() 
{
  SwerveDrive::getInstance()->DriveFieldPolar(.3,0,.2,false);
}

// Called repeatedly when this Command is scheduled to run
void TestDrive::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool TestDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void TestDrive::End() 
{
  SwerveDrive::getInstance()->DriveFieldPolar(0,0,0,false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestDrive::Interrupted() {}
