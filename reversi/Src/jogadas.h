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
#define limiteEsquerdo BSP_LCD_GetXSize() / 10




typedef struct jogadas fnode,*pfnode;

struct jogadas{

	 bool valida;
	 int posicao;//de 1 a 64
	 unsigned int posicaoX;//poonta superior esquerda do rectangulo
	 unsigned int posicaoY;

	 bool ja_jogada;

	pfnode next;

};



pfnode addJogada(bool validat,int possicao,int possicaot,int possicaoy,bool ja_jogadat,pfnode lista);

void insereAs4inic(pfnode list);
void inserePeca(int a,int b,bool x);

#endif /* JOGADAS_H_ */
