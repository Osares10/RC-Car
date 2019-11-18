# RC-Car

**_Radio controlled car operated by an arduino trough serial communication in C._**


This program wouldn't have been done without the help of this repository [arduino-serial](https://github.com/todbot/arduino-serial).
#
The next repository has been made to work with an especific project, manipulation will be needed for general purposes.

## Requirements
* Unix/Linux OS.
* Arduino or similar serial communication protocol target.

## Usage
For basic usage modify the following line in the path **/PC/main.c**

```c
strcpy(serialport, "/dev/ttyACM0"); 
```
to the corresponding port your arduino is using.

It will be need to adapt the code in the path **/Arduino/main/main.ino** for especific models.

Then you will have to upload the Arduino code to your target and compile the new C codes with the next terminal command while being in the PC folder.

    gcc main.c -o main -L /Programming/Proyecto/PC arduino-serial-lib.c -lncurses

And you will have to start it with the next command while being in the same PC folder.

    sudo ./main