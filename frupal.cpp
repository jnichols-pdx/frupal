#include "frupal.h"

Frupal::Frupal(WINDOW * win, int y, int x)
{
  curWin = win;
  xCur = x;
  yCur = y;
  getmaxyx(curWin, yMax, xMax);
  yMax -= 2;
  xMax -= 2;
  keypad(curWin, true);
  mainGuy = new Hero(1000, 100);
}

//lk series updates cursors location coordinates for the map window, which will get updated in the disp() function

//lkup updates cursor location upwards
void Frupal::lkup()
{
  yCur -= 1;
  if(yCur < 1)
    yCur = yMax;
}

//lkdn updates cursor location downwards
void Frupal::lkdn()
{
  yCur -= -1; //yes, I am aware that this is...non-standard. lol
  if(yCur > yMax)
    yCur = 1;
}

//lklt updates cursor location to left
void Frupal::lklt()
{
  xCur -= 1;
  if(xCur < 1)
    xCur = xMax;
}

//lkrt updates cursor location to the right
void Frupal::lkrt()
{
  xCur -= -1;
  if(xCur > xMax)
    xCur = 1;
}

//performs the 'move' part of moving the cursor
void Frupal::disp()
{
    wmove(curWin, yCur, xCur);
}

//gets input from the user - currently only allows movement of cursor, and quitting. If an incorrect key is received, it simply recursively calls itself and awaits input

int Frupal::getmv()
{
  int ch = wgetch(curWin);
  wattroff(curWin, A_REVERSE);
  switch(ch)
  {
    case KEY_UP:
      lkup();
      break;
    case KEY_DOWN:
      lkdn();
      break;
    case KEY_LEFT:
      lklt();
      break;
    case KEY_RIGHT:
      lkrt();
      break;
    case 'q':
      break;
    default:
      ch = getmv();
      break;
  }
  return ch;
}
