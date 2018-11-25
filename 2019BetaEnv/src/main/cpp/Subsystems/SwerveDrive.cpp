/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/SwerveDrive.h"
#include "RobotMap.h"

SwerveDrive::DriveModule::DriveModule(int idAngle, int idDrive, int portZero, float angleOffset, bool invertAngleEncoder)
	:m_angle(new WPI_TalonSRX(idAngle))
	,m_drive(new WPI_TalonSRX(idDrive))
	,m_zero(new DigitalInput(portZero))
	,id(portZero)
	,edgeDet(Toggle<bool>(true,false))
	,zeroed(false)
	,m_angleOffset(angleOffset)
{
	m_angle->ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder,0,10);
	m_angle->ConfigAllowableClosedloopError(0, 100, 10);
	m_angle->ConfigClosedLoopPeakOutput(0,0.8,10);
	m_angle->SetSensorPhase(invertAngleEncoder);
	m_angle->ConfigClosedloopRamp(0.5, 10);
	m_angle->Config_kP(0, Preferences::GetInstance()->GetDouble("Angle P", .2),10);
	m_angle->Config_kI(0, Preferences::GetInstance()->GetDouble("Angle I", 0),10);
	m_angle->Config_kD(0, Preferences::GetInstance()->GetDouble("Angle D", .1),10);

	m_drive->ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder,0,10);
	m_drive->Config_kP(0,.1,10);
	m_drive->Config_kI(0,0,10);
	m_drive->Config_kD(0,.1,10);
}

SwerveDrive::DriveModule::~DriveModule()
{
	delete m_angle;
	delete m_drive;
	delete m_zero;
}

double SwerveDrive::DriveModule::getAngle()
{
	//return m_angle->GetSelectedSensorPosition(0);
	return 2*M_PI*m_angle->GetSelectedSensorPosition(0)/RATIO_ANGLE_COUNTS_PER_REV;
}

void SwerveDrive::DriveModule::setTurnRate(double rate)
{
	m_angle->Set(ControlMode::Velocity, rate/2/M_PI * RATIO_ANGLE_COUNTS_PER_REV);
}

void SwerveDrive::DriveModule::setAngle(double pos)
{
	//m_angle->Set(ControlMode::Position,pos);
	m_angle->Set(ControlMode::Position,(pos/(2*M_PI) * RATIO_ANGLE_COUNTS_PER_REV) + m_angleOffset);
}

bool SwerveDrive::DriveModule::maintainZero()
{
	std::cout<<id<<" state: "<<m_zero->Get()<<std::endl;
	if(edgeDet.fallingEdge(m_zero->Get())){
		std::cout<<id<<" Zeroed!!!"<<std::endl;
		m_angle->SetSelectedSensorPosition(0,0,20);
		zeroed=true;
		return true;
	}
	return false;
}

bool SwerveDrive::DriveModule::setZero()
{
	if(maintainZero()){
		m_angle->Set(ControlMode::PercentOutput, 0);
		return true;
	}
	return false;
}

void SwerveDrive::DriveModule::setDriveSpeed(double pVBus)
{
	m_drive->Set(ControlMode::PercentOutput, pVBus);
}

//-------------------------------------------------------------------------------------------------------//

SwerveDrive::SwerveDrive() : SideDrive("SwerveDrive") 
{
	m_leftFront = new DriveModule(CAN_LEFT_FRONT_ANGLE, CAN_LEFT_FRONT_DRIVE, DIO_LEFT_FRONT_ZERO, 
		Preferences::GetInstance()->GetDouble("FrontLeft Angle Offset",0), true);
	m_leftRear = new DriveModule(CAN_LEFT_REAR_ANGLE, CAN_LEFT_REAR_DRIVE, DIO_LEFT_REAR_ZERO, 
		Preferences::GetInstance()->GetDouble("RearLeft Angle Offset",0), true);
	m_rightFront = new DriveModule(CAN_RIGHT_FRONT_ANGLE, CAN_RIGHT_FRONT_DRIVE, DIO_RIGHT_FRONT_ZERO, 
		Preferences::GetInstance()->GetDouble("FrontRight Angle Offset",0), true);
	m_rightRear = new DriveModule(CAN_RIGHT_REAR_ANGLE, CAN_RIGHT_REAR_DRIVE, DIO_RIGHT_REAR_ZERO, 
		Preferences::GetInstance()->GetDouble("RearRight Angle Offset",0), true);

	m_leftMotors = new SpeedControllerGroup(*m_leftFront->m_drive, *m_leftRear->m_drive);
	m_rightMotors = new SpeedControllerGroup(*m_rightFront->m_drive, *m_rightRear->m_drive);
	m_frontMotors = new SpeedControllerGroup(*m_leftFront->m_drive, *m_rightFront->m_drive);
	m_rearMotors = new SpeedControllerGroup(*m_leftRear->m_drive, *m_rightRear->m_drive);

	m_fwdDrive = new DifferentialDrive(*m_leftMotors, *m_rightMotors);
	m_sideDrive = new DifferentialDrive(*m_frontMotors, *m_rearMotors);

	m_fwdDrive->SetSafetyEnabled(false);
	m_sideDrive->SetSafetyEnabled(false);
}

