/**
 *  @Author: Paul Goddard - 17019749
 *  @Date: March 2019
 *  @Description: The getters and setters used for the speed and 
 * 			direction of each wheel (in this case, will be used twice)
 */

#ifndef WHEEL_H
#define WHEEL_H

#include "MicroBit.h"
 
class Wheel {

 public:
	Wheel(); /** constructor, as per default settings */
	~Wheel(); /** deconstructor, as per default settings */
	
	/**
	  * Stores the wheel's speed
	  *
	  * @param Speed value up to 1023 can be used. The higher the 
	  * 		number, the faster the speed. 0 is stop.
	  * 
	  * @note If using setDigitalValue(), when operating the motor, 
	  * 		speed choices are 1 for full speed and 0 for stop.
	  *
	  */
    void setSpeed(uint64_t speed);
    
    
	/**
	  * Stores the wheel's direction (forward or reverse)
	  *
	  * @param Directional value. Choices are 1 for forward and 0 for 
	  * 		backwards.
	  *
	  */
    void setDirection(bool direction);
    
    
	/**
	  * Retreives the wheel's speed
	  *
	  * @return a positive value up to 1023. 0 is returned for stop.
	  */
    uint64_t getSpeed();
    
    
	/**
	  * Retreives the wheel's direction (forward or reverse)
	  *
	  * @return true for forward, and 0 for backwards.
	  */
    bool getDirection();

 private:
    uint64_t speed;
    bool direction;
};

#endif // WHEEL_H
