# UFCFVK-15-2 - IoT - Challenge 3 : Radio and Bluetooth Connection

## Overview
A small robotic "buggy" operated by a Micro:Bit over Bluetooth. The controller can either be another Micro:Bit or an Android phone. Optionally, the buggy can be connected to another Micro:Bit over wires which (via Bluetooth) relays movement data to a computer running NodeJS.

## Task Specification
(This information is copied from the Assignement brief found on Blackboard)

Implement an application that communicates between two micro:bits or a micro:bit and another device, e.g. a laptop or phone, using either the simplified radio comms (uBit.radio), or the more advanced Bluetooth LE.

Your solution should be implemented using C++. For the BLE solution you might what to look at using MBED rather that the the micro:bit DAL runtime we have been using to date. Your solution must be committed in UWE's Gitlab. It will naturally be time stamped and you must be careful to not make commits after the submission deadline. If you choose to use just the basic radio comms, then you can get a maximum of 70% for the submission.

To get beyond the 70% you should use Bluetooth LE.

Your solution's source code should follow a coding convention, it should be well commented, and include a README.md on how to build it and what and how to use your solution.

Submission should be individually and the README.md must document who contributed to
the submission.

But what should the communication do? That is up to you, but here are some possible ideas:

- Using BLE you could develop a service to transmit movements of the micro:bit using the accelerometer. These recordings could be transmitted to a laptop, for example, running a single client developed in Node.js that displays the movements in textural or better still graphical form. An alternative might be to use Python. (This is seen as the hardest challenge and will be marked as such. It is not recommended for those that have found the other 2 challenges hard.)

- Using the simplified radio comms API, which is part of the DAL, develop an extension of the Morse code protocol from challenge 2, so that it can work wireless. This should be fairly straightforward project and will be marked according.

