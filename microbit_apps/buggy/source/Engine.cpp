/**
 *  @Author: Paul Goddard - 17019749
 *  @Date: March 2019
 *  @Description: Responsible for operating both wheels 
 * 			and communicating with the Messenger class (which sends 
 * 			messages to the relay controller).
 */
 
#include "Engine.h"
#include "Messenger.h"

#define LEFT_ON			6001
#define LEFT_OFF		6002
#define RIGHT_ON		6003
#define RIGHT_OFF		6004

#define FORWARD_ON		7001
#define FORWARD_OFF		7002
#define BACKWARDS_ON	7003
#define BACKWARDS_OFF	7004

#define OFF				8000

Messenger messenger = Messenger(); /** new Messenger to send messages */

/** PINS FOR MOTOR			*/

/** Left motor - speed		*/
MicroBitPin P0(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_ALL);

/** Left motor - direction	*/
MicroBitPin P8(MICROBIT_ID_IO_P8, MICROBIT_PIN_P8, PIN_CAPABILITY_DIGITAL); 

/** Right motor - speed		*/
MicroBitPin P1(MICROBIT_ID_IO_P1, MICROBIT_PIN_P1, PIN_CAPABILITY_ALL);

/** Right motor - direction	*/
MicroBitPin P12(MICROBIT_ID_IO_P12, MICROBIT_PIN_P12, PIN_CAPABILITY_DIGITAL);

/** ENDPINS FOR MOTOR			*/


/** constructor, as per default settings */
Engine::Engine() {
}

/** deconstructor, as per default settings */
Engine::~Engine() {
}

	
/**
  * Takes the directional value, converts it into motor functions 
  * 	and drives the appropiate wheels.
  *
  * @param direction value, a 4 digit number (one of the selection 
  * 		noted below)
  * 
  * LEFT_ON			6001
  * LEFT_OFF		6002
  * RIGHT_ON		6003
  * RIGHT_OFF		6004

  * FORWARD_ON		7001
  * FORWARD_OFF		7002
  * BACKWARDS_ON	7003
  * BACKWARDS_OFF	7004

  * OFF				8000
  *
  */
void Engine::move(uint64_t direction){
	switch(direction) {
		case LEFT_ON:
			leftWheel.setSpeed(0);
			leftWheel.setDirection(1);
			rightWheel.setSpeed(1);
			rightWheel.setDirection(0);
			messenger.sendLeft();
			break;
		case RIGHT_ON:
			leftWheel.setSpeed(1);
			leftWheel.setDirection(0);
			rightWheel.setSpeed(0);
			rightWheel.setDirection(1);
			messenger.sendRight();
			break;
		case FORWARD_ON:
			leftWheel.setSpeed(1);
			leftWheel.setDirection(0);
			rightWheel.setSpeed(1);
			rightWheel.setDirection(0);
			messenger.sendForward();
			break;
		case BACKWARDS_ON:
			leftWheel.setSpeed(0);
			leftWheel.setDirection(1);
			rightWheel.setSpeed(0);
			rightWheel.setDirection(1);
			messenger.sendBackwards();
			break;
		case LEFT_OFF:
		case RIGHT_OFF:
		case FORWARD_OFF:
		case BACKWARDS_OFF:
		case OFF:
			leftWheel.setSpeed(0);
			leftWheel.setDirection(0);
			rightWheel.setSpeed(0);
			rightWheel.setDirection(0);
			messenger.sendOff();
			break;
	}
	
	/** Move motors according to speed and direction set */
	
	/** left wheel */
	P0.setDigitalValue(leftWheel.getSpeed());
	P8.setDigitalValue(leftWheel.getDirection());
	
	/** right wheel */
	P1.setDigitalValue(rightWheel.getSpeed());
	P12.setDigitalValue(rightWheel.getDirection());
}
