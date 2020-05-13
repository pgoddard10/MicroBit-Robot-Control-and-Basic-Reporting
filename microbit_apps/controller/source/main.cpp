 /**
 *  @Author: Paul Goddard - 17019749
 *  @Date: March 2019
 *  @Description: Simply used to call the Interface class.
 * 
 * 
 * Challenge 3 - UFCFVK-15-2
 * Specification:
 *		Implement an application that communicates between two micro:bits or a micro:bit and
 *		another device, e.g. a laptop or phone, using either the simplified radio comms (uBit.radio),
 *		or the more advanced Bluetooth LE. 
 * 
 */


#include "MicroBit.h"
#include "Interface.h"

int main() {
    Interface interface = Interface(); /** create new interface */
	interface.run(); 	/** run app */
}
