/**
 *  @Author: Paul Goddard - 17019749
 *  @Date: March 2019
 *  @Description: Sends messages over the pins to the relay MicroBit
 * 			The relay MicroBit then converts the signals into BLE events
 */

#ifndef MESSENGER_H
#define MESSENGER_H

#include "MicroBit.h"

class Messenger {

 public:
	/** constructor. Enables an instance of MicroBit and the radio */
	Messenger();
	
	
	/** deconstructor, as per default settings */
	~Messenger();
	
	
	/**
	  * Appropriately sets the pins to send the "left" message.
	  * This takes the form of 
	  * 	P2.setDigitalValue(1);
	  * 	P15.setDigitalValue(0);
	  *
	  */
    void sendLeft();
    
    
    /**
	  * Appropriately sets the pins to send the "right" message.
	  * This takes the form of 
	  * 	P2.setDigitalValue(1);
	  * 	P15.setDigitalValue(1);
	  *
	  */
    void sendRight();
    
    
    /**
	  * Appropriately sets the pins to send the "forward" message.
	  * This takes the form of 
	  * 	P14.setDigitalValue(1);
	  * 	P15.setDigitalValue(0);
	  *
	  */
    void sendForward();
    
    
    /**
	  * Appropriately sets the pins to send the "backwards" message.
	  * This takes the form of 
	  * 	P14.setDigitalValue(1);
	  * 	P15.setDigitalValue(1);
	  *
	  */
    void sendBackwards();
	
	
	/**
	  * Appropriately sets the pins to send the "off" message.
	  * This takes the form of 
	  * 	P2.setDigitalValue(0);
	  *	 	P14.setDigitalValue(0);
	  * 	P15.setDigitalValue(0);
	  *
	  */
    void sendOff();
};

#endif // MESSENGER_H
