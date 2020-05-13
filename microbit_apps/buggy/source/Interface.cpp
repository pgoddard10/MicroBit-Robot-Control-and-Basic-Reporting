/**
 *  @Author: Paul Goddard - 17019749
 *  @Date: March 2019
 *  @Description: Provides a user interface and handles received comms
 */

#include "Interface.h"

MicroBit uBit; //create new instance of the MicroBit
Engine engine = Engine();
	
#define EVENT_ID	5555

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
  * Displays the letter C on the LED display once a bluetooth 
  * 	connection is established
  *
  * @param a standard MicroBitEvent (in this case, BLE connected)
  *
  */
void Interface::ble_onConnected(MicroBitEvent){
	/** shows status of connection whilst in use */
	uBit.display.print("C");
}


/**
  * Displays the letter D on the LED display once a bluetooth 
  * 	connection stops
  *
  * @param a standard MicroBitEvent (in this case, BLE disconnected)
  *
  */
void Interface::ble_onDisconnected(MicroBitEvent){
	/** shows status of connection whilst "in use" */
	uBit.display.print("D");
}


/**
  * Passes the event value through to the move() function in the 
  * 		Engine class. Called via BLE connection only.
  *
  * @param a standard MicroBitEvent
  *
  */
void Interface::ble_onEvent(MicroBitEvent e){
	engine.move(e.value);
}


/**
  * Passes the event value through to the move() function in the 
  * 		Engine class. Called via radio connection only.
  *
  * @param a standard MicroBitEvent
  *
  */
void Interface::rdo_onReceive(MicroBitEvent){
	PacketBuffer pb = uBit.radio.datagram.recv();
	uint64_t value = 0;
	
	/** convert 4 digit string into int.
	MicroBit PacketBuffer class doesn't have a strtoi() function (>.<) */
	for(int i=0; i<pb.length(); i++) {
		/** n-48 converts ASCII char into int. Then positioned into 
		 *	correct place for 4-digit num */
		if(i==0) value = (pb[i]-48)*1000;
		if(i==1) value += (pb[i]-48)*100;
		if(i==2) value += (pb[i]-48)*10;
		if(i==3) value += (pb[i]-48)*1;
	}
	engine.move(value);
}


/**
  * Sets the listeners for all radio and BLE events.
  *
  */
void Interface::run(){
	/** welcome message */
    uBit.display.scroll("Buggy");
    
    
    /** BLE controller (i.e. an Android phone) */
    uBit.messageBus.listen(EVENT_ID, 0, ble_onEvent);
    uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_CONNECTED, ble_onConnected);
    uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_DISCONNECTED, ble_onDisconnected);
    
    /** Radio controller (i.e. another Micro:Bit) */
	uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, rdo_onReceive);
	
    release_fiber();
}
