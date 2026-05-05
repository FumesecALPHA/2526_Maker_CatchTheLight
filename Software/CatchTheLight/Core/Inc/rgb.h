/*
 * rgb.h
 *
 *  Created on: Apr 29, 2026
 *      Author: SERAPHIN Bradley
 */

#ifndef INC_RGB_H_
#define INC_RGB_H_

#include "main.h"
#include "time.h"

extern TIM_HandleTypeDef htim1;

void set_led_rgb(int led_idx, uint8_t r, uint8_t g, uint8_t b);
void setup(void);
void loop(void);
void eteindre_RGB_all (void);
void un (int num_chiffre, char color);
void deux (int num_chiffre, char color);
void trois (int num_chiffre, char color);
void quatre (int num_chiffre, char color);
void cinq (int num_chiffre, char color);
void six (int num_chiffre, char color);
void sept (int num_chiffre, char color);
void huit (int num_chiffre, char color);
void neuf (int num_chiffre, char color);
void zero (int num_chiffre, char color);

#endif /* INC_RGB_H_ */
