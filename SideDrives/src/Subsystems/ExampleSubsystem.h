#ifndef EXAMPLE_SUBSYSTEM_H
#define EXAMPLE_SUBSYSTEM_H

#include <Commands/Subsystem.h>

class ExampleSubsystem: public frc::Subsystem {
public:
	ExampleSubsystem();
	void InitDefaultCommand() override;
	static ExampleSubsystem* getInstance();

private:
	static ExampleSubsystem* m_instance;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
};

#endif  // EXAMPLE_SUBSYSTEM_H
