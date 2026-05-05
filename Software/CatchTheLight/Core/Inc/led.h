/*
 * led.h
 *
 *  Created on: Apr 20, 2026
 *      Author: SERAPHIN Bradley
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "main.h"

typedef struct
{
	GPIO_TypeDef* port;
	uint16_t pin;
	uint8_t id_joueur; // 1 pour J1, 2 pour J2
	uint8_t state;
} Led;

typedef enum {
    FIXE,
    CHENILLARD,
	CHENILLARD2,
	CHENILLARD3,
    CLIGNOTEMENT_ALL,
	STAR
} Animation_t;

void AllumerLed(int index);
void EteindreLed(int index);
void AllumerAll(void);
void AllumerJ1(void);
void AllumerJ2(void);
void EteindreAll(void);
int give_state_Led(int index);
int give_idJ_Led(int index);
void blinking_all(void);
void blinking_J1(void);
void blinking_J2(void);
void chenillard(void);
void chenillard2(void);
void inv_chenillard(void);
void inv_chenillard2(void);
void AnimationWait(Animation_t mode);

#endif /* INC_LED_H_ */
