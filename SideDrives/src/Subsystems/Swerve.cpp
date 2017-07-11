#include "Swerve.h"
#include "../RobotMap.h"

Swerve::Swerve() : Subsystem("ExampleSubsystem")
{
	m_frontLeftDrive = new CANTalon(0);
	m_frontRightDrive = new CANTalon(0);
	m_rearLeftDrive = new CANTalon(0);
	m_rearRightDrive = new CANTalon(0);

	m_frontLeftDrive->ConfigEncoderCodesPerRev(RATIO_DRIVE_ENCODER_RES);
	m_frontRightDrive->ConfigEncoderCodesPerRev(RATIO_DRIVE_ENCODER_RES);

	m_frontLeftTurn = new CANTalon(1);
	m_frontRightTurn = new CANTalon(2);
	m_rearLeftTurn = new CANTalon(3);
	m_rearRightTurn = new CANTalon(4);

	m_frontRightTurn->SetControlMode(CANTalon::ControlMode::kFollower);
	m_rearLeftTurn->SetControlMode(CANTalon::ControlMode::kFollower);
	m_rearRightTurn->SetControlMode(CANTalon::ControlMode::kFollower);

	m_frontRightTurn->Set(1);//m_frontLeftTurn CAN ID
	m_rearLeftTurn->Set(1);//m_frontLeftTurn CAN ID
	m_rearRightTurn->Set(1);//m_frontLeftTurn CAN ID

	m_TurnControl->ConfigEncoderCodesPerRev(RATIO_TURN_ENCODER_RES);

	m_drive = new RobotDrive(m_frontLeftDrive, m_rearLeftDrive, m_frontRightDrive, m_rearRightDrive);

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

Swerve::~Swerve()
{
	delete m_frontLeftDrive;
	delete m_frontRightDrive;
	delete m_rearLeftDrive;
	delete m_rearRightDrive;

	delete m_frontLeftTurn;
	delete m_frontRightTurn;
	delete m_rearLeftTurn;
	delete m_rearRightTurn;

	delete m_drive;
	delete m_navX;
}

void Swerve::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void Swerve::SetTalonPID()
{
	m_TurnControl->SetPID(1,0,0);//TODO: TUNE PID
	m_TurnControl->SetControlMode(CANTalon::ControlMode::kPosition);
}

void Swerve::DriveCartesian(float x, float y, float rotate, bool squaredInputs = false, float gyro=0.0)
{
	SideDrive::CartesianToPolar(x, y, rotate, squaredInputs, gyro);
}

void Swerve::DrivePolar(float m, float theta, float rotate, bool squaredInputs = false)
{
	SetTalonPID();
	m_TurnControl->Set(theta);
	m_drive->ArcadeDrive(m, rotate, squaredInputs);
}
