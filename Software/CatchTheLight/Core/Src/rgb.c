/*
 * rgb.c
 *
 *  Created on: Apr 29, 2026
 *      Author: SERAPHIN Bradley
 */

#include "rgb.h"

// Configuration du ruban
#define NUM_LEDS 7*8           // Nombre de LEDs à commander pour le test
#define RESET_PULSES 60       // Signal de reset (> 50us)
#define BUFFER_SIZE (NUM_LEDS * 24) + RESET_PULSES

// Valeurs PWM pour ARR = 99 (80MHz)
// 0.4us (High) / 1.25us (Total) -> environ 32
// 0.8us (High) / 1.25us (Total) -> environ 64
#define WS2812_0 32
#define WS2812_1 64

// Tableau de données pour le DMA (16 bits pour correspondre au Half-Word)
uint16_t led_buffer[BUFFER_SIZE];

/**
 * @brief Modifie la couleur d'une LED spécifique dans le buffer
 * @param r Rouge (0-255), g Vert (0-255), b Bleu (0-255)
 */
void set_led_rgb(int led_idx, uint8_t r, uint8_t g, uint8_t b)
{
	if (led_idx >= NUM_LEDS) return;

	// Le protocole WS2812B attend l'ordre Vert-Rouge-Bleu (GRB)
	uint32_t color = (g << 16) | (r << 8) | b;

	for (int i = 0; i < 24; i++) {
		if (color & (1 << (23 - i))) {
			led_buffer[led_idx * 24 + i] = WS2812_1;
		} else {
			led_buffer[led_idx * 24 + i] = WS2812_0;
		}
	}
}

void setup(void) {
	// 1. Initialisation du buffer à 0
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		led_buffer[i] = 0;
	}

	// 2. On prépare quelques couleurs pour le test
//	set_led_rgb(0, 100, 100, 100);
//	set_led_rgb(1, 0, 100, 0);   // LED 2 : Vert
//	set_led_rgb(2, 0, 0, 100);   // LED 3 : Bleu
//	set_led_rgb(3, 100, 0, 0);	// LED 1 : Rouge
//	set_led_rgb(4, 100, 100, 0);
//	set_led_rgb(5, 100, 0, 100);
//	set_led_rgb(6, 0, 100, 100);
}

void loop(void) {
	// 3. Envoi des données via DMA sur TIM3_CH1 (Pin PA6 / D12)
	// On force le cast en (uint32_t*) pour satisfaire la fonction HAL
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE);

	// 4. Petit clignotement pour tester
	HAL_Delay(500);

	// On éteint tout dans le buffer
	for (int i = 0; i < NUM_LEDS * 24; i++)
	{
		led_buffer[i] = WS2812_0;
	}
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE);

	HAL_Delay(500);

	// On remet les couleurs
	set_led_rgb(0, 100, 100, 100);
	set_led_rgb(1, 0, 100, 0);
	set_led_rgb(2, 0, 0, 100);
	set_led_rgb(3, 100, 0, 0);
	set_led_rgb(4, 100, 100, 0);
	set_led_rgb(5, 100, 0, 100);
	set_led_rgb(6, 0, 100, 100);
}

void eteindre_RGB_all (void)
{
	for (int i = 0; i < NUM_LEDS * 24; i++)
	{
		led_buffer[i] = WS2812_0;
	}
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE);
}

//1
void un (int num_chiffre, char color)
{
	int décal=(num_chiffre-1)*7;
	int r;
	int g;
	int b;

	switch(color)
	{
	case 'r': // Red
		r = 125;
		g = 0;
		b = 0;
		break;
	case 'b': // Blue
		r = 0;
		g = 0;
		b = 125;
		break;
	case 'w':  // White
		r = 100;
		g = 100;
		b = 100;
		break;
	}

	//Eteindre toutes les leds du chiffres
	for(int i = 0; i < 7; i++)
	{
		set_led_rgb(i+décal, 0, 0, 0);
	}
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE);

	//On définie les couleurs et le décalage en fonction du chiffre

	set_led_rgb(0+décal,0,0,0);
	set_led_rgb(1+décal,0,0,0);
	set_led_rgb(2+décal,0,0,0);
	set_led_rgb(3+décal,r,g,b);
	set_led_rgb(4+décal,r,g,b);
	set_led_rgb(5+décal,0,0,0);
	set_led_rgb(6+décal,0,0,0);

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE); //On allume les leds
}

