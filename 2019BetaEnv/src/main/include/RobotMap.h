/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int kLeftMotor = 1;
// constexpr int kRightMotor = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int kRangeFinderPort = 1;
// constexpr int kRangeFinderModule = 1;

//TODO: SET IDs
constexpr int CAN_LEFT_FRONT_DRIVE=1;
constexpr int CAN_LEFT_FRONT_ANGLE=2;
constexpr int CAN_LEFT_REAR_DRIVE=5;
constexpr int CAN_LEFT_REAR_ANGLE=6;
constexpr int CAN_RIGHT_FRONT_DRIVE=3;
constexpr int CAN_RIGHT_FRONT_ANGLE=4;
constexpr int CAN_RIGHT_REAR_DRIVE=7;
constexpr int CAN_RIGHT_REAR_ANGLE=8;

constexpr int DIO_LEFT_FRONT_ZERO=1;
constexpr int DIO_LEFT_REAR_ZERO=0;
constexpr int DIO_RIGHT_FRONT_ZERO=2;
constexpr int DIO_RIGHT_REAR_ZERO=3;


constexpr int CONTROLLER_STICK_L=0;
constexpr int CONTROLLER_STICK_R=1;
constexpr int CONTROLLER_GAMEPAD=2;