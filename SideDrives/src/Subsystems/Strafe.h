#ifndef STRAFE_H
#define STRAFE_H

#include <Commands/PIDSubsystem.h>
#include <ctre/Phoenix.h>
#include <AHRS.h>
#include "SideDrive.h"

class Strafe : public Subsystem, public SideDrive{
private:

	Strafe();
	static Strafe* m_instance;

	const int RATIO_ENCODER_RES = 128;//TODO: Insert Correct Number

	WPI_TalonSRX* m_frontLeft;
	WPI_TalonSRX* m_frontRight;
	WPI_TalonSRX* m_rearLeft;
	WPI_TalonSRX* m_rearRight;
	WPI_TalonSRX* m_strafe;

	SpeedControllerGroup* drive_l;
	SpeedControllerGroup* drive_r;

	//AHRS* m_navX;

	//RobotDrive* m_drive;

	//bool m_bNavXPresent;

public:
	static Strafe* GetInstance(){
		if(!m_instance) m_instance = new Strafe();
		return m_instance;
	}
	~Strafe();

	virtual void DriveCartesian(float x, float y, float rotate, bool squaredInputs = false, float gyro=0.0);

	virtual void DrivePolar(float m, float theta, float rotate, bool squaredInputs = false);
};

#endif  // Strafe_H
