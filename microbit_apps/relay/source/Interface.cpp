/**
 *  @Author: Paul Goddard - 17019749
 *  @Date: March 2019
 *  @Description: Listens for pin input and broadcasts corresponding 
 * 			events via BLE
 */

#include "MicroBit.h"
#include "Interface.h"

MicroBit uBit;

/** Used for displaying connection status. -1 represents not set */
int8_t connected = -1; 

MicroBitButton buttonB(MICROBIT_PIN_BUTTON_B, MICROBIT_ID_BUTTON_B);

/** PIN INPUTS */
MicroBitPin P0(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_ALL); 
MicroBitPin P1(MICROBIT_ID_IO_P1, MICROBIT_PIN_P1, PIN_CAPABILITY_ALL); 
MicroBitPin P2(MICROBIT_ID_IO_P2, MICROBIT_PIN_P2, PIN_CAPABILITY_ALL); 


/** constructor. Enables an instance of MicroBit */
Interface::Interface() {
	/** init the MicroBit object to allow use of the specific device 
	 * 	functions at runtime */
	uBit.init();
}

/** deconstructor, as per default settings */
Interface::~Interface() {
}

/**
  * Displays the letter C on the LED display once a bluetooth 
  * 	connection is established
  *
  * @param a standard MicroBitEvent (in this case, BLE connected)
  *
  */
void Interface::onConnected(MicroBitEvent)	{
	uBit.display.print("C");
	connected = true;
}

/**
  * Displays the letter D on the LED display once a bluetooth 
  * 	connection stops
  *
  * @param a standard MicroBitEvent (in this case, BLE disconnected)
  *
  */
void Interface::onDisconnected(MicroBitEvent)	{
	uBit.display.print("D");
	connected = false;
}


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
void Interface::run() {
	
	uBit.display.scroll("Relay");
    
	uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_CONNECTED, onConnected);
	uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_DISCONNECTED, onDisconnected);
    
    while(1) {

		if(connected==true){
			/** Connected */
			uBit.display.print("C");
		}
		else if (connected==false) {
			/** Disconnected */
			uBit.display.print("D"); 
		}
		/** else do not report on connection status as it is unknown */
		
		/** Track whether input has been sent to ensure a stop event is
		  		 also sent*/
		bool input = false;
	
		while(buttonB.isPressed()){
			/** Button B - used for testing */
			input = true;
			MicroBitEvent evt(this->EVENT_SND, 9);
			uBit.display.print("9");
		}
		
		while(P0.getDigitalValue()){
			input = true;
			if(P2.getDigitalValue()) {
				/** right */
				MicroBitEvent evt(this->EVENT_SND, 2);
				uBit.display.print("R");
			}
			else {
				/** left */
				MicroBitEvent evt(this->EVENT_SND, 1);
				uBit.display.print("L");
			}
		}
		
		while(P1.getDigitalValue()){
			input = true;
			if(P2.getDigitalValue()) {
				/** backwards */
				MicroBitEvent evt(this->EVENT_SND, 4);
				uBit.display.print("B");
			}
			else {
				/** forwards */
				MicroBitEvent evt(this->EVENT_SND, 3);
				uBit.display.print("F");
			}
		}
		
		if(input) {
			/** Send an 'end' event to let the receiver know that the 
					movement is over */
			uBit.sleep(100);
			MicroBitEvent evt(this->EVENT_SND, 0);
			uBit.display.print("0");
		}
    }
	release_fiber();
}