SwerveDrive::~SwerveDrive()
{
	delete m_leftMotors;
	delete m_rightMotors;
	delete m_frontMotors;
	delete m_rearMotors;

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
	if(m_instance==NULL||m_instance==nullptr) m_instance = new SwerveDrive();
	//std::cout<<"SwerveDrive Instance Got"<<std::endl;
	return m_instance;
}

void SwerveDrive::InitDefaultCommand() {
	SetDefaultCommand(new FieldDrive());
}

bool SwerveDrive::isZeroed()
{
	return m_leftFront->zeroed && m_leftRear->zeroed && m_rightFront->zeroed && m_rightRear->zeroed;
}

void SwerveDrive::maintainZero()
{
	std::cout<<"Maintaining Zero"<<std::endl;
	m_leftFront->maintainZero();
	m_leftRear->maintainZero();
	m_rightFront->maintainZero();
	m_rightRear->maintainZero();
}

void SwerveDrive::setZero()
{
	//std::cout<<"Setting Zero"<<std::endl;
	m_leftFront->setZero();
	m_leftRear->setZero();
	m_rightFront->setZero();
	m_rightRear->setZero();
}

void SwerveDrive::rotateWheels(double vel)
{
	std::cout<<"Rotating Wheels at "<<vel<<std::endl;
	m_leftFront->setTurnRate(vel);
	m_leftRear->setTurnRate(vel);
	m_rightFront->setTurnRate(vel);
	m_rightRear->setTurnRate(vel);
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

void SwerveDrive::setTurnLock(bool lock)
{
	turnLocked=lock;
	if(lock)
	{
		//Set wheels tangent to circle of robot wheel base
		m_leftFront->setAngle(M_PI/4.0);
		m_leftRear->setAngle(-M_PI/4.0);
		m_rightFront->setAngle(-M_PI/4.0);
		m_rightRear->setAngle(M_PI/4.0);
	}else{
		//Set wheels back to front facing
		m_leftFront->setAngle(0);
		m_leftRear->setAngle(0);
		m_rightFront->setAngle(0);
		m_rightRear->setAngle(0);
	}
}

void SwerveDrive::driveTurn(double turn)
{
	std::cout<<"Driving TurnLocked"<<std::endl;
	m_leftFront->setDriveSpeed(-turn);
	m_leftRear->setDriveSpeed(turn);
	m_rightFront->setDriveSpeed(turn);
	m_rightRear->setDriveSpeed(-turn);
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
	}else{
		//std::cout<<"AvgAngle: "<<getAvgWheelAngle()<<std::endl;
		std::cout<<"Driving Normal"<<std::endl;
		
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
}

void SwerveDrive::DriveFieldPolar(float m, float theta, float rotate, bool squaredInputs)
{
	//float actHeading = SideDrive::m_navX->GetYaw()-zeroHeading+theta;
	float actHeading=theta;
	getAvgWheelAngle();
	//actHeading += floor(getAvgWheelAngle()/(2*M_PI));
	std::cout<<"a"<<actHeading<<" "<<m<<" "<<theta<<" "<<rotate<<std::endl;
	std::cout<<"Turn Locked: "<<turnLocked<<std::endl;
	if(0 || std::fabs(m)>Preferences::GetInstance()->GetDouble("m threshold", 0.2) || std::fabs(rotate)>Preferences::GetInstance()->GetDouble("rotate threshold", 0.5)){
		//std::cout<<"Drivingasdf"<<std::endl;
		//float actHeading = SideDrive::m_navX->GetYaw()-zeroHeading+theta;
		//actHeading += floor(getWheelAngle()/(2*M_PI));
		DrivePolar(0.5*m, actHeading, rotate, squaredInputs);
	}else{
		//std::cout<<"Not_Driving"<<std::endl;
		DrivePolar(0,0,0,false);
	}

}

void SwerveDrive::DriveFieldCartesian(float x, float y, float rotate, bool squaredInputs)
{
	float m = std::sqrt(x*x+y*y);
	float theta = (y<0?-1:1) * std::acos(x/m);
	DriveFieldPolar(m, theta, rotate, squaredInputs);
}

float SwerveDrive::getAvgWheelAngle()
{
	std::cout<<m_leftFront->id<<" "<<m_leftFront->getAngle()<<std::endl;
	std::cout<<m_leftRear->id<<" "<<m_leftRear->getAngle()<<std::endl;
	std::cout<<m_rightFront->id<<" "<<m_rightFront->getAngle()<<std::endl;
	std::cout<<m_rightRear->id<<" "<<m_rightRear->getAngle()<<std::endl;
	return (m_leftFront->getAngle()+
			m_leftRear->getAngle()+
			m_rightFront->getAngle()+
			m_rightRear->getAngle())/4;
}

void SwerveDrive::rotateWheelsPVBus(double pVBus)
{
	getInstance()->m_leftFront->m_angle->Set(ControlMode::PercentOutput, pVBus);
	getInstance()->m_leftRear->m_angle->Set(ControlMode::PercentOutput, pVBus);
	getInstance()->m_rightFront->m_angle->Set(ControlMode::PercentOutput, pVBus);
	getInstance()->m_rightRear->m_angle->Set(ControlMode::PercentOutput, pVBus);
}
