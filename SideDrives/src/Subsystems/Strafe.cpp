#include "Strafe.h"
#include "../RobotMap.h"

Strafe* Strafe::GetInstance()
{
	if(!m_instance) m_instance = new Strafe();
	return m_instance;
}

Strafe::Strafe() : Subsystem("Strafe")
{
	m_frontLeft = new CANTalon(0);
	m_frontRight = new CANTalon(0);
	m_rearLeft = new CANTalon(0);
	m_rearRight = new CANTalon(0);
	m_strafe = new CANTalon(0);

	m_frontLeft->ConfigEncoderCodesPerRev(RATIO_ENCODER_RES);
	m_frontRight->ConfigEncoderCodesPerRev(RATIO_ENCODER_RES);

	m_drive = new RobotDrive(m_frontLeft, m_frontRight, m_rearLeft, m_rearRight);

	try{
		//Connect to navX Gyro on MXP port.
		m_navX = new AHRS(SPI::Port::kMXP);
		m_bNavXPresent = true;
	} catch (std::exception &ex){
		//If connection fails log the error and fall back to encoder based angle handling.
		std::string str_error = "Error instantiating navX from MXP: ";
		str_error += ex.what();
		DriverStation::ReportError(str_error.c_str());
		m_bNavXPresent = false;
	}
}

Strafe::~Strafe()
{
	delete m_frontLeft;
	delete m_frontRight;
	delete m_rearLeft;
	delete m_rearRight;
	delete m_strafe;
	delete m_drive;
	delete m_navX;
}

void Strafe::DriveCartesian(float x, float y, float rotate, bool squaredInputs, float gyro)
{
	m_strafe->Set(y);
	m_drive->ArcadeDrive(x, rotate, squaredInputs);
}

void Strafe::DrivePolar(float m, float theta, float rotate, bool squaredInputs)
{
	SideDrive::PolarToCartesian(m, theta, rotate, squaredInputs);
}
