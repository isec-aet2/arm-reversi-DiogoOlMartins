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
#include <time.h>
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

};



void insereAs4inic(fnode list[TAMMATRIZ][TAMMATRIZ],int player);
void inserePeca(int a,int b,int jogador);

fnode getPosicao(fnode list[TAMMATRIZ][TAMMATRIZ],int x, int y);

void mostraJogador(int jogador);
void checkIfGameEnded(void);
void fazerReset();
void sendToSd(int jog, int a ,char b[SIZE]);
void menuInicial(void);

void possible_move(void);
void poss_capt_h(int e,int p,int i,int j);
void poss_capt_v(int e,int p,int i,int j);
void poss_capt_dp(int e,int p,int i,int j);
void poss_capt_ds(int e,int p,int i,int j);
int check_reps(int jog);
void inserePosicaoPossivel(int x,int y,int jogador);
void poss_array_printer(void);
void poss_array_erasor(void);
void limpaPosicaoPossivel(int x,int y);
int jogouValida(int x, int y, fnode poss_listA[SIZE], int indice);

void inserePecaNaMatriz(void);
void piece_changer_h(int e,int p,int i, int j);
void piece_changer_v(int e,int p,int i, int j);
void piece_changer_dp(int e,int p,int i, int j);
void piece_changer_ds(int e,int p,int i, int j);
void place(void);
void redo(void);
int randomizado(int i);
void meteJogAI(void);
void redoMatriz(void);
void countMatriz(void);
void showPlayerPieces(void);

#endif /* JOGADAS_H_ */

































