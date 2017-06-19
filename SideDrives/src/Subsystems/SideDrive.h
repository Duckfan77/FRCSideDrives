/*
 * SideDrive.h
 *
 *  Created on: Jun 19, 2017
 *      Author: Colin
 */

#ifndef SRC_SUBSYSTEMS_SIDEDRIVE_H_
#define SRC_SUBSYSTEMS_SIDEDRIVE_H_

#include <math.h>

class SideDrive {
public:
	SideDrive();
	virtual ~SideDrive();

	/**
	 *
	 *
	 *
	 * @param x The rate of travel in the x direction
	 * @param y The rate of travel in the y direction
	 * @param rotate The rate of rotation, unrelated to x and y
	 * @param gyro A gyro value, used for field oriented drive
	 */
	virtual void DriveCartesian(float x, float y, float rotate, float gyro=0.0)=0;

	/**
	 *
	 * @param m The magnitude of travel
	 * @param theta The angle at which to travel
	 * @param rotate The rate of rotation, unrelated to m and theta
	 */
	virtual void DrivePolar(float m, float theta, float rotate)=0;

private:
	virtual void CartesianToPolar(float x, float y, float rotate, float gyro=0.0);
	virtual void PolarToCartesian(float m, float theta, float rotate);
};

#endif /* SRC_SUBSYSTEMS_SIDEDRIVE_H_ */
