#include "Strafe.h"

#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SmartDashboard.h>

#include "../RobotMap.h"

Strafe::Strafe() : PIDSubsystem("Strafe", 1.0, 0.0, 0.0)
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

double Strafe::ReturnPIDInput() {
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;
}

void Strafe::UsePIDOutput(double output) {
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
}

void Strafe::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
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
