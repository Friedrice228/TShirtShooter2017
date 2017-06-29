/*
 * Barrel.cpp
 *
 *  Created on: May 16, 2017
 *      Author: gracekwak
 */
//position
#include "Barrel.h"
#include <WPILib.h>
#define PI 3.14159

const int zero_state = 0;
const int down_state = 1;
const int sixty_state = 2;
const int eighty_state = 3;
int barrel_pos_state = zero_state; //init state

double position = 0.0;
double output = 0.0;

double Kp = 0.0;
double Ki = 0.0;
double Kd = 0.0;

double P = 0.0;
double I = 0.0;
double D = 0.0;

double i = 0.0;
double d = 0.0;

double error = 0.0;
double last_error = 0.0;

Barrel::Barrel() {

	canTalonBarrel = new CANTalon(0);

}

void Barrel::MoveTo(double ref) { //ref must be in radians from the starting position, the horizontal is NOT 0 Rad

	position = canTalonBarrel->GetEncPosition() * (2 * PI / 4096);

	if (ref <= position){

		Kp = 1.0; //not real values
		Ki = 1.0;
		Kd = 1.0;

	} else {

		Kp = 0.0;
		Ki = 0.0;
		Kd = 0.0;

	}

	error = ref - position;

	P = Kp * error;

	i += error;
	I = Ki * i;

	d = (error - last_error);
	D = Kd * d;

	output = P + I + D;

	canTalonBarrel->Set(output);

	last_error = error;

}

bool Barrel::IsAtPosition() {

	if(error <= PI/30) {
		return true;
	}
	else {
		return false;
	}

}

void Barrel::BarrelStateMachine() {

	switch(barrel_pos_state) {

	case zero_state:
		canTalonBarrel->Set(0);
		break;

	case down_state:
		MoveTo(0);
		break;

	case sixty_state:
		MoveTo(PI/3);
		IsAtPosition();
		break;

	case eighty_state:
		MoveTo(PI/2.2);
		IsAtPosition();
		break;

	}

}


