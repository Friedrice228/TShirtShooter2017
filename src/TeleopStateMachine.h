/*
 * TeleopStateMachine.h
 *
 *  Created on: May 17, 2017
 *      Author: gracekwak
 */
#include <WPILib.h> //
#include <Tank.h>
#include <Barrel.h>
#include <Firing.h>
#ifndef TELEOPSTATEMACHINE_H_
#define TELEOPSTATEMACHINE_H_

class TeleopStateMachine {
public:
	TeleopStateMachine(Barrel *barrelP, Tank *tankP, Firing *firingP);
	void StateMachine(bool shoot, bool sixty, bool eighty);

	const int wait_for_button_state_h = 0;
	const int input_valve_state_h = 1;
	const int sixty_state_h = 2;
	const int eighty_state_h = 3;
	const int output_valve_state_h = 4;
	int state = wait_for_button_state_h;

};

#endif /* TELEOPSTATEMACHINE_H_ */
