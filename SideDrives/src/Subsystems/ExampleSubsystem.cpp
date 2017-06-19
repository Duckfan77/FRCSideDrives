#include "ExampleSubsystem.h"

#include "../RobotMap.h"

ExampleSubsystem* ExampleSubsystem::getInstance()
{
	if(!m_instance)
		m_instance = new ExampleSubsystem();
	return m_instance;
}

ExampleSubsystem::ExampleSubsystem() :
		frc::Subsystem("ExampleSubsystem") {

}

void ExampleSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

