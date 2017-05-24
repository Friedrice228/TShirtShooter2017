/*
 * Tank.cpp
 *
 *  Created on: May 17, 2017
 *      Author: gracekwak
 */

#include "Tank.h"
#include <WPILib.h>

const int close_state = 0;
const int open_state = 1;
int tank_state = close_state;

Tank::Tank() {

	inputValve = new DoubleSolenoid(0, 0, 0);
	pressureSensor = new AnalogInput(0);

}

void Tank::Open() {

	inputValve->Set(DoubleSolenoid::Value::kForward);

}

void Tank::Close() {

	inputValve->Set(DoubleSolenoid::Value::kReverse);

}

void Tank::TankStateMachine() {

	switch(tank_state) {

	case close_state:
		Close();
		break;

	case open_state:
		Open();
		break;

	}

}


