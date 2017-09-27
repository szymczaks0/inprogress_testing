//***************************************************************************************
//  MSP430 Blink the LED Demo - Software Toggle P1.0
//
//  Description; Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430x5xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  Texas Instruments, Inc
//  July 2013
//***************************************************************************************

#include <msp430.h>
#include <stdio.h>
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    P1DIR |= BIT0;  //SET BIT0 (LED1) AS OUTPUT
    P1OUT &= ~BIT0; //SET LED1 OFF

    P1DIR &= ~BIT3; //SET P1.3 AS INPUT

    P1REN |= BIT3; //ENABLED PULL UP OR DOWN FOR P1.3
    P1OUT |= BIT3; //SPECIFIED AS A PULLUP FOR P1.3
    volatile unsigned int TOGGLE = 0;
    for(;;)
    {
        volatile unsigned int i;    // volatile to prevent optimization
        if (!(BIT3 & P1IN))
        {
            TOGGLE++;
            __delay_cycles(500000);
        }
        if (TOGGLE == 4) TOGGLE = 0;
        switch(TOGGLE)
        {
        case 0:
            if (!(BIT3 & P1IN)) break;
            i = 5000;                  // SW Delay
            do
                {
                i--;
                if (!(BIT3 & P1IN))
                    {
                        TOGGLE++;
                        __delay_cycles(500000);
                        break;
                    }
                }
            while(i != 0);
            P1OUT ^= BIT0;
            break;
        case 1:
            if (!(BIT3 & P1IN)) break;
            i = 10000;                  // SW Delay
            do
                {
                i--;
                if (!(BIT3 & P1IN))
                   {
                        TOGGLE++;
                        __delay_cycles(500000);
                   }
                }
            while(i != 0);
            P1OUT ^= BIT0;
            break;
        case 2:
            if (!(BIT3 & P1IN)) break;
            i = 20000;                  // SW Delay
            do
            {
                i--;
                if (!(BIT3 & P1IN))
                   {
                        TOGGLE++;
                       __delay_cycles(500000);
                   }
            }
            while(i != 0);
            P1OUT ^= BIT0;
            break;
        case 3:
            if (!(BIT3 & P1IN)) break;
            P1OUT &= ~BIT0;
            break;
        default:
            break;
        }
    }

}
/* if((P1IN & BIT3))
       {
           volatile unsigned int i;    // volatile to prevent optimization

           i = 25000;                  // SW Delay
           do i--;
           while(i != 0);
           P1OUT ^= BIT0;
           P1OUT &= ~BIT6;             //makes sure LED2 doesn't get stuck on in this state
       }
       else
       {
           volatile unsigned int i;    // volatile to prevent optimization
           i = 50000;                  // SW Delay
           do i--;
           while(i != 0);
           P1OUT ^= BIT6;
           P1OUT &= ~BIT0;             //makes sure LED1 doesn't get stuck on in this state
       }*/
