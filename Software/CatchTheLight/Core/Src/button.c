/*
 * button.c
 *
 *  Created on: Apr 19, 2026
 *      Author: SERAPHIN Bradley
 */

#include "button.h"

Button Boutons[20] =
{
		// Joueur 1
		{GPIOC, GPIO_PIN_2, 1, 1, 0},//1
		{GPIOC, GPIO_PIN_3, 1, 1, 0},//2
		{GPIOA, GPIO_PIN_0, 1, 1, 0},//3
		{GPIOA, GPIO_PIN_1, 1, 1, 0},//4
		{GPIOA, GPIO_PIN_2, 1, 1, 0},//5
		{GPIOA, GPIO_PIN_3, 1, 1, 0},//6
		{GPIOA, GPIO_PIN_4, 1, 1, 0},//7
		{GPIOA, GPIO_PIN_5, 1, 1, 0},//8
		{GPIOA, GPIO_PIN_6, 1, 1, 0},//9
		{GPIOA, GPIO_PIN_7, 1, 1, 0},//10

		// Joueur 2
		{GPIOC, GPIO_PIN_4, 2, 1, 0},//1
		{GPIOC, GPIO_PIN_5, 2, 1, 0},//2
		{GPIOB, GPIO_PIN_0, 2, 1, 0},//3
		{GPIOB, GPIO_PIN_1, 2, 1, 0},//4
		{GPIOB, GPIO_PIN_2, 2, 1, 0},//5
		{GPIOB, GPIO_PIN_10, 2, 1, 0},//6
		{GPIOB, GPIO_PIN_11, 2, 1, 0},//7
		{GPIOB, GPIO_PIN_12, 2, 1, 0},//8
		{GPIOB, GPIO_PIN_13, 2, 1, 0},//9
		{GPIOB, GPIO_PIN_14, 2, 1, 0},//10
};

extern int scoreJ1;
extern int scoreJ2;
extern GameState_t State;

void test(void)
{
	for (int i = 0; i < 20; i++) {
		uint8_t state = HAL_GPIO_ReadPin(Boutons[i].port, Boutons[i].pin);

		// Anti-rebond (Debounce) : on vérifie que l'état est stable depuis 50ms
		if (state != Boutons[i].last_state) {
			if ((HAL_GetTick() - Boutons[i].last_debounce_time) > 50) {

				// Si l'état passe de 1 (relâché) à 0 (appuyé)
				if (state == 0)
				{
					int state_led = give_state_Led(i);
					switch(state_led)
					{
					case 1:
						EteindreLed(i);
						break;
					case 0:
						AllumerLed(i);
						break;
					}

				}

				Boutons[i].last_state = state;
				Boutons[i].last_debounce_time = HAL_GetTick();
			}
		}
	}
}

void Scan_Buttons(void)
{
	for (int i = 0; i < 20; i++) {
		uint8_t state = HAL_GPIO_ReadPin(Boutons[i].port, Boutons[i].pin);

		if (state != Boutons[i].last_state) {
			if ((HAL_GetTick() - Boutons[i].last_debounce_time) > 50) {

				// Si l'état passe de 1 (relâché) à 0 (appuyé)
				if (state == 0)
				{
//					int state_led = give_state_Led(i);
//					switch(state_led)
//					{
//					case 1:
//						EteindreLed(i);
//						break;
//					case 0:
//						AllumerLed(i);
//						break;
//					}
					Check(i);

				}

				Boutons[i].last_state = state;
				Boutons[i].last_debounce_time = HAL_GetTick();
			}
		}
	}
}

void Check(int i)
{
    if (State != GAME)
    {
    	return;
    }

    if (give_state_Led(i)== 1)
    {
        // GAGNÉ : La LED était allumée
        EteindreLed(i);

        if (give_idJ_Led(i)==1)
        {
        	scoreJ1++;
        }

        else if (give_idJ_Led(i)== 2)
        {
        	scoreJ2++;
        }
    }

    else if (give_state_Led(i)==0)
	{
        // PERDU : Appui sur une LED éteinte
        if (give_idJ_Led(i)==1)
        {
            if (scoreJ1 > 0)
            {
            	scoreJ1--;
            }

        }

        else if (give_idJ_Led(i)== 2)
        {
            if (scoreJ2 > 0)
            {
            	scoreJ2--;
            }
        }
    }

    // Optionnel : UpdateScoreDisplay(); // Mettre à jour tes rubans LED ici
}
