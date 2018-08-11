#include "Swerve.h"
#include "../RobotMap.h"

Swerve* Swerve::GetInstance()
{
	if(!m_instance) m_instance = new Swerve();
	return m_instance;
}

Swerve::Swerve() : Subsystem("ExampleSubsystem")
{
	m_frontLeftDrive = new WPI_TalonSRX(0);
	m_frontRightDrive = new WPI_TalonSRX(0);
	m_rearLeftDrive = new WPI_TalonSRX(0);
	m_rearRightDrive = new WPI_TalonSRX(0);

	//m_frontLeftDrive->ConfigEncoderCodesPerRev(RATIO_DRIVE_ENCODER_RES);
	//m_frontRightDrive->ConfigEncoderCodesPerRev(RATIO_DRIVE_ENCODER_RES);

	m_frontLeftTurn = new WPI_TalonSRX(1);
	m_frontRightTurn = new WPI_TalonSRX(2);
	m_rearLeftTurn = new WPI_TalonSRX(3);
	m_rearRightTurn = new WPI_TalonSRX(4);

	m_frontRightTurn->Set(ControlMode::Follower, 1);//m_frontLeftTurn CAN ID
	m_rearLeftTurn->Set(ControlMode::Follower, 1);//m_frontLeftTurn CAN ID
	m_rearRightTurn->Set(ControlMode::Follower, 1);//m_frontLeftTurn CAN ID

	//m_TurnControl->ConfigEncoderCodesPerRev(RATIO_TURN_ENCODER_RES);

	drive_l=new SpeedControllerGroup(m_frontLeftDrive, m_rearLeftDrive);
	drive_r=new SpeedControllerGroup(m_frontRightDrive, m_rearRightDrive);

	m_drive = new DifferentialDrive(drive_l, drive_r);

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

	delete drive_l;
	delete drive_r;
}

void Swerve::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void Swerve::SetTalonPID()
{
	/*
	m_TurnControl->SetPID(1,0,0);//TODO: TUNE PID
	m_TurnControl->SetControlMode(WPI_TalonSRX::ControlMode::kPosition);*/
}

void Swerve::DriveCartesian(float x, float y, float rotate, bool squaredInputs, float gyro)
{
	SideDrive::CartesianToPolar(x, y, rotate, squaredInputs, gyro);
}

void Swerve::DrivePolar(float m, float theta, float rotate, bool squaredInputs)
{
	SetTalonPID();
	m_TurnControl->Set(theta);
	m_drive->ArcadeDrive(m, rotate, squaredInputs);
}
