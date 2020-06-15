/*
 * main.c
 * joytest
 *
 * Created by Jeremy Rand on 2020-06-02.
 * Copyright (c) 2020 Jeremy Rand. All rights reserved.
 *
 */


#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <conio.h>
#include <joystick.h>
#include <apple2.h>

#include "drivers/a2_joystick_drv.h"


// Defines

#define SW_VERSION "0.5"


// Implementation

void drawJoystick(uint8_t joyDriverMask)
{
    revers(JOY_BTN_1(joyDriverMask));
    cputcxy(9, 11, '1');
    
    revers(JOY_BTN_2(joyDriverMask));
    cputcxy(11, 11, '2');
    
    joyDriverMask &= (JOY_UP_MASK | JOY_DOWN_MASK | JOY_LEFT_MASK | JOY_RIGHT_MASK);
    
    revers(joyDriverMask == (JOY_UP_MASK | JOY_LEFT_MASK));
    cputsxy(3, 5, "UL");
    
    revers(joyDriverMask == JOY_UP_MASK);
    cputcxy(6, 5, 'U');
    
    revers(joyDriverMask == (JOY_UP_MASK | JOY_RIGHT_MASK));
    cputsxy(8, 5, "UR");
    
    revers(joyDriverMask == JOY_LEFT_MASK);
    cputcxy(4, 7, 'L');
    
    revers(joyDriverMask == 0);
    cputcxy(6, 7, 'C');
    
    revers(joyDriverMask == JOY_RIGHT_MASK);
    cputcxy(8, 7, 'R');
    
    revers(joyDriverMask == (JOY_DOWN_MASK | JOY_LEFT_MASK));
    cputsxy(3, 9, "DL");
    
    revers(joyDriverMask == JOY_DOWN_MASK);
    cputcxy(6, 9, 'D');
    
    revers(joyDriverMask == (JOY_DOWN_MASK | JOY_RIGHT_MASK));
    cputsxy(8, 9, "DR");
    
    revers(false);
}


void pollJoystick(void)
{
    uint8_t joystickCount;
    uint8_t joyDriverMask = 0x00;
    uint8_t joystickNum = 0;
    char ch;
    
    joystickCount = joy_count();
    
    clrscr();
    cputsxy(11, 0, "CC65 JOYSTICK TEST");
    cputsxy(11, 1, "------------------");
    
    if (joystickCount == 0)
    {
        cputsxy(0, 3, "NO JOYSTICKS FOUND");
        cputsxy(0, 4, "PRESS ANY KEY TO QUIT");
        while (!kbhit())
            ;
        cgetc();
        return;
    }
    
    cputsxy(0, 3, "JOYSTICK NUM:");
    cputsxy(0, 11, "BUTTONS:");
    
    if (joystickCount > 1)
    {
        gotoxy(0, 22);
        cprintf("PRESS 1%c%u TO SELECT JOYSTICK NUMBER",
                (joystickCount > 2 ? '-' : '/'), joystickCount);
    }
    cputsxy(0, 23, "PRESS Q TO QUIT");
    cputsxy(30, 23, "(VER " SW_VERSION ")");
    
    do {
        joyDriverMask = joy_read(joystickNum);
        
        drawJoystick(joyDriverMask);
        
        cputcxy(14, 3, '1' + joystickNum);
        
        if (kbhit())
        {
            ch = cgetc();
            switch (ch)
            {
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                {
                    uint8_t newJoystickNum = (ch - '1');
                    
                    if (joystickCount < 2)
                        break;
                    
                    if (newJoystickNum >= joystickCount)
                        break;
                    
                    if (newJoystickNum == joystickNum)
                        break;
                    
                    joystickNum = (ch - '1');
                    
                    break;
                }
                    
                case 'q':
                case 'Q':
                case 0x1b:
                    return;
            }
        }
    } while (1);
}


int main(void)
{
    joy_install(&a2_joystick_drv);
    pollJoystick();
    joy_uninstall();
    
    return 0;
}
