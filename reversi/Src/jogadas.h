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
#define LIMITE_ESQUERDO BSP_LCD_GetXSize() / 10
#define LIMITE_DIREITO LIMITE_ESQUERDO+(9*QUADRADO)
#define LIMITE_SUPERIOR QUADRADO
#define LIMITE_INFERIOR BSP_LCD_GetYSize()-QUADRADO



typedef struct jogadas fnode,*pfnode;

struct jogadas{


	 int posicao;//de 1 a 64
	 unsigned int posicaoX;//ponta superior esquerda do rectangulo
	 unsigned int posicaoY;
	 int jogador;
	 bool valida;
	 bool ja_jogada;

	pfnode next;

};



pfnode addJogada(bool validat,int possicao,int possicaot,int possicaoy,pfnode lista);

void insereAs4inic(pfnode list,int jogador);
void inserePeca(int a,int b,int jogador);

pfnode getPosicao(pfnode list,int x, int y);
bool seraValida(pfnode list,int posi,int jogador);

int verSeValidaHorizontal(pfnode list,int posi,int jogador, int enemy);
int verSeValidaVertical(pfnode list,int posi,int jogador, int enemy);
int verSeValidaDiagonalSubir(pfnode list,int posi,int jogador, int enemy);
int verSeValidaDiagonalDesc(pfnode list,int posi,int jogador, int enemy);


#endif /* JOGADAS_H_ */

































