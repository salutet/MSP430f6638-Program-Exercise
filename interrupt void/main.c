#include <msp430f6638.h>

volatile unsigned int i;

void delay(volatile unsigned int duration)
{
	for(i=0 ; i<5000*duration ; i++);
}

void keycontrol()
{
	if((P4IN&BIT2) == 0)
	{
	delay(20);
	if((P4IN&BIT2) == 0)
		while((P4OUT&BIT2) == 0)
	    delay(20);
	    {
	    if((P4IN&BIT2) != 0)
	    {
	    P4OUT <<= 1;
	    if(P4OUT == BIT7)
	    	P4OUT = BIT4;
	    }

	    }
	 }
}
void main()
{
	WDTCTL = WDTPW + WDTHOLD;
	P4DIR |= BIT4 + BIT5 + BIT6 + BIT7;
    P4DIR &= ~(BIT2+BIT3);
    P4OUT = BIT4;
    while(1)
    {
    	keycontrol();
    }
}
