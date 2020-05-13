/**
 *  @Author: Paul Goddard - 17019749
 *  @Date: March 2019
 *  @Description: Provides a user interface and handles received comms
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include "Engine.h"
#include "MicroBit.h"
 
class Interface {

 public:
 
	/** constructor. Enables an instance of MicroBit and the radio */
	Interface();
	
	/** deconstructor, as per default settings */
	~Interface();
	
	
	/**
	  * Displays the letter C on the LED display once a bluetooth 
	  * 	connection is established
	  *
	  * @param a standard MicroBitEvent (in this case, BLE connected)
	  *
	  */
	static void ble_onConnected(MicroBitEvent e);
	
	
	/**
	  * Displays the letter D on the LED display once a bluetooth 
	  * 	connection stops
	  *
	  * @param a standard MicroBitEvent (in this case, BLE disconnected)
	  *
	  */
    static void ble_onDisconnected(MicroBitEvent e);
    
    
	/**
	  * Passes the event value through to the move() function in the 
	  * 		Engine class. Called via BLE connection only.
	  *
	  * @param a standard MicroBitEvent
	  *
	  */
    static void ble_onEvent(MicroBitEvent e);
    
    
	/**
	  * Passes the event value through to the move() function in the 
	  * 		Engine class. Called via radio connection only.
	  *
	  * @param a standard MicroBitEvent
	  *
	  */
    static void rdo_onReceive(MicroBitEvent e);
    
    
	/**
	  * Sets the listeners for all radio and BLE events.
	  *
	  */
    void run();
};

#endif // INTERFACE_H
