/*
 * SideDrive.cpp
 *
 *  Created on: Jun 19, 2017
 *      Author: Colin
 */

#include <Subsystems/SideDrive.h>

SideDrive::SideDrive() {
	// TODO Auto-generated constructor stub

}

SideDrive::~SideDrive() {
	// TODO Auto-generated destructor stub
}

virtual void SideDrive::CartesianToPolar(float x, float y, float rotate, float gyro)
{
	float m=std::sqrt(x*x+y*y);
	float theta = std::acos(x/m);

	DrivePolar(m, theta, rotate);
}

virtual void SideDrive::PolarToCartesian(float m, float theta, float rotate)
{
	float x = std::cos(theta)*m;
	float y = std::sin(theta)*m;

	DriveCartesian(x, y, rotate);
}

