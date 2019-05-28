/*
 * jogadas.h
 *
 *  Created on: 28/05/2019
 *      Author: Diogo e Rosa
 */

#ifndef JOGADAS_H_
#define JOGADAS_H_
//includes
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "stm32f769i_discovery_lcd.h"
#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_ts.h"

//defines
#define QUADRADO BSP_LCD_GetYSize()/10 //a mudar se o ecra for diferente





typedef struct jogadas fnode,*pfnode;

struct jogadas{

	unsigned int valida;
	unsigned int possicao;//de 1 a 64
	unsigned int possicaoX;
	unsigned int possicaoY;
	bool ja_jogada;
	pfnode next;

};



pfnode addJogada(int validat,int possicao,int possicaot,int possicaoy,bool ja_jogadat,pfnode lista);

void insereAs4inic(pfnode list);
void inserePeca(int a,int b);

#endif /* JOGADAS_H_ */
