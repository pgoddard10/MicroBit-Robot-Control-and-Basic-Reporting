/**
 *  @Author: Paul Goddard - 17019749
 *  @Date: March 2019
 *  @Description: Listens for pin input and broadcasts corresponding 
 * 			events via BLE
 */
#ifndef INTERFACE_H
#define INTERFACE_H

#include "MicroBit.h"

class Interface
{
public:
	/** constructor. Enables an instance of MicroBit  */
	Interface();
	
	/** deconstructor, as per default settings */
	~Interface();
	
	/**
	  * Sets the listeners for the BLE. Also listens for pin input on P0, 
	  * 	P1 and P2.
	  * 	P0 = left
	  * 	P1 = forward
	  * 	P3 = switch (i.e. if P0 and P3, then right.
	  * Sends BLE events to match the input.
	  *		Left = Event 1
	  *		Right = Event 2
	  *		Forward = Event 3
	  *		Backwards = Event 4
	  * 	End of movement = Event 0
	  * 	Button B = 9 (used for testing purposes only)
	  *
	  */
	void run();
	
	/**
	  * Displays the letter C on the LED display once a bluetooth 
	  * 	connection is established
	  *
	  * @param a standard MicroBitEvent (in this case, BLE connected)
	  *
	  */
	static void onConnected(MicroBitEvent);
	
	/**
	  * Displays the letter D on the LED display once a bluetooth 
	  * 	connection stops
	  *
	  * @param a standard MicroBitEvent (in this case, BLE disconnected)
	  *
	  */
	static 	void onDisconnected(MicroBitEvent);
	
private:
	const int EVENT_SND = 9999;
};

#endif
