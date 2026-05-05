/*
 * utils.c
 *
 *  Created on: Apr 20, 2026
 *      Author: SERAPHIN Bradley
 */

#include "utils.h"

#define Port_START GPIOB
#define Pin_START GPIO_PIN_15
#define Port_SELECT GPIOC
#define Pin_SELECT GPIO_PIN_6
#define TIME_GAME 15000 //30sec

void random_idx(int *idx1, int *idx2)
{
	// Formule : rand() % (max - min + 1) + min
	*idx1 = rand() % 10 + 0;  // Donne un nombre entre 0 et 9
	*idx2 = rand() % 10 + 10; // Donne un nombre entre 10 et 19
}

void random_idx_J1(int *idx1)
{
	// Formule : rand() % (max - min + 1) + min
	*idx1 = rand() % 10 + 0;  // Donne un nombre entre 0 et 9
}

void random_idx_J2(int *idx2)
{
	// Formule : rand() % (max - min + 1) + min
	*idx2 = rand() % 10 + 10; // Donne un nombre entre 10 et 19
}

void test_led(void)
{
	AllumerAll();
	HAL_Delay(1000);
	EteindreAll();
	HAL_Delay(1000);
}

GameState_t State = WAIT;

uint32_t gameStartTime=0;
int time_over=5000;
uint32_t Led_Time=0;
int scoreJ1=0;
int scoreJ2=0;
int index1, index2;

// Index des LEDs actuellement allumées (-1 si aucune)
int currentLedJ1 = -1;
int currentLedJ2 = -1;

void SETUP(void)
{
	EteindreAll();
	eteindre_RGB_all();
	//	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,0);
	//	srand(HAL_GetTick());
	//	int index1, index2;
	//	random_idx(&index1, &index2);
	//	AllumerLed(index1);
	//	AllumerLed(index2);

}

Animation_t Mode = CHENILLARD;

void LOOP(void)
{
	Scan_Buttons();
	switch (State)
	{
	case WAIT:
		AnimationWait(Mode); // Ta fonction d'animation
		// Vérifie si le bouton START est appuyé (Active Low : 0)
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15) == GPIO_PIN_RESET)
		{
			EteindreAll();
			State = GAME;
			gameStartTime = HAL_GetTick();
		}
		break;

	case GAME:
		Game();
		// Vérifie la fin du jeu (30 secondes)
		if ((HAL_GetTick() - gameStartTime) > TIME_GAME)
		{
			EteindreAll();
			State = GAME_OVER;
		}
		break;

	case GAME_OVER:
		Winner();
		if ((HAL_GetTick() - gameStartTime) > TIME_GAME+time_over)
		{
			State = WAIT;
		}
		//HAL_Delay(5000); // Affiche le résultat 5s
		break;
	}
}


void Winner(void)
{
	if (scoreJ1>scoreJ2)
	{
		blinking_J1();
	}
	else if (scoreJ2>scoreJ1)
	{
		blinking_J2();
	}
	else
	{
		blinking_all();
	}
}

void Game(void)
{
	//	uint32_t now = HAL_GetTick();
	//
	//	// Toutes les 1000ms, on change les cibles
	//	if ((now - Led_Time) > 1000) {
	//		Led_Time = now;
	//
	//		// Éteindre les anciennes
	//		if(currentLedJ1 != -1) HAL_GPIO_WritePin(mesLeds[currentLedJ1].port, mesLeds[currentLedJ1].pin, 0);
	//		if(currentLedJ2 != -1) HAL_GPIO_WritePin(mesLeds[currentLedJ2].port, mesLeds[currentLedJ2].pin, 0);
	//
	//		// Choisir nouvelles LEDs (J1: index 0-9, J2: index 10-19)
	//		currentLedJ1 = rand() % 10;
	//		currentLedJ2 = 10 + (rand() % 10);
	//
	//		// Allumer les nouvelles
	//		HAL_GPIO_WritePin(mesLeds[currentLedJ1].port, mesLeds[currentLedJ1].pin, 1);
	//		HAL_GPIO_WritePin(mesLeds[currentLedJ2].port, mesLeds[currentLedJ2].pin, 1);
	//	}
	uint32_t now = HAL_GetTick();
	uint32_t time_spend = now - gameStartTime;
	uint32_t time_led_on;

//	int eteindre = 0;
//	if (eteindre==0)
//	{
//		EteindreAll();
//		eteindre=1;
//	}

//	if (time_spend<15000) {
//		time_led_on= 1000; // Première moitié : 1 seconde
//	} else {
//		time_led_on= 500;  // Deuxième moitié : 0.5 seconde (accélération)
//	}
	time_led_on= 300;
	if ((now - Led_Time) > time_led_on) {
		Led_Time = now;

		// --- JOUEUR 1 ---
		int tentativeJ1 = 0;
		// On cherche une LED éteinte (max 10 tentatives pour éviter une boucle infinie si tout est plein)
		do {
			random_idx_J1(&index1);
			tentativeJ1++;
		} while (give_state_Led(index1)== 1 && tentativeJ1 < 10);

		// Si on a trouvé une LED libre, on l'allume
		if (give_state_Led(index1) == 0)
		{
			AllumerLed(index1);
		}

		// --- JOUEUR 2 ---
		int tentativeJ2 = 0;
		do {
			random_idx_J2(&index2);
			tentativeJ2++;
		} while (give_state_Led(index2) == 1 && tentativeJ2 < 10);

		if (give_state_Led(index2)== 0)
		{
			AllumerLed(index2);
		}
	}
}


