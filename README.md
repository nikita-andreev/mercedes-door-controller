# A custom-made controller for handling the electric-driven door in the armored car based on the Mercedes-Benz 313 CDi 

The controller itself is an Arduino-Uno board with connected peripherals:
- Power supply (DC-DC converter 12V to 5V)
- 4 relays module
- The current sensor (based on ACS712 microchip)
- Remote control module 315MHz (based on PT2272-M4 microchip)

## Sketch description

Here you'll find a standard Arduino sketch. How to operate:
- checkout
- open the file `mercedes_door_controller.ino` in Arduino IDE
- correct if needed
- Compile && Upload to the board

**After the sketch is started it opens the door**

The `Door` class is configured through pre-processor directives (See door.h for details)

For the `Button` class and derived classes, the constructor takes 4 parameters:
`Button(byte pin, int short_time, int long_time, int fuse_timeout);`

- `byte pin` - An Arduino pin the button connected to
- `int short_time` - a time in milliseconds the button has to be pushed and then released to trigger **short pressed** event
- `int long_time` - a time in milliseconds the button has to be pushed and held to trigger a **long pressed** event 
- `int fuse_timeout` - a time to ignore (in milliseconds) any button inputs if the event was raised. This is provided to handle possible contact chatter effects

## Some photos in high resolution might help with understanding the schematic :)
