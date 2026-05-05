/*
 * button.h
 *
 *  Created on: Apr 19, 2026
 *      Author: SERAPHIN Bradley
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include "led.h"
#include <utils.h>

typedef struct
{
	GPIO_TypeDef* port;
	uint16_t pin;
	uint8_t id_joueur; // 1 pour J1, 2 pour J2
	uint8_t last_state;
	uint32_t last_debounce_time;
} Button;


void test(void);
void Scan_Buttons(void);
void Check(int i);

#endif /* INC_BUTTON_H_ */
