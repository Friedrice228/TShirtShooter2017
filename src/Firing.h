/*
 * Firing.h
 *
 *  Created on: May 22, 2017
 *      Author: gracekwak
 */
#include <WPILib.h>
#ifndef SRC_FIRING_H_
#define SRC_FIRING_H_

class Firing {
public:

	Firing();
	void FiringStateMachine();
	void Close();
	void Fire();

	DoubleSolenoid *outputValve;

	const int close_state_h = 0;
	const int fire_state_h = 1;
	int barrel_fire_state = close_state_h;

};

#endif /* SRC_FIRING_H_ */
