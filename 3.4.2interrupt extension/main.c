#include <msp430f6638.h>

volatile unsigned int duty=50;

void darken(void)
{
	if(TB0CCR4 > 400)
	{
		TB0CCR4 -= duty;
		TB0CCR5 += duty;
	}
}

void lighten(void)
{
	if(TB0CCR4 < 1200)
	{
		TB0CCR4 += duty;
		TB0CCR5 -= duty;
	}
}

void main (void)
{
	WDTCTL = WDTPW + WDTHOLD;                  //close watchdog timer

	TB0CTL = TBSSEL_1 + MC_1 + TBCLR;
	TB0CCR0 = 1200;                            //T = 1200*(1/32768)=0.0366s
	TB0CCTL4 = OUTMOD_7;
	TB0CCR4 = 1200;
	TB0CCTL5 = OUTMOD_7;
	TB0CCR5 = 400;

	P4DIR |= BIT4 + BIT5;
	P4SEL |= BIT4 + BIT5;
	P4DIR &= ~(BIT2+BIT3);
	P4IE |= BIT2+BIT3;                         // Allow P4.2 P4.3 interrupt
	P4IES |= BIT2+BIT3;                        // P4.2 P4.3选择下降沿触发
	P4IFG &= ~(BIT2 + BIT3);                   // Clear interrupt flag
	_BIS_SR(LPM0_bits + GIE);
}

// 中断服务程序
#pragma vector = PORT4_VECTOR
__interrupt void KEYCONTROL(void)
{

	if((P4IFG & BIT2) == BIT2)
	{
		lighten();
		P4IFG &= ~BIT2;          //清除中断标志
	}

	else if((P4IFG & BIT3) == BIT3)
	{
		darken();
		P4IFG &= ~BIT3;         //清除中断标志
	}

}
