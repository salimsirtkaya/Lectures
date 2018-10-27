kMatlab -- Matlab commands for Khepera
======================================

by Yves Piguet, 8/1998
   Skye Legon,  2/1999

Copyright (c) 1998/99, K-Team SA
Extended for use with KiKS 2000-2004 by Theodor Storm

kMatlab is a set of Matlab routines that permit the user to interact with
Khepera over a serial connection.  It includes Windows DLLs to perform the 
system-level serial-port communication, and a library of useful Matlab .m
files to read sensors, set speed, etc.

==============================================================================

Install (for Win95/98/NT, but similar process for Mac)
------------------------------------------------------

Extract all "kMatlab" files to a directory on your hard disk.

Run Matlab.  To use the commands, you can simply change the local directory
to your kMatlab directory (e.g. » cd d:\path\to\kMatlab).
   
To avoid performing this step every time you load Matlab (or to run the
kMatlab commands from another directory) you can add the kMatlab directory
to the Matlab path.  From the Matlab menu, choose File, Set Path, and enter
(or Browse for) your kMatlab directory.  Choose "Add to Path".

Make sure Khepera is connected to your computer and powered on.
You are now ready to use the commands!

==============================================================================

Usage
-----

You must first OPEN the serial port using the KOPEN command, which
is of the form:

  » port_reference = kopen([ com_port, baud_rate, timeout])

e.g. use first serial device (COM1), at 19200 baud, with 1 second timeout:

  » ref = kopen([0,19200,1])

or for COM2 at 38400 baud:

  » ref = kopen([1,38400,1]) 

If you receive the response:

  ??? Undefined function or variable 'kopen'.

then you are not in the correct directory, or you have not set up your
path correctly.

Note that 0=COM1, 1=COM2!  Also, do not forget to assign kopen's return
value to some variable; it is required for all subsequent commands.
We will use 'ref' as our return variable for the following examples.


When you are done you must CLOSE the serial port:

  » kclose(ref)


Sending commands
----------------

To send a command that returns a SINGLE line response:

  » return_value = kcmd( port_reference, 'khepera_command')

To send a command that returns a MULTIPLE line response, you add a '1':

  » return_value = kcmd( port_reference, 'khepera_command', 1)

Notes:

The single-line command returns everything it receives from Khepera until it
receives a newline character.

The multi-line command, however, doesn't know how long your multi-line response
it, and so it waits for 'timeout' seconds, and then returns everything in the buffer.
The choice of timeout is therefore important.  Too small, and multi-line responses
will be truncated; too long, and the command will take a long time to return.
One second (timeout = 1) is recommended, and corresponds to 48 lines of 80-column text
at 38400 baud.

The use of the return value is optional.

Use the 'port_reference' that was returned by kopen.

Examples:

To return the system bios version (single-line):

  » kcmd(ref,'B')

  ans =

  b,5.01,5.00

To list currently running processes (multi-line):

  » kcmd(ref,'process',1)

  ans =

  Process N. 00000000  IDLE process for the micro-kernell, EF-98: Rev. 1.00
  Process N. 00000001  Start-up process of the Khepera, EF-98:    Rev. 5.00

==============================================================================

kMatlab Command Library
-----------------------

Although kopen, kcmd, and kclose are all you need to fully control Khepera
from Matlab, for convenience we have also provided a library of useful matlab 
commands.  They are described briefly below, but for more information please
read the .m files.  For explanation of the actual Khepera commands sent
by these Matlab routines, please consult Appendix A of the Khepera User Manual.

These commands are provided as a starting point.  You are encouraged to modify
and/or create your own new functions to suit your application.

The commands are not case sensitive.  They are written in mixed-case for
clarity, but for example kSetSpeedPID and ksetspeedpid are equivalent.

If an error occurs, many of the functions will return -1 as an error code.

The equivalents for all of the Khepera commands listed in Appendix A of 
the Khepera User Manual are listed at the end of this document.

Demos:
------
kProximityG(ref)
 - Graphical histogram or polar plot display of proximity sensor readings

kBraitenbergG(ref, gain)
 - Graphical demonstration of a Braitenberg vehicle ('gain' is optional)

System Commands:
----------------
kopen([port, baud_rate, timeout])
 - opens serial port, supports baud rates up to 115200 bps.

kcmd(ref, text_string)
 - sends a command to Khepera for a SINGLE-LINE response

kcmd(ref, text_string, 1)
 - sends a command to Khepera for a MULTI-LINE response

kclose(ref)
 - closes the serial port

kFlush(ref)
 - empties the buffer.  This is useful if you issue a multi-line
   command but forget the '1' parameter.  (see sample session below)
   A "command not found" message will be returned by Khepera--ignore this.

Information Commands:
---------------------
kBios(ref)
 - kBios(ref);          displays the bios and protocol versions
 - [a,b] = kBios(ref);  does not display, but assigns the values to a and b

kList(ref)
 - lists available ROM modules

kTeam(ref)
 - lists the K-Team

Sensor Commands:
----------------
kAmbient(ref)
 - returns the ambient light sensor readings as an 8-element vector

