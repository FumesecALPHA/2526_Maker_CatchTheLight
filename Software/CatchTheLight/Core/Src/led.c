/*
 * led.c
 *
 *  Created on: Apr 20, 2026
 *      Author: SERAPHIN Bradley
 */

#include "led.h"

Led Leds[20] =
{
		// Joueur 1
		{GPIOC, GPIO_PIN_7, 1, 0},//1
		{GPIOC, GPIO_PIN_8, 1, 0},//2
		{GPIOC, GPIO_PIN_9, 1, 0},//3
		{GPIOA, GPIO_PIN_8, 1, 0},//4
		{GPIOA, GPIO_PIN_9, 1, 0},//5
		{GPIOA, GPIO_PIN_10, 1, 0},//6
		{GPIOA, GPIO_PIN_11, 1, 0},//7
		{GPIOA, GPIO_PIN_12, 1, 0},//8
		{GPIOA, GPIO_PIN_15, 1, 0},//9
		{GPIOC, GPIO_PIN_10, 1, 0},//10

		// Joueur 2
		{GPIOC, GPIO_PIN_11, 2, 0},//1
		{GPIOC, GPIO_PIN_12, 2, 0},//2
		{GPIOD, GPIO_PIN_2, 2, 0},//3
		{GPIOB, GPIO_PIN_3, 2, 0},//4
		{GPIOB, GPIO_PIN_4, 2, 0},//5
		{GPIOB, GPIO_PIN_5, 2, 0},//6
		{GPIOB, GPIO_PIN_6, 2, 0},//7
		{GPIOB, GPIO_PIN_7, 2, 0},//8
		{GPIOF, GPIO_PIN_1, 2, 0},//9
		{GPIOB, GPIO_PIN_9, 2, 0},//10
};

void AllumerLed(int index)
{
	HAL_GPIO_WritePin(Leds[index].port,Leds[index].pin, SET);
	Leds[index].state = 1;
}

void EteindreLed(int index)
{
	HAL_GPIO_WritePin(Leds[index].port, Leds[index].pin, RESET);
	Leds[index].state = 0;
}

void AllumerAll(void)
{
	for (int i=0; i<20; i++)
	{
		AllumerLed(i);
	}
}

void AllumerJ1(void)
{
	for (int i=0; i<10; i++)
	{
		AllumerLed(i);
	}
}

void AllumerJ2(void)
{
	for (int i=10; i<20; i++)
	{
		AllumerLed(i);
	}
}

void EteindreAll(void)
{
	for (int i=0; i<20; i++)
	{
		EteindreLed(i);
	}
}

int give_state_Led(int index)
{
	return Leds[index].state;
}

int give_idJ_Led(int index)
{
	return Leds[index].id_joueur;
}

void blinking_all(void)
{
	static uint32_t last_tick=0;
	static uint8_t led_is_on=0;

	if (HAL_GetTick()-last_tick>=500)
	{
		last_tick=HAL_GetTick();

		if (led_is_on)
		{
			EteindreAll();
			led_is_on=0;
		}
		else
		{
			AllumerAll();
			led_is_on=1;
		}
	}
}

void blinking_J1(void)
{
	static uint32_t last_tick=0;
	static uint8_t led_is_on=0;

	if (HAL_GetTick()-last_tick>=500)
	{
		last_tick=HAL_GetTick();

		if (led_is_on)
		{
			EteindreAll();
			led_is_on=0;
		}
		else
		{
			AllumerJ1();
			led_is_on=1;
		}
	}
}

void blinking_J2(void)
{
	static uint32_t last_tick=0;
	static uint8_t led_is_on=0;

	if (HAL_GetTick()-last_tick >= 500)
	{
		last_tick=HAL_GetTick();

		if (led_is_on)
		{
			EteindreAll();
			led_is_on=0;
		}
		else
		{
			AllumerJ2();
			led_is_on=1;
		}
	}
}

