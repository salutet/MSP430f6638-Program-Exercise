/*****************************
led 每隔10s点亮 再过6s熄灭
*****************************/

#include <msp430f6638.h>

unsigned int counter=0;

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;
	P4DIR |= BIT4 + BIT5 + BIT6;

	TA0CTL = TASSEL_1 + MC_1 + TACLR +TAIE;              //TA0控制寄存器：时钟源选择为ACLK 工作模式选择为增记数  清0
//	TA0CTL = TASSEL_1 + MC_1 + TACLR;                    //TA0控制寄存器：时钟源选择为ACLK 工作模式选择为增记数  清0
//	TA0CCTL0 |= CCIE;                                    //TA0CCTL0中断使能
	TA0CCR0 = 32767;                                     //32768/32768=1S
	_BIS_SR(LPM0_bits + GIE);
}

//#pragma vector = TIMER0_A0_VECTOR
#pragma vector = TIMER0_A1_VECTOR
__interrupt void TA0 (void)
{
		switch(TA0IV)
		{
		    case 0: break;
		    case 2: break;
		    case 4: break;
		    case 6: break;
		    case 8: break;
		    case 10: break;
			case 12: break;
	        case 14:counter++;
	        if (counter == 10)
	        	P4OUT |= BIT4 + BIT5 + BIT6;
	        if(counter == 16)
	        	{
	        		P4OUT &= ~(BIT4 + BIT5 + BIT6);
	        		counter = 0;
	        	}
	        break;
		}
}
//{
//	counter++;
//	if (counter == 10)
//		P4OUT |= BIT4 + BIT5 + BIT6;
//	if(counter == 16)
//		{
//		P4OUT &= ~(BIT4 + BIT5 + BIT6);
//		counter = 0;
//		}
//}
