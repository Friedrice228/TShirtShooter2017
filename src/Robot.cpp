#include <iostream>
#include <memory>
#include <string>
#include <IterativeRobot.h>
#include <WPILib.h>
#include <Joystick.h>
#include <CANTalon.h>
#include <Barrel.h>
#include <Tank.h>
#include <Firing.h>
#include <TeleopStateMachine.h>

#define PI 3.14159

class Robot: public frc::IterativeRobot {

	const int SHOOT_BUTTON = 0;
	const int SIXTY_BUTTON = 0;
	const int EIGHTY_BUTTON = 0;

	Firing *firing_;
	Joystick *joyOp;
	Tank *tank_;
	Barrel *barrel_;
	TeleopStateMachine *teleop_state_machine;

	void RobotInit() {

		joyOp = new Joystick(0);
		tank_ = new Tank();
		barrel_ = new Barrel();
		firing_ = new Firing();
		teleop_state_machine = new TeleopStateMachine(barrel_, tank_, firing_);

	}

	void TeleopInit() {

		barrel_->barrel_pos_state = barrel_->zero_state_h;
		teleop_state_machine->state = teleop_state_machine->wait_for_button_state_h;

	}

	void TeleopPeriodic() {

		bool shoot_button = joyOp->GetRawButton(SHOOT_BUTTON);
		bool sixty_deg = joyOp->GetRawButton(SIXTY_BUTTON);
		bool eighty_deg = joyOp->GetRawButton(EIGHTY_BUTTON);

		teleop_state_machine->StateMachine(shoot_button, sixty_deg, eighty_deg);
		tank_->TankStateMachine();
		barrel_->BarrelStateMachine();

	}

};

START_ROBOT_CLASS(Robot)
