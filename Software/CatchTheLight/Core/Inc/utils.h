/*
 * utils.h
 *
 *  Created on: Apr 20, 2026
 *      Author: SERAPHIN Bradley
 */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include "button.h"
#include "led.h"
#include "rgb.h"
#include <stdlib.h>
#include <time.h>

typedef enum {
    WAIT,
    GAME,
    GAME_OVER
} GameState_t;

#define NBbuttons 10

void random_idx(int *idx1, int *idx2);
void random_idx_J1(int *idx1);
void random_idx_J2(int *idx2);
void test_led(void);
void SETUP(void);
void LOOP(void);
void Winner(void);
void Game(void);

#endif /* INC_UTILS_H_ */
