/*
 * Barrel.h
 *
 *  Created on: May 16, 2017
 *      Author: gracekwak
 */
#include <WPILib.h>
#include <CANTalon.h>
#ifndef BARREL_H_
#define BARREL_H_

class Barrel {
public:

	CANTalon *canTalonBarrel;

	Barrel();
	void MoveTo(double ref);
	void BarrelStateMachine();
	bool IsAtPosition();

	double previous_ref = 0;

	const int zero_state_h = 0;
	const int down_state_h = 1;
	const int sixty_state_h = 2;
	const int eighty_state_h = 3;
	int barrel_pos_state = zero_state_h;

};

#endif /* BARREL_H_ */
