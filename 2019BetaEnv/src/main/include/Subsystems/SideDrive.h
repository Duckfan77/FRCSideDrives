#pragma once

#include <math.h>
#include <AHRS.h>
#include <WPILib.h>

class SideDrive : frc::Subsystem
{
    protected:
        SideDrive(std::string name);
        AHRS* m_navX;
        bool m_bNavXPresent;

        virtual void CartesianToPolar(float x, float y, float rotate, bool squaredInputs = false);
        virtual void PolarToCartesian(float m, float theta, float rotate, bool squaredInputs = false);
    public:
        ~SideDrive();

        /**
         * 
         * @param x The rate of travel in the x direction
         * @param y The rate of travel in the y direction
         * @param rotate The rate of rotation, unrelated to x and y
         * @param squaredInputs Whether to square the input values, usually true for manual driving
         */
        virtual void DriveCartesian(float x, float y, float rotate, bool squaredInputs = false)=0;

        /**
         * 
         * @param m The magnitude of travel
         * @param theta The angle at which to travel
         * @param rotate The rate of rotation, unrleated to m and theta
         * @param squaredInputs Whether to square the input values, usually true for manual driving
         */
        virtual void DrivePolar(float m, float theta, float rotate, bool squaredInputs=false)=0;


};