/*
 * Firing.cpp
 *
 *  Created on: May 22, 2017
 *      Author: gracekwak
 */

#include <Firing.h>

const int close_state = 0;
const int fire_state = 1;
int barrel_fire_state = close_state;

Firing::Firing() {

	outputValve = new DoubleSolenoid(0, 0, 0);

}

void Firing::Close() {

	outputValve->Set(DoubleSolenoid::Value::kReverse);

}

void Firing::Fire() {

	outputValve->Set(DoubleSolenoid::Value::kForward);

}

void Firing::FiringStateMachine() {

	switch(barrel_fire_state) {

	case close_state:
		Close();
		break;

	case fire_state:
		Fire();
		break;
	}

}


