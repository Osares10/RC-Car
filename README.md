# RC-Car

**_Radio controlled car operated by an arduino trough serial communication in C._**

### Disclaimer
**This README is still work in progress.**

This program wouldn't have been done without the help of this repository [arduino-serial](https://github.com/todbot/arduino-serial).

## Requirements
* Unix/Linux OS.
* Arduino or similar serial communication protocol target.

## Usage
For basic usage modify the following line in the path **/PC/test.c**

    ```
    strcpy(serialport, "/dev/ttyACM0"); 
    ```
to the corresponding port your arduino is using.