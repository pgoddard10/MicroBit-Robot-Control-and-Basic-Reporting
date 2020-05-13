/**
 *  @Author: Paul Goddard - 17019749
 *  @Date: March 2019
 *  @Description: Sends messages over the pins to the relay MicroBit
 * 			The relay MicroBit then converts the signals into BLE events
 */

#include "Messenger.h"

/** PINS FOR MESSAGES				*/

/** Left												*/
MicroBitPin P2(MICROBIT_ID_IO_P2, MICROBIT_PIN_P2, PIN_CAPABILITY_DIGITAL);

/** Forward												*/
MicroBitPin P14(MICROBIT_ID_IO_P14, MICROBIT_PIN_P14, PIN_CAPABILITY_DIGITAL);

/** Switch to opposite (i.e. left on becomes right on)	*/
MicroBitPin P15(MICROBIT_ID_IO_P15, MICROBIT_PIN_P15, PIN_CAPABILITY_DIGITAL);
/** END PINS FOR MESSAGES			*/

/** constructor. Enables an instance of MicroBit and the radio */
Messenger::Messenger(){
}

/** deconstructor, as per default settings */
Messenger::~Messenger(){
}


/**
  * Appropriately sets the pins to send the "left" message.
  * This takes the form of 
  * 	P2.setDigitalValue(1);
  * 	P15.setDigitalValue(0);
  *
  */
void Messenger::sendLeft(){
	P2.setDigitalValue(1);
	P15.setDigitalValue(0);
}

/**
  * Appropriately sets the pins to send the "right" message.
  * This takes the form of 
  * 	P2.setDigitalValue(1);
  * 	P15.setDigitalValue(1);
  *
  */
void Messenger::sendRight(){
	P2.setDigitalValue(1);
	P15.setDigitalValue(1);
}

/**
  * Appropriately sets the pins to send the "forward" message.
  * This takes the form of 
  * 	P14.setDigitalValue(1);
  * 	P15.setDigitalValue(0);
  *
  */
void Messenger::sendForward(){
	P14.setDigitalValue(1);
	P15.setDigitalValue(0);
}

/**
  * Appropriately sets the pins to send the "backwards" message.
  * This takes the form of 
  * 	P14.setDigitalValue(1);
  * 	P15.setDigitalValue(1);
  *
  */
void Messenger::sendBackwards(){
	P14.setDigitalValue(1);
	P15.setDigitalValue(1);
}

/**
  * Appropriately sets the pins to send the "off" message.
  * This takes the form of 
  * 	P2.setDigitalValue(0);
  *	 	P14.setDigitalValue(0);
  * 	P15.setDigitalValue(0);
  *
  */
void Messenger::sendOff(){
	P2.setDigitalValue(0);
	P14.setDigitalValue(0);
	P15.setDigitalValue(0);
}