//2
void deux (int num_chiffre, char color)
{
	int décal=(num_chiffre-1)*7;
	int r;
	int g;
	int b;

	switch(color)
	{
	case 'r': // Red
		r = 125;
		g = 0;
		b = 0;
		break;
	case 'b': // Blue
		r = 0;
		g = 0;
		b = 125;
		break;
	case 'w':  // White
		r = 100;
		g = 100;
		b = 100;
		break;
	}

	//Eteindre toutes les leds du chiffres
	for(int i = 0; i < 7; i++)
	{
		set_led_rgb(i+décal, 0, 0, 0);
	}
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE);

	//On définie les couleurs et le décalage en fonction du chiffre

	set_led_rgb(0+décal,r,g,b);
	set_led_rgb(1+décal,r,g,b);
	set_led_rgb(2+décal,r,g,b);
	set_led_rgb(3+décal,0,0,0);
	set_led_rgb(4+décal,r,g,b);
	set_led_rgb(5+décal,r,g,b);
	set_led_rgb(6+décal,0,0,0);

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE); //On allume les leds
}

//3
void trois (int num_chiffre, char color)
{
	int décal=(num_chiffre-1)*7;
	int r;
	int g;
	int b;

	switch(color)
	{
	case 'r': // Red
		r = 125;
		g = 0;
		b = 0;
		break;
	case 'b': // Blue
		r = 0;
		g = 0;
		b = 125;
		break;
	case 'w':  // White
		r = 100;
		g = 100;
		b = 100;
		break;
	}

	//Eteindre toutes les leds du chiffres
	for(int i = 0; i < 7; i++)
	{
		set_led_rgb(i+décal, 0, 0, 0);
	}
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE);

	//On définie les couleurs et le décalage en fonction du chiffre

	set_led_rgb(0+décal,r,g,b);
	set_led_rgb(1+décal,0,0,0);
	set_led_rgb(2+décal,r,g,b);
	set_led_rgb(3+décal,r,g,b);
	set_led_rgb(4+décal,r,g,b);
	set_led_rgb(5+décal,r,g,b);
	set_led_rgb(6+décal,0,0,0);

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE); //On allume les leds
}

//4
void quatre (int num_chiffre, char color)
{
	int décal=(num_chiffre-1)*7;
	int r;
	int g;
	int b;

	switch(color)
	{
	case 'r': // Red
		r = 125;
		g = 0;
		b = 0;
		break;
	case 'b': // Blue
		r = 0;
		g = 0;
		b = 125;
		break;
	case 'w':  // White
		r = 100;
		g = 100;
		b = 100;
		break;
	}

	//Eteindre toutes les leds du chiffres
	for(int i = 0; i < 7; i++)
	{
		set_led_rgb(i+décal, 0, 0, 0);
	}
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE);

	//On définie les couleurs et le décalage en fonction du chiffre

	set_led_rgb(0+décal,r,g,b);
	set_led_rgb(1+décal,0,0,0);
	set_led_rgb(2+décal,0,0,0);
	set_led_rgb(3+décal,r,g,b);
	set_led_rgb(4+décal,r,g,b);
	set_led_rgb(5+décal,0,0,0);
	set_led_rgb(6+décal,r,g,b);

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE); //On allume les leds
}

//5
void cinq (int num_chiffre, char color)
{
	int décal=(num_chiffre-1)*7;
	int r;
	int g;
	int b;

	switch(color)
	{
	case 'r': // Red
		r = 125;
		g = 0;
		b = 0;
		break;
	case 'b': // Blue
		r = 0;
		g = 0;
		b = 125;
		break;
	case 'w':  // White
		r = 100;
		g = 100;
		b = 100;
		break;
	}

	//Eteindre toutes les leds du chiffres
	for(int i = 0; i < 7; i++)
	{
		set_led_rgb(i+décal, 0, 0, 0);
	}
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE);

	//On définie les couleurs et le décalage en fonction du chiffre

	set_led_rgb(0+décal,r,g,b);
	set_led_rgb(1+décal,0,0,0);
	set_led_rgb(2+décal,r,g,b);
	set_led_rgb(3+décal,r,g,b);
	set_led_rgb(4+décal,0,0,0);
	set_led_rgb(5+décal,r,g,b);
	set_led_rgb(6+décal,r,g,b);

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE); //On allume les leds
}

//6
void six (int num_chiffre, char color)
{
	int décal=(num_chiffre-1)*7;
	int r;
	int g;
	int b;

	switch(color)
	{
	case 'r': // Red
		r = 125;
		g = 0;
		b = 0;
		break;
	case 'b': // Blue
		r = 0;
		g = 0;
		b = 125;
		break;
	case 'w':  // White
		r = 100;
		g = 100;
		b = 100;
		break;
	}

	//Eteindre toutes les leds du chiffres
	for(int i = 0; i < 7; i++)
	{
		set_led_rgb(i+décal,0,0,0);
	}
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE);

	//On définie les couleurs et le décalage en fonction du chiffre

	set_led_rgb(0+décal,r,g,b);
	set_led_rgb(1+décal,r,g,b);
	set_led_rgb(2+décal,r,g,b);
	set_led_rgb(3+décal,r,g,b);
	set_led_rgb(4+décal,0,0,0);
	set_led_rgb(5+décal,r,g,b);
	set_led_rgb(6+décal,r,g,b);

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE); //On allume les leds
}