- Using the simplified radio comms API, which is part of the DAL, develop a protocol to communicate commands to work with the BBC micro:bit inventor kit. (https://www.kitronik.co.uk/5603-inventors-kit-for-the-bbc-microbit.html). These can be loaned from the project room, on a two day basis. There will also be some in the lab sessions. Node.js library to develop BLE central applications is: https://github.com/noble/noble. Note, your laptop or desktop device must support BLE (Bluetooth 4) for this to work.

## Prerequisites
There are several options available here, depending on equipment available and how much effort you can be bothered to go through.
At a minimum, you'll need a Micro:Bit and a controller device (either an Android phone, or another Micro:Bit).
To get data relating to the length of time the buggy is stationary and moving for, you'll need another Micro:Bit and four wires to connect (with appropriate connections).

The setup section of this ReadMe will direct you on how everything fits together.

### Hardware:
* Compatible Bluetooth receiver in your computer (if used with a relay). See documentation at https://github.com/noble/noble
* An Android phone (if used as controller)
* Robo:Bit Buggy (tested on Mk2 but should work on newer versions). Purchase from https://shop.4tronix.co.uk/collections/robobit/products/robo-bit-buggy-for-the-bbc-micro-bit-robobit-for-microbit?variant=5859703619616
* A Micro:Bit for the buggy
* A Micro:Bit for the relay device (if used)
* A Micro:Bit for use as the controller (if used in place of the Android phone)
* Micro USB cable to transfer .hex files onto Micro:Bits

### Windows 10 PC - To display length of time buggy travels in each direction
* With NodeJS and Noble installed. See https://github.com/noble/noble for installation instructions

### Android Software (if used as a controller)
* Martin Woolley's Micro:Bit Blue - https://github.com/microbit-foundation/microbit-blue

## Setup & Operation
### Robo:Bit / Buggy
Select a connection method: Android Phone via BLE or Micro:Bit via radio. Download and load the relevant <a href="https://gitlab.uwe.ac.uk/p3-goddard/ufcfvk-15-2-iot-challenge-3/tree/master/microbit%20hex%20files%20-%20ready%20to%20use">iot-c3-buggy-combined.hex</a> file for the method you wish to use.
Insert the Micro:Bit containing this program into the slot connector for the Robo:Bit (at the back, on the Mk2).

#### Relay
Download and load the relevant <a href="https://gitlab.uwe.ac.uk/p3-goddard/ufcfvk-15-2-iot-challenge-3/tree/master/microbit%20hex%20files%20-%20ready%20to%20use">iot-c3-relay-combined.hex</a> file.

The table below shows how the wires are connected

| Robo:Bit Pin   | Micro:Bit Pin |
|----------------| --------------|
|P2              |P0             |
|P14             |P1             |
|P15             |P2             |
|GND             |GND            |

You will also need a power source for the Relay Micro:Bit, connected as per usual.

It is suggested that you create an additional case to hold the Relay device (and associated power/wires, like the one in the diagram below:

<img src="https://gitlab.uwe.ac.uk/p3-goddard/ufcfvk-15-2-iot-challenge-3/raw/master/img/Labelled%20Buggy%20Diagram.png" alt="Labelled Buggy Diagram"/>

### Android Controller
1. Pair with phone through the phone's Bluetooth settings (see https://vimeo.com/161609551 for help)
2. Open Micro:Bit Blue and press `FIND PAIRED BBC MICRO:BITS`
3. Select the paired Micro:Bit
4. Select `Dual D-Pad Controller`
5. Select the menu button (elipses in the top-right corner)
6. Configure with the following settings (You only need to configure one D-Pad)
7. Go back to the D-Pad picture and press the directional controls!

Bluetooth Event Codes required within the Android App settings

| Name              | Code          |
|-------------------| --------------|
|GamePad Event Code |5555           |
|Up ON              |7001           |
|Up OFF             |7002           |
|Down ON            |7003           |
|Down OFF           |7004           |
|Left ON            |6001           |
|Left OFF           |6002           |
|Right ON           |6003           |
|Right OFF          |6004           |

### Micro:Bit Controller
Download and load the <a href="https://gitlab.uwe.ac.uk/p3-goddard/ufcfvk-15-2-iot-challenge-3/tree/master/microbit%20hex%20files%20-%20ready%20to%20use">iot-c3-controller-combined.hex</a> file. This will only work over the radio communication, so ensure the Buggy is using the radio .hex file.
Tilt in the direction you wish the buggy to travel in.
*Note:* This is quite inflexible due to the getX() and getY() commands not working (so the tilt listeners have been used intead). As a result, you may find it difficult to gain precision on the controls.

#### Windows
1. Turn on Windows PC
2. Load Command Prompt as Administrator
3. Change directory (CD) to the location of the Noble files
4. run `pg-mb-events.js` with the MAC address of the Micro:Bit after as a parameter, e.g. `node pg-mb-events.js abcdefghijk` If you do not know the MAC address, put in any string and it will start searching for nearby devices. Make a note of the address on screen and give it a try.
5. Put the micro:bit serving as the Relay (i.e. the one with the wires connected) into Bluetooth pairing mode (see https://vimeo.com/161609551 for help)
6. Wait for the script to pair. The Micro:Bit will display a tick (this may be distorted due to power fluctuations if the wires are connected)
7. Reset the Micro:Bit
8. Restart the js script
9. The script will now be listening for events. Make the buggy move and see what happens!

## State Diagrams
These state diagrams explain how each application functions on a state-by-state basis.
<img src="https://gitlab.uwe.ac.uk/p3-goddard/ufcfvk-15-2-iot-challenge-3/raw/master/img/state_diagrams/radio_controller.png" alt="radio_controller" width="500px"/>

<img src="https://gitlab.uwe.ac.uk/p3-goddard/ufcfvk-15-2-iot-challenge-3/raw/master/img/state_diagrams/buggy.png" alt="buggy/robot" width="500px"/>

<img src="https://gitlab.uwe.ac.uk/p3-goddard/ufcfvk-15-2-iot-challenge-3/raw/master/img/state_diagrams/relay.png" alt="relay" width="500px"/>

<img src="https://gitlab.uwe.ac.uk/p3-goddard/ufcfvk-15-2-iot-challenge-3/raw/master/img/state_diagrams/nodeJS.png" alt="nodeJS" width="500px"/>

## References
1. <I>Config.Json. </I>(2018) Available from: <a href="https://github.com/lancaster-university/microbit-samples/blob/master/source/examples/bluetooth-services/config.json" TARGET="_blank">https://github.com/lancaster-university/microbit-samples/blob/master/source/examples/bluetooth-services/config.json</a> [Accessed 11 March 2019].
2. <I><B>Robo:Bit Mk2 Robotics Controller and Buggy for Micro:Bit</B>. </I>(2017) Available from: <a href="https://4tronix.co.uk/blog/?p=1534" TARGET="_blank">https://4tronix.co.uk/blog/?p=1534</a> [Accessed 11 March 2019].
3. <I><B>Bit:Bot Robot for BBC Micro:Bit</B>. </I>(2016) Available from: <a href="https://4tronix.co.uk/blog/?p=1490" TARGET="_blank">https://4tronix.co.uk/blog/?p=1490</a> [Accessed 11 March 2019].
4. <I><B>getAnalogValue should be 0- 1023</B>. </I>(2016) Available from: <a href="https://github.com/lancaster-university/microbit-docs/issues/37" TARGET="_blank">https://github.com/lancaster-university/microbit-docs/issues/37</a> [Accessed 13 March 2019].
5. <I><B>BBC Micro:Bit Bluetooth Profile</B>. </I>Available from: <a href="https://lancaster-university.github.io/microbit-docs/ble/profile/" TARGET="_blank">https://lancaster-university.github.io/microbit-docs/ble/profile/</a> [Accessed 11 March 2019].
6. <I><B>uBit.Io</B>. </I>Available from: <a href="https://lancaster-university.github.io/microbit-docs/ubit/io/#constructor" TARGET="_blank">https://lancaster-university.github.io/microbit-docs/ubit/io/#constructor</a> [Accessed 13 March 2019].
7. Woolley, M. (2017) <I><B>Micro:Bit Blue</B>. </I>Available from: <a href="https://github.com/microbit-foundation/microbit-blue" TARGET="_blank">https://github.com/microbit-foundation/microbit-blue</a> [Accessed 11 March 2019].
8. Woolley, M. (2017) <I>Range is Going to be a Factor of Three Things. </I>Available from: <a href="http://bluetooth-mdw.blogspot.com/p/bbc-microbit.html?showComment=1488162079018#c7229269737602883749" TARGET="_blank">http://bluetooth-mdw.blogspot.com/p/bbc-microbit.html?showComment=1488162079018#c7229269737602883749</a> [Accessed 13 March 2019].
9. Lancaster University (2018) *micro:bit runtime.* Available from: https://lancaster-university.github.io/microbit-docs/ [Accessed 11 February 2019].
10. Micro:bit Educational Foundation (2018) *Hardware.* Available from: Hardware [Accessed 11 February 2019].
