// Basic libraries for usage in linux
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

// Library for serial communication
#include "arduino-serial-lib.h"

// Libraries for screen manipulation
#include <termios.h>
#include <ncurses.h>

// To use time library of C 
#include <time.h> 

// Redifying variables for screen manipulation
#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

// Code for delays, obtained from:
/* -B- https://www.geeksforgeeks.org/time-delay-c/ */
void delay(int milliseconds){
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}
/* -B- */

// Code to get char from keyboard inputs, obtained from:
/* -A- https://stackoverflow.com/questions/7469139/what-is-the-equivalent-to-getch-getche-in-linux */
static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      current.c_lflag |= ECHO; /* set echo mode */
  } else {
      current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getcht_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getcht(void) 
{
  return getcht_(0);
}

/* Read 1 character with echo */
char getchet(void) 
{
  return getcht_(1);
}
/* -A- */

// Main program for arduino control
int main(){

    char c; // Variable for car character
    int i = 0;

    char car = '>';
    int y = 3, x = 1; // Variable for car starter position

    const int buf_max = 256; // Max size for buffer

    int fd = -1;
    char serialport[buf_max];
    int baudrate = 9600;  // default
    char quiet=0;
    char eolchar = '\n';
    int timeout = 5000;
    char buf[buf_max];
    int rc,n;

    strcpy(serialport, "/dev/ttyACM0"); // COM Port for the Arduino

    fd = serialport_init(serialport, baudrate);

    initscr(); // Screen manipulation start function

    cbreak(); // Function to make possible cancelation

    system("clear"); // Clean screen for fresh starter

    // To print Starting message
    // It gives time to the arduino to start listening
    for(i = 10; i > 0; i--){
      printf("Starting simulation in %i seconds. \n", i);
      delay(1000);
      system("clear");
    }

    gotoxy(x, y); // Start position for car
    printf("%c", car); // First printage of the car

    do{

      c = getcht(); // Calling function to get key pressed

      switch (c){ // Options for pressed key
        case 'w':  // For forward movement
          serialport_writebyte(fd, 1); // Sending instruction to arduino to move forward

          switch (car){ // To respond from previous position
            case '>':
              x = x + 1;
              break;
            case 'v':
              y = y + 1;
              break;
            case '<':
              x = x - 1;
              break;
            case '^':
              y = y - 1;
              break;
            default:
              break;
          }
          break;
        case 'a': // For left movement
          serialport_writebyte(fd, 2); // Sending instruction to arduino to move left

          switch (car){ // To respond from previous position
            case '>':
              car = '^';
              break;
            case '^':
              car = '<';
              break;
            case '<':
              car = 'v';
              break;
            case 'v':
              car = '>';
              break;
            default:
              break;
          }
          break;
        case 's':  // For backwards movement
          serialport_writebyte(fd, 3); // Sending instruction to arduino to move backwards

          switch (car){ // to respond from previous movement
            case '>':
              x = x - 1;
              break;
            case 'v':
              y = y - 1;
              break;
            case '<':
              x = x + 1;
              break;
            case '^':
              y = y + 1;
              break;
            default:
              break;
          }
          break;
        case 'd': // For right movement
          serialport_writebyte(fd, 4); // Sending instruction to arduino to move right

          switch (car){ // to respond from previous movement
              case '>':
                car = 'v';
                break;
              case 'v':
                car = '<';
                break;
              case '<':
                car = '^';
                break;
              case '^':
                car = '>';
                break;
              default:
                break;
            }
          break;
        case 'p':  // For ending program
          serialport_writebyte(fd, 5);
          break;
        default:
          break;
      }
      
      gotoxy(x, y); // For each call it prints the new position of the car
      printf("%c", car);

      // delay(1000);
    }while(c != 'p'); // It works while it isn't finished

    clear(); // Clears the window one last time
    endwin(); // Ends screen manipulation

    system("clear"); // Clears the terminal

    // To print Ending message
    for(i = 10; i > 0; i--){
      printf("Ending simulation in %i seconds. \n", i);
      delay(1000);
      system("clear");
    }

    return 0;
}