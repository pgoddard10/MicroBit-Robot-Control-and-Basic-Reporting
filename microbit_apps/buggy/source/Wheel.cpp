/**
 *  @Author: Paul Goddard - 17019749
 *  @Date: March 2019
 *  @Description: The getters and setters used for the speed and 
 * 			direction of each wheel (in this case, will be used twice)
 */

#include "Wheel.h"

/** constructor, as per default settings */
Wheel::Wheel() {
}

/** deconstructor, as per default settings */
Wheel::~Wheel() {
}

/**
  * Stores the wheel's speed
  *
  * @param Speed value up to 1023 can be used. The higher the number, 
  * 		the faster the speed. 0 is stop.
  * 
  * @note If using setDigitalValue(), when operating the motor, speed 
  * 		choices are 1 for full speed and 0 for stop.
  *
  */
void Wheel::setSpeed(uint64_t speed){
	this->speed = speed;
}


/**
  * Stores the wheel's direction (forward or reverse)
  *
  * @param Directional value. Choices are 1 for forward and 0 for 
  * 		backwards.
  *
  */
void Wheel::setDirection(bool direction){
	this->direction = direction;
}


/**
  * Retreives the wheel's speed
  *
  * @return a positive value up to 1023. 0 is returned for stop.
  */
uint64_t Wheel::getSpeed(){
	return this->speed;
}


/**
  * Retreives the wheel's direction (forward or reverse)
  *
  * @return true for forward, and 0 for backwards.
  */
bool Wheel::getDirection(){
    return this->direction;
}
