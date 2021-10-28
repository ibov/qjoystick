# qjoystick
- This qjoystick class is rewritten based on the lib: https://github.com/drewnoakes/joystick
- I create the library and examples in Qt. See the headers for more details of the class functions. 
> Note that, your gamepad should be recognized under Linux, for example, mine is located at "/dev/input/js0".
> This library should work on Linux-based OS. I only tested the library on Ubuntu 18.04. It'll up to you to adapt to other OS.  
- **Author: N.D.Quan - 10/2021**

## New functions added:
- Auto reconnect to joystick after unplugging / plugging
- Emit signals including:
      + button / axis values
      + disconnected state

## Tested on:
- Ubuntu 18.04
- Qt5

## Creation and Handle functions:
```ruby
joystick = new Joystick("/dev/input/js0");
connect(joystick, &Joystick::onButtonChange,this,&JoystickMonitor::onButtonEvent);
connect(joystick, &Joystick::onAxisChange,this,&JoystickMonitor::onAxisEvent);
connect(joystick, &Joystick::onDisconnected,this,&JoystickMonitor::onDisconnectedEvent);
joystick->start();
```
##### Example results with x-mode joystick:
```ruby
Axis  4 : 31341
Axis  4 : 22535
Axis  4 : 0
Button  2 : 1
Button  2 : 0
Button  1 : 1
Button  1 : 0
Button  2 : 1
Button  2 : 0
Button  0 : 1
Button  0 : 0
Axis  1 : -520
Axis  1 : -8549
Axis  1 : -18133
Axis  1 : -28494
Axis  1 : -16061
Axis  1 : -4405
Axis  1 : 0
Joystick is disconnected:  true
Joystick is disconnected:  true
Joystick is disconnected:  true
Joystick is disconnected:  true
Joystick is disconnected:  false
Button  0 : 0
Button  1 : 0
Button  2 : 0
Button  3 : 0
Button  4 : 0
Button  5 : 0
Button  6 : 0
Button  7 : 0
Button  8 : 0
Button  9 : 0
Button  10 : 0
Axis  0 : 0
Axis  1 : 0
Axis  2 : -32767
Axis  3 : 0
Axis  4 : 0
Axis  5 : -32767
Axis  6 : 0
Axis  7 : 0
```
