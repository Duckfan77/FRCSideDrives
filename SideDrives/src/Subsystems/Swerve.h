#ifndef SWERVE_H
#define SWERVE_H

#include <Commands/PIDSubsystem.h>
#include <CANTalon.h>
#include <AHRS.h>
#include "SideDrive.h"
#define m_frontLeftTurn m_TurnControl

class Swerve : public Subsystem, public SideDrive{
private:

	Swerve();
	static Swerve* m_instance;

	const int RATIO_DRIVE_ENCODER_RES = 128;//TODO: Insert Correct Number
	const int RATIO_TURN_ENCODER_RES = 256;//TODO: Insert Correct Number

	CANTalon* m_frontLeftDrive;
	CANTalon* m_frontRightDrive;
	CANTalon* m_rearLeftDrive;
	CANTalon* m_rearRightDrive;

	CANTalon* m_frontLeftTurn; //Also known as m_TurnControl
	CANTalon* m_frontRightTurn;
	CANTalon* m_rearLeftTurn;
	CANTalon* m_rearRightTurn;

	AHRS* m_navX;

	RobotDrive* m_drive;

	bool m_bNavXPresent;

	void SetTalonPID();

public:
	static Swerve* GetInstance();
	~Swerve();
	void InitDefaultCommand();

	virtual void DriveCartesian(float x, float y, float rotate, bool squaredInputs = false, float gyro=0.0);
	virtual void DrivePolar(float m, float theta, float rotate, bool squaredInputs = false);
};

#endif  // Swerve_H
