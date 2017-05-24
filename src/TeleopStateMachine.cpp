/*
 * TeleopStateMachine.cpp
 *
 *  Created on: May 17, 2017
 *      Author: gracekwak
 */

#include "TeleopStateMachine.h"
#define PI 3.14159

const int threshold = 0;

const int wait_for_button_state = 0;
const int input_valve_state = 1;
const int sixty_state = 2;
const int eighty_state = 3;
const int output_valve_state = 4;
int state = wait_for_button_state;

bool sixty_ = false;
bool eighty_ = false;

Barrel * barrel_;
Tank * tank_;
Firing * firing_;

TeleopStateMachine::TeleopStateMachine(Barrel *barrelP, Tank *tankP, Firing *firingP) {

	barrel_ = barrelP;
	tank_ = tankP;
	firing_ = firingP;

}

void TeleopStateMachine::StateMachine(bool shoot, bool sixty, bool eighty) {

	switch(state) {

	case wait_for_button_state:
		sixty_ = false;
		eighty_ = false;
		barrel_->barrel_pos_state = barrel_->down_state_h;
		tank_->tank_state = tank_->close_state_h;
		firing_->barrel_fire_state = firing_->close_state_h;
		if(sixty) {
			sixty_ = true;
			state = input_valve_state;
		}
		if(eighty) {
			eighty_ = true;
			state = input_valve_state;
		}
		break;

	case input_valve_state:
		tank_->tank_state = tank_->open_state_h;
		if(tank_->pressureSensor->GetValue() > threshold) {
			if(sixty_) {
				state = sixty_state;
			}
			else if (eighty_) {
				state = eighty_state;
			}
		}
		break;

	case sixty_state:
		barrel_->barrel_pos_state = barrel_->sixty_state_h;
		if(shoot && barrel_->IsAtPosition()) {
			state = output_valve_state;
		}
		break;

	case eighty_state:
		barrel_->barrel_pos_state = barrel_->eighty_state_h;
		if(shoot && barrel_->IsAtPosition()) {
			state = output_valve_state;
		}
		break;

	case output_valve_state:
		firing_->barrel_fire_state = firing_->fire_state_h;

		state = wait_for_button_state;
		break;

	}

}

