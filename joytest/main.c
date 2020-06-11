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
#include "pdlread.h"


// Defines

#define SW_VERSION "0.3"


// Globals

static uint8_t highestUp = 0x00;
static uint8_t lowestDown = 0xff;
static uint8_t lowestVertCentre = 0xff;
static uint8_t highestVertCentre = 0x00;

static uint8_t highestLeft = 0x00;
static uint8_t lowestRight = 0xff;
static uint8_t lowestHorizCentre = 0xff;
static uint8_t highestHorizCentre = 0x00;

// Implementation

void clearGlobals(void)
{
    highestUp = 0x00;
    lowestDown = 0xff;
    lowestVertCentre = 0xff;
    highestVertCentre = 0x00;

    highestLeft = 0x00;
    lowestRight = 0xff;
    lowestHorizCentre = 0xff;
    highestHorizCentre = 0x00;
}


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
    uint8_t joyDriverMask = 0x00;
    uint8_t prevJoyDriverMask = 0x00;
    uint8_t joystickNum = 0;
    char ch;
    
    uint8_t x;
    uint8_t y;
    bool testingX = true;
    uint8_t pdlNum = 0;
    
    clearGlobals();
    
    clrscr();
    cputsxy(11, 0, "CC65 JOYSTICK TEST");
    cputsxy(11, 1, "------------------");
    
    cputsxy(0, 3, "JOYSTICK NUM:");
    
    cputsxy(0, 11, "BUTTONS:");
    
    cputsxy(20, 10, "X POSITION:     ");
    cputsxy(20, 11, "Y POSITION:     ");
    
    cputsxy(0, 20, "PRESS 1/2 TO SELECT JOYSTICK NUMBER");
    cputsxy(0, 21, "PRESS X/Y TO SELECT AXIS TEST");
    cputsxy(0, 22, "PRESS C TO CLEAR TEST RESULTS");
    cputsxy(0, 23, "PRESS Q TO QUIT");
    cputsxy(30, 23, "(VER " SW_VERSION ")");
    
    prevJoyDriverMask = joy_read(joystickNum);
    drawJoystick(joyDriverMask);
    
    do {
        joyDriverMask = joy_read(joystickNum);
        
        drawJoystick(joyDriverMask);
        
        if (testingX)
        {
            x = pdlRead(pdlNum);
            
            if (JOY_LEFT(joyDriverMask))
            {
                if ((!JOY_LEFT(prevJoyDriverMask)) &&
                    (x > highestLeft))
                    highestLeft = x;
            }
            else if (JOY_RIGHT(joyDriverMask))
            {
                if ((!JOY_RIGHT(prevJoyDriverMask)) &&
                    (x < lowestRight))
                    lowestRight = x;
            }
            else
            {
                if ((JOY_LEFT(prevJoyDriverMask)) &&
                    (x < lowestHorizCentre))
                    lowestHorizCentre = x;
                else if ((JOY_RIGHT(prevJoyDriverMask)) &&
                         (x > highestHorizCentre))
                    highestHorizCentre = x;
            }
            
            cputsxy(20, 3, "TESTING: X AXIS");
            
            cputsxy(20, 5, "HIGHEST LEFT:   ");
            if (highestLeft == 0x00)
                cputs("N/A");
            else
                cprintf("%3d", highestLeft);
            
            cputsxy(20, 6, "LOWEST CENTRE:  ");
            if (lowestHorizCentre == 0xff)
                cputs("N/A");
            else
                cprintf("%3d", lowestHorizCentre);
            
            cputsxy(20, 7, "HIGHEST CENTRE: ");
            if (highestHorizCentre == 0x00)
                cputs("N/A");
            else
                cprintf("%3d", highestHorizCentre);
            
            cputsxy(20, 8, "LOWEST RIGHT:   ");
            if (lowestRight == 0xff)
                cputs("N/A");
            else
                cprintf("%3d", lowestRight);
            
            y = pdlRead(pdlNum + 1);
        }
        else
        {
            y = pdlRead(pdlNum);
            
            if (JOY_UP(joyDriverMask))
            {
                if ((!JOY_UP(prevJoyDriverMask)) &&
                    (y > highestUp))
                    highestUp = y;
            }
            else if (JOY_DOWN(joyDriverMask))
            {
                if ((!JOY_DOWN(prevJoyDriverMask)) &&
                    (y < lowestDown))
                    lowestDown = y;
            }
            else
            {
                if ((JOY_UP(prevJoyDriverMask)) &&
                    (y < lowestVertCentre))
                    lowestVertCentre = y;
                else if ((JOY_DOWN(prevJoyDriverMask)) &&
                         (y > highestVertCentre))
                    highestVertCentre = y;
            }
            
            cputsxy(20, 3, "TESTING: Y AXIS");
            
            cputsxy(20, 5, "HIGHEST UP:     ");
            if (highestUp == 0x00)
                cputs("N/A");
            else
                cprintf("%3d", highestUp);
            
            cputsxy(20, 6, "LOWEST CENTRE:  ");
            if (lowestVertCentre == 0xff)
                cputs("N/A");
            else
                cprintf("%3d", lowestVertCentre);
            
            cputsxy(20, 7, "HIGHEST CENTRE: ");
            if (highestVertCentre == 0x00)
                cputs("N/A");
            else
                cprintf("%3d", highestVertCentre);
            
            cputsxy(20, 8, "LOWEST DOWN:    ");
            if (lowestDown == 0xff)
                cputs("N/A");
            else
                cprintf("%3d", lowestDown);
                
            x = pdlRead(pdlNum - 1);
        }
        
        gotoxy(36, 10);
        cprintf("%3d", x);
        gotoxy(36, 11);
        cprintf("%3d", y);
        
        cputcxy(14, 3, '1' + joystickNum);
        
        prevJoyDriverMask = joyDriverMask;
        
        if (kbhit())
        {
            ch = cgetc();
            switch (ch)
            {
                case '1':
                case '2':
                    joystickNum = (ch - '1');
                    pdlNum = (testingX ? (2 * joystickNum) : ((2 * joystickNum) + 1));
                    
                    // Fallthrough...
                case 'C':
                case 'c':
                    clearGlobals();
                    break;
                    
                case 'x':
                case 'X':
                    testingX = true;
                    pdlNum = 2 * joystickNum;
                    break;
                    
                case 'y':
                case 'Y':
                    testingX = false;
                    pdlNum = (2 * joystickNum) + 1;
                    break;
                    
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
