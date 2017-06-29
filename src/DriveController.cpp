/*
 * DriveController.cpp
 *
 *  Created on: May 15, 2017
 *      Author: gracekwak
 */
#include "DriveController.h"

#define PI 3.14159

const double MAX_Y_RPM_ACTUAL = 0.0;
const double MAX_Y_RPM = 0.0;
const double MAX_YAW_RATE = (15.48 / 508) * MAX_Y_RPM; //max angular velocity divided by the max rpm multiplied by set max rpm

double output_l = 0.0;
double output_r = 0.0;

double Kf_d = 1 / MAX_Y_RPM_ACTUAL;
double Kp_d = 0.0;
double Ki_d = 0.0;
double Kd_d = 0.0;

double P_l = 0.0;
double P_r = 0.0;

double I_l = 0.0;
double I_r = 0.0;

double i_l = 0.0;
double i_r = 0.0;

double D_l = 0.0;
double D_r = 0.0;

double d_r = 0.0;
double d_l = 0.0;

double error_l = 0.0;
double error_r = 0.0;
double target_l = 0.0;
double target_r = 0.0;
double last_error_r = 0.0;
double last_error_l = 0.0;

double target_yaw_rate = 0.0;
double yaw_error = 0.0;
double yaw_rate_current = 0.0;
double yaw_last_error = 0.0;

double d_yaw = 0.0;
double k_p_yaw = 0.0;
double k_d_yaw = 0.0;

double yaw_output = 0.0;

DriveController::DriveController() {

	canTalonFrontLeft = new CANTalon(0);
	canTalonFrontRight = new CANTalon(0);
	canTalonBackLeft = new CANTalon(0);
	canTalonBackRight = new CANTalon(0);

	joyThrottle = new Joystick(0);
	joyWheel = new Joystick(0);
	ahrs = new AHRS(SPI::Port::kMXP);

}

void DriveController::Drive() {

	target_l = joyThrottle->GetY() * MAX_Y_RPM;
	target_r = joyThrottle->GetY() * MAX_Y_RPM;

	error_l = target_l - (canTalonFrontLeft->GetEncVel() / 4096.0) * 600.0;
	error_r = target_r + (canTalonFrontRight->GetEncVel() / 4096.0) * 600.0;

	target_yaw_rate = -1.0 * (joyWheel->GetX()) * MAX_YAW_RATE;
	yaw_rate_current = -1.0 * (double) ahrs->GetRawGyroZ()
			* (double) ((PI) / 180); //left should be positive
	yaw_error = target_yaw_rate - yaw_rate_current;

	target_l = target_l - (target_yaw_rate * (MAX_Y_RPM / MAX_YAW_RATE));
	target_r = target_r + (target_yaw_rate * (MAX_Y_RPM / MAX_YAW_RATE));

	d_yaw = yaw_error - yaw_last_error;
	yaw_output = (k_p_yaw * yaw_error) + (k_d_yaw * d_yaw);

	target_l = target_l - yaw_output;
	target_r = target_r + yaw_output;

	P_l = Kp_d * error_l;
	P_r = Kp_d * error_r;

	i_l += error_l;
	i_r += error_r;

	I_l = Ki_d * i_l;
	I_r = Ki_d * i_r;

	d_r = (error_r - last_error_r);
	d_l = (error_l - last_error_l);

	D_l = Kd_d * d_l;
	D_r = Kd_d * d_r;

	output_l = P_l + I_l + D_l + (Kf_d * target_l);
	output_r = P_r + I_r + D_r + (Kf_d * target_r);

	canTalonFrontLeft->Set(output_l);
	canTalonBackLeft->Set(output_l);
	canTalonFrontRight->Set(output_r);
	canTalonBackRight->Set(output_r);

	last_error_l = error_l;
	last_error_r = error_r;
	yaw_last_error = yaw_error;

}

