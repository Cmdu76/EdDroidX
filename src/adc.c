/*
 * adc.c
 *
 *  Created on: 13 janv. 2018
 *      Author: Cmdu76
 */

#include <msp430.h>
#include "utils.h"

///////////////////////////////////////////////////////////////
// Initialise l'ADC                                          //
///////////////////////////////////////////////////////////////
void adc_init()
{
	ADC10CTL0 = ADC10CTL1 = 0;

    ADC10CTL0 = SREF_0 + ADC10SHT_2 + REFON + REF2_5V + ADC10ON;
    ADC10CTL0 &= ~(ADC10SR);

    ADC10CTL1 |= (ADC10DIV_0 + ADC10SSEL_2 + SHS_0 + CONSEQ_0);
}

///////////////////////////////////////////////////////////////
// R�cup�re la valeur du capteur sur le pin sp�cifi�         //                                    //
///////////////////////////////////////////////////////////////
int adc_get(unsigned char pin)
{
    ADC10CTL1 |= (pin * 0x1000u);
    ADC10CTL0 |= ENC | ADC10SC;

    while (!(ADC10CTL0 & ADC10IFG) || (ADC10CTL1 & ADC10BUSY));

    ADC10CTL0 &= ~(ENC | ADC10IFG);
    ADC10CTL1 &= ~(pin * 0x1000u);

    return ADC10MEM;
}

///////////////////////////////////////////////////////////////
// R�cup�re la valeur de l'ADC avec un filtre passe bas      //
///////////////////////////////////////////////////////////////
int adc_getLow(unsigned char pin)
{
	int lp = 0;
	int i;
	for (i = 0; i < 64; i++)
	{
		lp += adc_get(pin);
	}
	return (lp >> 6);
}

