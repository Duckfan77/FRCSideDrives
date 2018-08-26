#include "Subsystems/SideDrive.h"

SideDrive::SideDrive(std::string name) : frc::Subsystem("Sidedrive:"+name)
{
    try{
        //Connect to navX Gyro on MXP
        m_navX = new AHRS(SPI::Port::kMXP);
        m_bNavXPresent = true;
    } catch(std::exception &ex){
        //If connection fails, log the error.
        std::string str_error = "Error instantiating navX from MXP: ";
        str_error += ex.what();
        DriverStation::ReportError(str_error.c_str());
        m_bNavXPresent = false;
    }
}

SideDrive::~SideDrive()
{
    delete m_navX;
}

void SideDrive::CartesianToPolar(float x, float y, float rotate, bool squaredInputs)
{
    float m = std::sqrt(x*x+y*y);
    float theta = std::acos(x/m);

    DrivePolar(m,theta,rotate,squaredInputs);
}

void SideDrive::PolarToCartesian(float m, float theta, float rotate, bool squaredInputs)
{
    float x = std::cos(theta)*m;
    float y = std::sin(theta)*m;

    DriveCartesian(x,y,rotate,squaredInputs);
}