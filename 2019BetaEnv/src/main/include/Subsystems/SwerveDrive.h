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

class SwerveDrive : SideDrive {
	private:
		class DriveModule
		{
			public:
			WPI_TalonSRX* m_angle;
			WPI_TalonSRX* m_drive;
			DigitalInput* m_zero;
			//TODO: Setup Value
			static constexpr int RATIO_ANGLE_COUNTS_PER_REV = 1;

			DriveModule(int idAngle, int idDrive, int portZero);
			~DriveModule();

			/**
			 * @brief Gets the position of the angle encoder
			 * 
			 * @return int the angle in radians
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
			 * @brief Set the encoder zero poin
			 * 
			 * Triggers the zero point when the digital input first triggers and the angle is increasing
			 * 
			 * @return true the zero was set
			 * @return false the zero was not set
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

		DifferentialDrive* getDrive(int itheta);
	public:
		~SwerveDrive();
		static SwerveDrive* getInstance();

		void InitDefaultCommand() override;

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
		void setTurnLock(bool lock){turnLocked=lock;};

		/**
		 * @brief Rotates the modules such that it sets the zero properly for each one.
		 * 
		 * While it is running, driving is disabled
		 */
		void zeroMotors();

		/**
		 * @brief Tracks module rotation, to reset the zero when in the proper location.
		 * 
		 * For quality maintnance, should be run continuosly, independent of drive command. 
		 * If properly zeroed, shouldn't be needed, unless encoders drift or gears slip.
		 */
		void maintainZero();

		void DriveCartesian(float x, float y, float rotate, bool squaredInputs = false) override;
		void DrivePolar(float m, float theta, float rotate, bool squaredInputs = false) override;
};
