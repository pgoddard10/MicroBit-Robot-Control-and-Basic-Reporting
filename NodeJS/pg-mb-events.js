/**
 * @Author: Paul Goddard - 17019749
 * @Date: March 2019
 * @Description: This script listens for Micro:Bit events broadcast over a compatible BLE connection
 * 					Specifically, the events should link to the direction of a robot buggy and report
 * 					on how much time the buggy spend in each direction, and how long it is stationary.
 *
 *		Events: 0 = stationary
 *				1 = left
 *				2 = right
 *				3 = forward
 *				4 = backwards
 *				9 = button press (used for testing)
 * 
 * @note uses the Micro:Bit package from https://github.com/sandeepmistry/node-bbc-microbit
 *
 */

var BBCMicrobit = require('bbc-microbit');
var EVENT_FAMILY    = 9999; /** BLE variable */
var EVENT_VALUE_ANY = 0;	/** BLE variable */

console.log('\n\tYOU SHOULD BE RUNNING COMMAND PROMPT AS ADMINISTRATOR!!\n'); /** reminder, because my memory is short! */

/** check to see if a Micro:Bit address has been entered */
if(!process.argv[2]) {
	console.log("You haven't specified an address or ID. Please specify one and try again.");
	console.log("Example: noble pg-mb-events.js abcdefghijk");
	console.log("\tWhere abcdefghijk is the ID or address");
    process.exit(0);
}

var peripheralIdOrAddress = process.argv[2].toLowerCase(); /** i.e. [0]node [1]pg-mb-events.js [2]address */

var moving = false;
var left = null;
var right = null;
var forward = null;
var backwards = null;
var buttonPress = null;
var stationary = null;

/**
  * Listens for state changes and triggers the startScanning() function again
  *		This is to ensure that the app keeps scanning if the first Micro:Bit
  *		it finds isn't the one that the user has specified
  *
  * @param state can be <"unknown" | "resetting" | "unsupported" | "unauthorized" | "poweredOff" | "poweredOn">
  *
  *	@note this function was created as a workaround for Noble issue #223 "scanning seems stopped after connecting to 1 peripheral"
  *         Workaround was created by Steckdoserich (Aug 30, 2016), see
  *			https:/** github.com/noble/noble/issues/223#issuecomment-243415638
  */
function stateChanged(state) {
     if (state === 'poweredOn') {
         BBCMicrobit.on('scanStop', function () {
             setTimeout(function () {
                 BBCMicrobit.startScanning([], true, function (err) {
                     if (err) {
                         console.log("startScanning error: " + err);
                     }
                 });
             },2500);
         });
         BBCMicrobit.stopScanning();
         BBCMicrobit.startScanning([], true, function (err) {
             if (err) {
                 console.log("startScanning error: " + err);
             }
         });
     }
     else {
         BBCMicrobit.stopScanning();
     }
 }


/**
  * Converts the milliseconds into a string formatted as 
  *		hh:mm:ss:mss
  *
  * @param ms is the total milliseconds for the date entered
  * 
  * @note toISOString converts into the format of YYYY-MM-DDTHH:mm:ss.sssZ
  *		hence slicing as we're only interested in time
  * 
  */
function convertMStoTime(ms) {
    return new Date(ms).toISOString().slice(11, -1);
}

/** Searches for Micro:Bit devices over BLE  */
console.log('\tLooking for a Micro:Bit');
BBCMicrobit.discover(function(microbit) {
	console.log('\t\tdiscovered Micro:Bit: id = %s, address = %s', microbit.id, microbit.address);
	microbit.on('event', function(id, value) {		
		/** on each event received, create a new date value to track when the event was first received */
		var delta = new Date;
		
		/** value is the received event number. 0 is end of direction value
		 * This statement will check if the directional turn is over and print on the screen
		 * Will also set a start-point date for being stationary */
		if(value==0){
			if(left!=null) {
				console.log('Turned LEFT for %s',convertMStoTime(delta-left));
			}
			if(right!=null) {
				console.log('Turned RIGHT for %s',convertMStoTime(delta-right));
			}
			if(forward!=null) {
				console.log('Moved FORWARD for %s',convertMStoTime(delta-forward));
			}
			if(backwards!=null) {
				console.log('Moved BACKWARDS for %s',convertMStoTime(delta-backwards));
			}
			if(buttonPress!=null) {
				console.log('Pressed BUTTON for %s',convertMStoTime(delta-buttonPress));
			}
			
			moving = false;
			left = null;
			right = null;
			forward = null;
			backwards = null;
			buttonPress = null;
			stationary = new Date;
		}
		else {
			if(!moving) {
				if(stationary!=null) {
					console.log('STATIONARY for %s',convertMStoTime(delta-stationary));
					stationary = null;
				}
				if(value==1){
					moving = true;
					left = new Date;
				}
				else if(value==2){
					moving = true;
					right = new Date;
				}
				else if(value==3){
					moving = true;
					forward = new Date;
				}
				else if(value==4){
					moving = true;
					backwards = new Date;
				}
				else if(value==9){
					moving = true;
					buttonPress = new Date;
				}
			}
		}
	});

	/** quits app when Micro:Bit disconnects */
	microbit.on('disconnect', function() {
		console.log('\t\tMicro:Bit disconnected.');
		process.exit(0);
	});

	console.log('\tConnecting to Micro:Bit...');
	/** connects to Micro:Bit that has been discovered and subscribe to events */
	microbit.connectAndSetUp(function() {
		
		/** check whether the found Micro:Bit matches what the user specified */
		if (microbit.id === peripheralIdOrAddress || microbit.address === peripheralIdOrAddress) {	
			console.log('\t\tSuccessfully connected to Micro:Bit');
		
			console.log('\tSubscribing to event family %d',EVENT_FAMILY);
			/** subscribe to the Micro:Bit events */
			microbit.subscribeEvents(EVENT_FAMILY, EVENT_VALUE_ANY, function() {
				console.log('\t\tSuccessfully subscribed to all Micro:Bit events.');
			});
		}
		else {
			console.log("\tThere are no more Micro:Bits to identify.");
			console.log("\tPlease ensure you have turned it on and BLE is enabled.");
			process.exit(0);
		}
	});
});
