/**
 *  @Author: Paul Goddard - 17019749
 *  @Date: March 2019
 *  @Description: Provides a user interface and sends MicroBit events 
 * 			over the radio
 */
#include "Interface.h"

#define EVENT_ID		5555

#define LEFT_ON			6001
#define RIGHT_ON		6003
#define FORWARD_ON		7001
#define BACKWARDS_ON	7003
#define RESET			8000


MicroBit uBit;

/** constructor. Enables an instance of MicroBit and the radio */
Interface::Interface() {
	/** init the MicroBit object to allow use of the specific device 
	 * 	functions at runtime */
	uBit.init();
    
    /** turn the radio on */
    uBit.radio.enable(); 
     
     /** limit radio broadcasts to group 2 (prevents cross-over with 
      * 	colleague's MicroBits) */
    uBit.radio.setGroup(2);
}

/** deconstructor, as per default settings */
Interface::~Interface() {
}


/**
  * Takes the directional values, noted below, and sends over 
  * 	the radio
  *
  * @param takes the directional values, noted below
  * 
  * LEFT_ON			6001
  * RIGHT_ON		6003
  * FORWARD_ON		7001
  * BACKWARDS_ON	7003
  * RESET			8000
  * 
  */
void Interface::send(int direction){
	ManagedString ms(direction);
	uBit.radio.datagram.send(ms);
}


/**
  * Calls the send() function, passing through the value for 
  * 	RIGHT_ON (6003). Also displays R on the LED display
  *
  * @param MicroBitEvent is passed by the listener, by default, 
  * 	but is not used
  *
  */
void Interface::tiltRight(MicroBitEvent){
	uBit.display.print("R");
	send(RIGHT_ON);
}


/**
  * Calls the send() function, passing through the value for 
  * 	LEFT_ON (6001). Also displays L on the LED display
  *
  * @param MicroBitEvent is passed by the listener, by default, 
  * 	but is not used
  *
  */
void Interface::tiltLeft(MicroBitEvent){
	uBit.display.print("L");
	send(LEFT_ON);
}


/**
  * Calls the send() function, passing through the value for 
  * 	BACKWARDS_ON (7003). Also displays B on the LED display
  *
  * @param MicroBitEvent is passed by the listener, by default, 
  * 	but is not used
  *
  */
void Interface::tiltForward(MicroBitEvent){
	uBit.display.print("B");
	send(BACKWARDS_ON);
}


/**
  * Calls the send() function, passing through the value for 
  * 	FORWARD_ON (7001). Also displays F on the LED display
  *
  * @param MicroBitEvent is passed by the listener, by default, 
  * 	but is not used
  *
  */
void Interface::tiltBackwards(MicroBitEvent){
	uBit.display.print("F");
	send(FORWARD_ON);
}


/**
  * Calls the send() function, passing through the value for 
  * 	RESET (8000). Also displays - on the LED display
  *
  * @param MicroBitEvent is passed by the listener, by default, 
  * 	but is not used
  *
  */
void Interface::faceUp(MicroBitEvent){
	uBit.display.print("-");
	send(RESET);
}


/**
  * Sets the listeners for accelerometer data and calls the relevant 
  * 	functions to send messages to the buggy
  *
  */
void Interface::run(){
    
	uBit.display.scroll("Control");
	
	/** listens for the provided radio events before sending */
    uBit.radio.event.listen(EVENT_ID, MICROBIT_EVT_ANY);
    
	/** listens for the tilts via the accelerometer events before sending */
	uBit.messageBus.listen( MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_LEFT, this->tiltLeft);
	uBit.messageBus.listen( MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT, this->tiltRight);
	uBit.messageBus.listen( MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_UP, this->tiltForward);
	uBit.messageBus.listen( MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_DOWN, this->tiltBackwards);
	uBit.messageBus.listen( MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_FACE_UP, this->faceUp);
    
    release_fiber();
}