//7
void sept (int num_chiffre, char color)
{
	int décal=(num_chiffre-1)*7;
	int r;
	int g;
	int b;

	switch(color)
	{
	case 'r': // Red
		r = 125;
		g = 0;
		b = 0;
		break;
	case 'b': // Blue
		r = 0;
		g = 0;
		b = 125;
		break;
	case 'w':  // White
		r = 100;
		g = 100;
		b = 100;
		break;
	}

	//Eteindre toutes les leds du chiffres
	for(int i = 0; i < 7; i++)
	{
		set_led_rgb(i+décal, 0, 0, 0);
	}
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE);

	//On définie les couleurs et le décalage en fonction du chiffre

	set_led_rgb(0+décal,0,0,0);
	set_led_rgb(1+décal,0,0,0);
	set_led_rgb(2+décal,0,0,0);
	set_led_rgb(3+décal,r,g,b);
	set_led_rgb(4+décal,r,g,b);
	set_led_rgb(5+décal,r,g,b);
	set_led_rgb(6+décal,0,0,0);

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE); //On allume les leds
}

//8
void huit (int num_chiffre, char color)
{
	int décal=(num_chiffre-1)*7;
	int r;
	int g;
	int b;

	switch(color)
	{
	case 'r': // Red
		r = 125;
		g = 0;
		b = 0;
		break;
	case 'b': // Blue
		r = 0;
		g = 0;
		b = 125;
		break;
	case 'w':  // White
		r = 100;
		g = 100;
		b = 100;
		break;
	}

	//Eteindre toutes les leds du chiffres
	for(int i = 0; i < 7; i++)
	{
		set_led_rgb(i+décal, 0, 0, 0);
	}
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE);

	//On définie les couleurs et le décalage en fonction du chiffre

	set_led_rgb(0+décal,r,g,b);
	set_led_rgb(1+décal,r,g,b);
	set_led_rgb(2+décal,r,g,b);
	set_led_rgb(3+décal,r,g,b);
	set_led_rgb(4+décal,r,g,b);
	set_led_rgb(5+décal,r,g,b);
	set_led_rgb(6+décal,r,g,b);

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE); //On allume les leds
}

//9
void neuf (int num_chiffre, char color)
{
	int décal=(num_chiffre-1)*7;
	int r;
	int g;
	int b;

	switch(color)
	{
	case 'r': // Red
		r = 125;
		g = 0;
		b = 0;
		break;
	case 'b': // Blue
		r = 0;
		g = 0;
		b = 125;
		break;
	case 'w':  // White
		r = 100;
		g = 100;
		b = 100;
		break;
	}

	//Eteindre toutes les leds du chiffres
	for(int i = 0; i < 7; i++)
	{
		set_led_rgb(i+décal, 0, 0, 0);
	}
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE);

	//On définie les couleurs et le décalage en fonction du chiffre

	set_led_rgb(0+décal,r,g,b);
	set_led_rgb(1+décal,0,0,0);
	set_led_rgb(2+décal,r,g,b);
	set_led_rgb(3+décal,r,g,b);
	set_led_rgb(4+décal,r,g,b);
	set_led_rgb(5+décal,r,g,b);
	set_led_rgb(6+décal,r,g,b);

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE); //On allume les leds
}

//0
void zero (int num_chiffre, char color)
{
	int décal=(num_chiffre-1)*7;
	int r;
	int g;
	int b;

	switch(color)
	{
	case 'r': // Red
		r = 125;
		g = 0;
		b = 0;
		break;
	case 'b': // Blue
		r = 0;
		g = 0;
		b = 125;
		break;
	case 'w':  // White
		r = 100;
		g = 100;
		b = 100;
		break;
	}

	//Eteindre toutes les leds du chiffres
	for(int i = 0; i < 7; i++)
	{
		set_led_rgb(i+décal, 0, 0, 0);
	}
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE);

	//On définie les couleurs et le décalage en fonction du chiffre

	set_led_rgb(0+décal,0,0,0);
	set_led_rgb(1+décal,r,g,b);
	set_led_rgb(2+décal,r,g,b);
	set_led_rgb(3+décal,r,g,b);
	set_led_rgb(4+décal,r,g,b);
	set_led_rgb(5+décal,r,g,b);
	set_led_rgb(6+décal,r,g,b);

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE); //On allume les leds
}
