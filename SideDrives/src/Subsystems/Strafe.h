#ifndef STRAFE_H
#define STRAFE_H

#include <Commands/PIDSubsystem.h>
#include <CANTalon.h>
#include <AHRS.h>

class Strafe : public PIDSubsystem, public SideDrive{
private:

	const int RATIO_ENCODER_RES = 128;//TODO: Insert Correct Number

	CANTalon* m_frontLeft;
	CANTalon* m_frontRight;
	CANTalon* m_rearLeft;
	CANTalon* m_rearRight;
	CANTalon* m_strafe;

	AHRS* m_navX;

	RobotDrive* m_drive;

	bool m_bNavXPresent;

public:
	Strafe();
	~Strafe();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();

	virtual void DriveCartesian(float x, float y, float rotate, bool squaredInputs = false, float gyro=0.0);

	virtual void DrivePolar(float m, float theta, float rotate, bool squaredInputs = false);
};

#endif  // Strafe_H