kProximity(ref)
 - returns the proximity sensor readings as an 8-element vector

Motor/Encoder Commands:
-----------------------
kGetStatus(ref)
 - returns a 6-element vector describing motor controller status

kStatus(ref)
 - displays text description of current motor controller status

kGetEncoders(ref)
 - returns a 2-element vector of current encoder values

kSetEncoders(ref, left, right)
 - sets the encoder positions.  If left and right aren't specified,
   the positions are reset to zero.

kSetPWM(ref, left, right)
 - sets the speed of the motors using pulse-width modulation values 
   (-255..+255)

== SPEED CONTROL:

kGetSpeed(ref)
 - returns a 2-element vector of current speeds

kSetSpeed(ref, left, right)
 - sets the motor speeds, regulated by PID control

kStop(ref)
 - stop Khepera (set speed to zero)

kSetSpeedPID(ref, Kp, Ki, Kd)
 - sets the PID coefficients of the speed controller.  If no values are 
   specified, they are reset to the defaults (3800, 800, 100)

== POSITION CONTROL:

kMoveTo(ref, left, right)
 - use the position controller to move to a position specified by encoder 
   counts

kSetPositionPID(ref, Kp, Ki, Kd)
 - sets the PID coefficients of the position controller.  If no
   values are specified, they are reset to the defaults (3000, 20, 4000)

kSetProfile(ref, velLeft, accLeft, velRight, accRight)
 - sets the velocity and acceleration profile of the position controller.
   If no values are specified, they are reset to the defaults 
   (vel=20, acc=64)

Miscellaneous Commands:
-----------------------

kGetAnalog(ref, channel)
 - read an analog input channel via the 10-bit A/D converter

kLED(ref, n, action)
 - set the two LEDs.  'n' and/or 'action' can be vectors,
   e.g. kLED(ref, [0 1], [2 0]) will toggle LED0, and turn off LED1.

kReadByte(ref, address)
 - reads a byte from the extension bus

kWriteByte(ref, address)
 - writes a byte to the extension bus

kTurret(ref, turretID, textString)
 - sends a text string command to an extension turret

kTurretBios(ref, turretID)
 - provided as an example of possible turret commands, this displays
   the bios version of an extension turret

kBraitenberg(ref, gain)
 - demonstrates a Braitenberg vehicle.  If no gain is specified, a default
   value of 0.7 is used.

==============================================================================

kMatlab equivalents to Khepera commands 
(as listed in Appendix A of the User Manual)

Khepera Command                                 kMatlab equivalent
------------------------------------------------------------------------
A - Configure                                   kSetSpeedPID
B - Read software version                       kBios
C - Set a position to be reached                kMoveTo
D - Set speed                                   kSetSpeed
E - Read speed                                  kGetSpeed
F - Configure the position PID controller       kSetPositionPID
G - Set position to the position counter        kSetEncoders
H - Read position                               kGetEncoders
I - Read A/D input                              kGetAnalog
J - Configure the speed profile controller      kSetProfile
K - Read the status of the motion controller    kGetStatus
L - Change LED state                            kLED
N - Read proximity sensors                      kProximity
O - Read ambient light sensors                  kAmbient
P - Set PWM (pulse width modulation)            kSetPWM
T - Send a message to an extension turret       kTurret
R - Read a byte on the extension bus            kReadByte
W - Write a byte on the extension bus           kWriteByte

==============================================================================

Sample session (has been edited for clarity):
---------------------------------------------

% open COM1 at 38400 baud, 1 second timeout

» ref = kopen([0, 38400, 1]);  

» kBios(ref);
Khepera BIOS version: 5.01
Khepera protocol version: 5.00

» kGetEncoders(ref)
ans =
     0
     0

% move forward 100 encoder counts

» kMoveTo(ref,100,100);   

» kGetEncoders(ref)
ans =
   100
   100

» kStatus(ref)
Left:   (status = AT TARGET) (control = SPEED)    (Error = 0)
Right:  (status = AT TARGET) (control = SPEED)    (Error = 0)

% try a multi-line command using the '1' parameter

» kcmd(ref,'memory',1)  
ans =
First free ROM address:   16'00012490, used 57%
First free RAM 1 address: 16'001243F4, used 13%
First free RAM 2 address: 16'001A0000, used 0%

% but if we forget the '1', we only receive the first line of the buffer

» kcmd(ref,'process')    
ans =
First free ROM address:   16'00012490, used 57%

% subsequent commands will receive incorrect responses stored in the buffer
% Here we ask for the system bios, but receive part of the previous response

» kcmd(ref,'B')  
ans =
First free RAM 1 address: 16'001243F4, used 13%

% flushing the buffer will let us continue normally (ignore the
% "Command not found" message)

» kFlush(ref)    
Buffer contents:
First free RAM 2 address: 16'001A0000, used 0%
b,5.01,5.00
Command not found

% we can now continue...

» kcmd(ref,'B')
ans =
b,5.01,5.00

% when we are finished, we can close the connection

» kclose(ref)
