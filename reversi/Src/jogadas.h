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

pfnode getPosicao(pfnode list,int posi);
bool seraValida(pfnode list,int posi,int jogador);

int verSeValidaHorizontal(pfnode list,int posi,int jogador, int enemy);
int verSeValidaVertical(pfnode list,int posi,int jogador, int enemy);
int verSeValidaDiagonalSubir(pfnode list,int posi,int jogador, int enemy);
int verSeValidaDiagonalDesc(pfnode list,int posi,int jogador, int enemy);


#endif /* JOGADAS_H_ */





/*


char e=enemy;                 //enemy piece
 char p=player;                 //player piece
 int m,n,val,poss= i*10+j;

 for(m=j+2; m<9; m++){
     if(mat[i][j+1]==e && mat[i][m]==p){
         val=check_reps(poss_list, index,poss);
         if(val==0){
            poss_list[index]=poss;
            index++;
            break;
         }
     } else if(mat[i][m]=='.'){
            break;
     }
 }

for(m=j-2; m>0; m--){
     if(mat[i][j-1]==e && mat[i][m]==p){
         val=check_reps(poss_list, index,poss);
         if(val==0){
            poss_list[index]=poss;
            index++;
            break;
         }
     } else if(mat[i][m]=='.'){
            break;
     }
 }

*/

































