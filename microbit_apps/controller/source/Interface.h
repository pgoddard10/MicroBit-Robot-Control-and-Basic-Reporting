/**
 *  @Author: Paul Goddard - 17019749
 *  @Date: March 2019
 *  @Description: Provides a user interface and sends MicroBit events 
 * 			over the radio
 */
#ifndef INTERFACE_H
#define INTERFACE_H

#include "MicroBit.h"
 
class Interface {

 public:
 
	/** constructor. Enables an instance of MicroBit  */
	Interface();
	
	/** deconstructor, as per default settings */
	~Interface();
	
	
	/**
	  * Sets the listeners for accelerometer data and calls the relevant 
	  * 	functions to send messages to the buggy
	  *
	  */
	void run();
 private:
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
    static void send(int direction);
    
    /**
	  * Calls the send() function, passing through the value for 
	  * 	RIGHT_ON (6003). Also displays R on the LED display
	  *
	  * @param MicroBitEvent is passed by the listener, by default, 
	  * 	but is not used
	  *
	  */
    static void tiltRight(MicroBitEvent);
    
    /**
	  * Calls the send() function, passing through the value for 
	  * 	LEFT_ON (6001). Also displays L on the LED display
	  *
	  * @param MicroBitEvent is passed by the listener, by default, 
	  * 	but is not used
	  *
	  */
    static void tiltLeft(MicroBitEvent);
    
    /**
	  * Calls the send() function, passing through the value for 
	  * 	FORWARD_ON (7001). Also displays F on the LED display
	  *
	  * @param MicroBitEvent is passed by the listener, by default, 
	  * 	but is not used
	  *
	  */
    static void tiltForward(MicroBitEvent);
    
    /**
	  * Calls the send() function, passing through the value for 
	  * 	BACKWARDS_ON (7003). Also displays B on the LED display
	  *
	  * @param MicroBitEvent is passed by the listener, by default, 
	  * 	but is not used
	  *
	  */
    static void tiltBackwards(MicroBitEvent);

	/**
	  * Calls the send() function, passing through the value for 
	  * 	RESET (8000). Also displays - on the LED display
	  *
	  * @param MicroBitEvent is passed by the listener, by default, 
	  * 	but is not used
	  *
	  */
    static void faceUp(MicroBitEvent);
};

#endif // INTERFACE_H








