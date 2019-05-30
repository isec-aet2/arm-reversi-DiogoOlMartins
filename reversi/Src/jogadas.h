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
#include "fatfs.h"


//defines
#define TAMMATRIZ 8
#define TAMLCDX BSP_LCD_GetXSize()
#define TAMLCDY BSP_LCD_GetYSize()
#define QUADRADO TAMLCDY/10 //a mudar se o ecra for diferente
#define CENTROX TAMLCDX/2
#define CENTROY TAMLCDY/2
#define LIMITE_ESQUERDO TAMLCDX / 10
#define LIMITE_DIREITO LIMITE_ESQUERDO+(TAMMATRIZ*QUADRADO)
#define LIMITE_SUPERIOR QUADRADO
#define LIMITE_INFERIOR TAMLCDY-QUADRADO
#define SIZE 100





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
bool seraValida(pfnode list,pfnode posicao,int player);

int verSeValidaHorizontal(pfnode auxlist,pfnode posicao, int enemy);
int verSeValidaVertical(pfnode auxlist,pfnode posicao, int enemy);
int verSeValidaDiagonalSubir(pfnode auxlist,pfnode posicao, int enemy);
int verSeValidaDiagonalDesc(pfnode auxlist,pfnode posicao, int enemy);
void mostraJogador(int jogador);
void checkIfGameEnded(pfnode list, char b[SIZE]);
void fazerReset();
void sendToSd(int jog, int a ,char b[SIZE]);
void menuInicial(void);


#endif /* JOGADAS_H_ */

