static const int COLONNES[8][4]=
{
		{11-1, 12-1, 19-1, 20-1},   // Colonne 1 (Extrême gauche)
		{13-1, 16-1, 18-1, -1},  // Colonne 2
		{14-1, 17-1, -1, -1},  // Colonne 3
		{15-1, -1, -1, -1},  // Colonne 4
		{5-1, -1, -1, -1},  // Colonne 5
		{4-1, 7-1, -1,  -1},    // Colonne 6
		{3-1, 6-1, 8-1,  -1},	// Colonne 7
		{1-1, 2-1, 9-1,  10-1}	// Colonne 8 (Extrême droite)
};

static const int NB_LEDS_PAR_COL[8] = {4, 3, 2, 1, 1, 2, 3, 4};

void chenillard(void)
{
	static uint32_t last_tick = 0;
	static int col_index = 0;
	const uint32_t tempo = 500; // Vitesse de balayage

	if (HAL_GetTick() - last_tick >= tempo)
	{
		last_tick = HAL_GetTick();

		EteindreAll();

		// On parcourt la colonne actuelle (max 4 LEDs ici)
		for (int i = 0; i < 4; i++)
		{
			int led_id = COLONNES[col_index][i];
			if (led_id >= 0) { // On vérifie que ce n'est pas un index vide (-1)
				AllumerLed(led_id);
			}
		}

		// On passe à la colonne suivante sur 8 colonnes au total
		col_index = (col_index + 1) % 8;
	}
}

void chenillard2(void)
{
	static uint32_t last_tick = 0;
	static int col_index = 0;
	const uint32_t tempo = 500; // Vitesse de balayage

	if (HAL_GetTick() - last_tick >= tempo)
	{
		last_tick = HAL_GetTick();
		if (col_index==0)
		{
			EteindreAll();
		}

		// On parcourt la colonne actuelle (max 4 LEDs ici)
		for (int i = 0; i < 4; i++)
		{
			int led_id = COLONNES[col_index][i];
			if (led_id >= 0) { // On vérifie que ce n'est pas un index vide (-1)
				AllumerLed(led_id);
			}
		}

		// On passe à la colonne suivante sur 8 colonnes au total
		col_index = (col_index + 1) % 8;
	}
}

void inv_chenillard(void)
{
	static uint32_t last_tick = 0;
	static int col_index = 7;
	const uint32_t tempo = 500; // Vitesse de balayage

	if (HAL_GetTick() - last_tick >= tempo)
	{
		last_tick = HAL_GetTick();

		EteindreAll();

		// On parcourt la colonne actuelle (max 4 LEDs ici)
		for (int i = 0; i < 4; i++)
		{
			int led_id = COLONNES[col_index][i];
			if (led_id >= 0) { // On vérifie que ce n'est pas un index vide (-1)
				AllumerLed(led_id);
			}
		}

		col_index--;
		// On passe à la colonne suivante sur 8 colonnes au total
		if (col_index < 0)
		{
			col_index = 7;
		}
	}
}

void inv_chenillard2(void)
{
	static uint32_t last_tick = 0;
	static int col_index = 7;
	const uint32_t tempo = 500; // Vitesse de balayage

	if (HAL_GetTick() - last_tick >= tempo)
	{
		last_tick = HAL_GetTick();
		if (col_index==0)
		{
			EteindreAll();
		}

		// On parcourt la colonne actuelle (max 4 LEDs ici)
		for (int i = 0; i < 4; i++)
		{
			int led_id = COLONNES[col_index][i];
			if (led_id >= 0) { // On vérifie que ce n'est pas un index vide (-1)
				AllumerLed(led_id);
			}
		}

		col_index--;

		if (col_index < 0)
		{
			col_index = 7;
		};
	}
}

void AnimationWait(Animation_t mode)
{
	int start=0;
	switch(mode)
	{
	case CLIGNOTEMENT_ALL:
//		start=HAL_GetTick();
		blinking_all();
//		if (HAL_GetTick()-start>5000)
//		{
//			start=0;
//			mode=CHENILLARD;
//		}
		break;
	case CHENILLARD:
//		start=HAL_GetTick();
		chenillard();
//		if (HAL_GetTick()-start>5000)
//		{
//			start=0;
//			mode=CHENILLARD2;
//		}
		break;
	case CHENILLARD2:

		break;
	case CHENILLARD3:

		break;
	case FIXE:

		break;
	case STAR:

		break;
	}
}
