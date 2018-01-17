#include <msp430.h>

#include "utils.h"
#include "chassis.h"
#include "adc.h"
#include "sensorInfrared.h"
#include "sensorLine.h"
#include "movement.h"
#include "display.h"

void testIR()
{
	ir_init();

	while (1)
	{
		if (ir_detect() == 1)
		{
			ut_led1(0);
			ut_led2(1);
		}
		else
		{
			ut_led1(1);
			ut_led2(0);
		}

		delay(50);
	}
}

void testLINE()
{
	li_init();

	while (1)
	{
		if (li_detect() == 1)
		{
			ut_led1(0);
			ut_led2(1);
		}
		else
		{
			ut_led1(1);
			ut_led2(0);
		}

		delay(50);
	}
}

void testDISPLAY()
{
	dis_init();
	
	dis_print(1234);
}

void main()
{
	ut_init();
	ch_init();
	adc_init();
	
	testLINE();
	
	//testIR();
	
	// testDISPLAY
}
