/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/SwerveDrive.h"
#include "RobotMap.h"

SwerveDrive::DriveModule::DriveModule(int idAngle, int idDrive, int portZero)
	:m_angle(new WPI_TalonSRX(idAngle))
	,m_drive(new WPI_TalonSRX(idDrive))
	,m_zero(new DigitalInput(portZero))
{

}

SwerveDrive::DriveModule::~DriveModule()
{
	delete m_angle;
	delete m_drive;
	delete m_zero;
}

void SwerveDrive::DriveModule::setAngle(double pos)
{
	m_angle->Set(ControlMode::Position,(int)pos/(2*M_PI) * RATIO_ANGLE_COUNTS_PER_REV);
}

bool SwerveDrive::DriveModule::setZero()
{

}

void SwerveDrive::DriveModule::setDriveSpeed(double pVBus)
{
	m_drive->Set(ControlMode::PercentOutput, pVBus);
}

//-------------------------------------------------------------------------------------------------------//

SwerveDrive::SwerveDrive() : SideDrive("SwerveDrive") 
{
	m_leftFront = new DriveModule(CAN_LEFT_FRONT_ANGLE, CAN_LEFT_FRONT_DRIVE, DIO_LEFT_FRONT_ZERO);
	m_leftRear = new DriveModule(CAN_LEFT_REAR_ANGLE, CAN_LEFT_REAR_DRIVE, DIO_LEFT_REAR_ZERO);
	m_rightFront = new DriveModule(CAN_RIGHT_FRONT_ANGLE, CAN_RIGHT_FRONT_DRIVE, DIO_RIGHT_FRONT_ZERO);
	m_rightRear = new DriveModule(CAN_RIGHT_REAR_ANGLE, CAN_RIGHT_REAR_DRIVE, DIO_RIGHT_REAR_ZERO);

	m_leftMotors = new SpeedControllerGroup(*m_leftFront->m_drive, *m_leftRear->m_drive);
	m_rightMotors = new SpeedControllerGroup(*m_rightFront->m_drive, *m_rightRear->m_drive);
	m_frontMotors = new SpeedControllerGroup(*m_leftFront->m_drive, *m_rightFront->m_drive);
	m_rearMotors = new SpeedControllerGroup(*m_leftRear->m_drive, *m_rightRear->m_drive);

	m_fwdDrive = new DifferentialDrive(*m_leftMotors, *m_rightMotors);
	m_sideDrive = new DifferentialDrive(*m_frontMotors, *m_rearMotors);
}

SwerveDrive::~SwerveDrive()
{
	delete m_leftMotors;
	delete m_rightMotors;
	delete m_frontMotors;
	delete m_rearMotors;

	delete m_fwdDrive;
	delete m_sideDrive;
}

SwerveDrive* SwerveDrive::m_instance = NULL;

SwerveDrive* SwerveDrive::getInstance()
{
	if(!m_instance) m_instance = new SwerveDrive();
	return m_instance;
}

void SwerveDrive::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void SwerveDrive::zeroMotors()
{
	m_leftFront->setZero();
	m_leftRear->setZero();
	m_rightFront->setZero();
	m_rightRear->setZero();
}

DifferentialDrive* SwerveDrive::getDrive(int itheta)
{
	//Get drive closest to being parallel to direction of travel
	itheta%=180;
	//In this band, closest to sideDrive, outside, closest to fwdDrive
	if(itheta>45 && itheta<90+45){
		return m_sideDrive;
	}
	return m_fwdDrive;
}

void SwerveDrive::driveTurn(double turn)
{
	m_leftFront->setDriveSpeed(turn);
	m_leftRear->setDriveSpeed(turn);
	m_rightFront->setDriveSpeed(turn);
	m_rightRear->setDriveSpeed(turn);
}

void SwerveDrive::DriveCartesian(float x, float y, float rotate, bool squaredInputs)
{
	//Easier to control as polar
	CartesianToPolar(x,y,rotate,squaredInputs);
}

void SwerveDrive::DrivePolar(float m, float theta, float rotate, bool squaredInputs)
{
	if(turnLocked){
		return driveTurn(rotate);
	}
	m_leftFront->setAngle(theta);
	m_leftRear->setAngle(theta);
	m_rightFront->setAngle(theta);
	m_rightRear->setAngle(theta);

	int itheta = (int)(theta*180/M_PI);

	//If in this band, the drive is going to have left and right reversed relative to what we want, so flip them
	itheta%=360;
	if(itheta > 90+45 && itheta<360-45){
		rotate*=-1;
	}

	//Get optimal drive, and drive using it
	getDrive(theta)->ArcadeDrive(m,rotate,squaredInputs);
}
