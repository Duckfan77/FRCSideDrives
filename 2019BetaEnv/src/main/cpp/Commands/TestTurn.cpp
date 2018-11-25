/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/TestTurn.h"

TestTurn::TestTurn() {
	Requires(SwerveDrive::getInstance());
}

// Called just before this Command runs the first time
void TestTurn::Initialize() {
	std::cout<<"TestTurnInit"<<std::endl;
	SwerveDrive::getInstance()->setTurnLock(!SwerveDrive::getInstance()->isTurnLocked());
}

// Called repeatedly when this Command is scheduled to run
void TestTurn::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool TestTurn::IsFinished() { return true; }

// Called once after isFinished returns true
void TestTurn::End() 
{
	//SwerveDrive::getInstance()->setTurnLock(false);
	//SwerveDrive::getInstance()->DriveFieldPolar(0,0,0,false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestTurn::Interrupted() {
	End();
}
