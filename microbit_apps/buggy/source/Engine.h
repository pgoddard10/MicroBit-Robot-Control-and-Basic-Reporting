/**
 *  @Author: Paul Goddard - 17019749
 *  @Date: March 2019
 *  @Description: Responsible for operating both wheels 
 * 			and communicating with the Messenger class (which sends 
 * 			messages to the relay controller).
 */

#ifndef ENGINE_H
#define ENGINE_H

#include "Messenger.h"
#include "Wheel.h"
#include "MicroBit.h"

class Engine {

 public:
	Engine(); /** constructor, as per default settings */
	~Engine(); /** deconstructor, as per default settings */
	
	
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
    void move(uint64_t direction);

 private:
    Wheel leftWheel = Wheel(); /** a new instance of Wheel for the left */
    Wheel rightWheel = Wheel(); /** a new instance of Wheel for the right */
};

#endif // ENGINE_H
