/*
 * Tank.h
 *
 *  Created on: May 17, 2017
 *      Author: gracekwak
 */
#include <WPILib.h>
#include <CANTalon.h>

#ifndef TANK_H_
#define TANK_H_

class Tank {
public:

	DoubleSolenoid *inputValve;
	AnalogInput *pressureSensor;
	Tank();
	void Open();
	void Close();
	void TankStateMachine();

	const int close_state_h = 0;
	const int open_state_h = 1;
	int tank_state = close_state_h;


};

#endif /* TANK_H_ */
