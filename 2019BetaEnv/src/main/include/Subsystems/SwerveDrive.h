/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include "Subsystems/SideDrive.h"
#include "ctre/Phoenix.h"
#include "misc/ToggleClass.h"
#include <math.h>
#include "Commands/FieldDrive.h"
#include <iostream>

class SwerveDrive : public SideDrive {
	private:
		class DriveModule
		{
			private:
			Toggle<bool> edgeDet;
			public:
			WPI_TalonSRX* m_angle;
			WPI_TalonSRX* m_drive;
			DigitalInput* m_zero;
			bool zeroed;
			//TODO: Setup Value
			static constexpr int RATIO_ANGLE_COUNTS_PER_REV = 1;

			DriveModule(int idAngle, int idDrive, int portZero);
			~DriveModule();

			/**
			 * @brief Gets the position of the angle encoder
			 * 
			 * @return double the angle in radians
			 */
			double getAngle();

			/**
			 * @brief Set the angle of the module
			 * 
			 * @param pos the angle in radians
			 */
			void setAngle(double pos);

			/**
			 * @brief Set the rate of rotation for the module
			 * 
			 * @param vel the rotation rate in radians/100 milliseconds
			 */
			void setTurnRate(double vel);

			/**
			 * @brief Set the drive speed for the module
			 * 
			 * @param pVBus the speed as a fraction of the input voltage
			 */
			void setDriveSpeed(double pVBus);

			/**
			 * @brief Set the encoder zero point
			 * 
			 * Triggers the zero point when the digital input first triggers and the angle is increasing
			 * 
			 * @return true the zero was set
			 * @return false the zero was not set
			 */
			bool maintainZero();

			/**
			 * @brief Sets the encoder zero point
			 * 
			 * Triggers the zero point when the digital input triggers and the angle is increasing, then stops rotation
			 * 
			 * @return true the zero was set, and motion stopped 
			 * @return false the zero has not been set
			 */
			bool setZero();
		};

		SwerveDrive();
		static SwerveDrive* m_instance;

		DriveModule* m_leftFront;
		DriveModule* m_leftRear;
		DriveModule* m_rightFront;
		DriveModule* m_rightRear;

		SpeedControllerGroup* m_leftMotors;
		SpeedControllerGroup* m_rightMotors;
		SpeedControllerGroup* m_frontMotors;
		SpeedControllerGroup* m_rearMotors;

		DifferentialDrive* m_fwdDrive;
		DifferentialDrive* m_sideDrive;

		bool turnLocked;

		float zeroHeading=0;//TODO: To Set, may add setter later

		/**
		 * @brief Get the Drive object closest to parallel to the direction of travel
		 * 
		 * Gets the most parallel drive object to improve the turning ability of the robot.
		 * 
		 * @param itheta the direction of travel in degrees
		 * @return DifferentialDrive* the optimal drive to use
		 */
		DifferentialDrive* getDrive(int itheta);

		/**
		 * @brief Handles Driving when turnLocked is true
		 * 
		 * Should ONLY be used when turnLocked is true.
		 * 
		 * @param turn the rate of turning, as percentVBus.
		 */
		void driveTurn(double turn);
	public:
		~SwerveDrive();
		static SwerveDrive* getInstance();

		void InitDefaultCommand() override;

		/**
		 * @brief Checks if the wheels have found their zeros yet
		 * 
		 * @return true The zeros have been located
		 * @return false At least one wheel is unzeroed. 
		 */
		bool isZeroed();

		/**
		 * @brief gets the status of the turn lock
		 * 
		 * @return true turn lock is enabled
		 * @return false turn lock is disabled
		 */
		bool isTurnLocked(){return turnLocked;};

		/**
		 * @brief Sets the the turn lock status
		 * 
		 * When turn locked, the robot is unable to drive lateraly, but turning is easier.
		 * 
		 * @param lock True enables the lock, False disables it
		 */
		void setTurnLock(bool lock);

		/**
		 * @brief Tracks module rotation, to reset the zero when in the proper location.
		 * 
		 * For quality maintnance, should be run continuosly, independent of drive command. 
		 * If properly zeroed, shouldn't be needed, unless encoders drift or gears slip.
		 */
		void maintainZero();

		/**
		 * @brief Sets the zero initially
		 * 
		 * Identical to maintainZero(), but wheels stop when they find the zero point.
		 * 
		 */
		void setZero();

		/**
		 * @brief Rotates the drive wheels
		 * 
		 * Causes the drive wheels to rotate orientation at vel;
		 * 
		 * @param vel the rate of rotation in radians/100 ms
		 */
		void rotateWheels(double vel);

		static void rotateWheelsPVBus(double pVBus);

		void DriveCartesian(float x, float y, float rotate, bool squaredInputs = false) override;
		void DrivePolar(float m, float theta, float rotate, bool squaredInputs = false) override;

		void DriveFieldPolar(float m, float theta, float rotate, bool squaredInputs = false);
		void DriveFieldCartesian(float x, float y, float rotate, bool squaredInputs=false);

		float getWheelAngle();
};
