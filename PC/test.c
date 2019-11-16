#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "arduino-serial-lib.h"

#include <termios.h>
#include <ncurses.h>

// To use time library of C 
#include <time.h> 

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

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

int main(){

    char c;
    int i = 0;

    char car = '>';
    int y = 3, x = 1;

    const int buf_max = 256;

    int fd = -1;
    char serialport[buf_max];
    int baudrate = 9600;  // default
    char quiet=0;
    char eolchar = '\n';
    int timeout = 5000;
    char buf[buf_max];
    int rc,n;

    strcpy(serialport, "/dev/ttyACM0");

    fd = serialport_init(serialport, baudrate);

    initscr();

    cbreak();

    system("clear");

    gotoxy(x, y);
    printf("%c", car);

    do{

      c = getcht();
      // printf("\nYou typed: %c\n", c);

      switch (c){
        case 'w':
          serialport_writebyte(fd, 1);

          switch (car){
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
        case 'a':
          serialport_writebyte(fd, 2);

          switch (car){
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
        case 's':
          serialport_writebyte(fd, 3);

          switch (car){
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
        case 'd':
          serialport_writebyte(fd, 4);

          switch (car){
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
        case 'p':
          serialport_writebyte(fd, 5);
          break;
        default:
          break;
      }
      
      gotoxy(x, y);
      printf("%c", car);

      delay(1000);
    }while(c != 'p');

    clear();
    endwin();

    system("clear");
    for(i = 10; i > 0; i--){
      printf("Finalizando simulacion en %i segundos. \n", i);
      delay(1000);
      system("clear");
    }

    return 0;
}