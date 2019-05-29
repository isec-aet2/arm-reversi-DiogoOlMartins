/*
 * jogadas.c
 *
 *  Created on: 28/05/2019
 *      Author: Diogo e Rosa
 */

#include "jogadas.h"





pfnode addJogada(bool validat,int posicao,int posicaox,int posicaoy,pfnode lista){

	char erro[100];
	pfnode auxLista=lista;

	pfnode aux = malloc(sizeof(fnode));

	if(aux==NULL){
		sprintf(erro, "ERROR ALOCATING MEMORY");

		BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, BSP_LCD_GetYSize()/2, (uint8_t *) erro, LEFT_MODE);
	}

	aux->valida=validat;
	aux->posicao=posicao;
	aux->posicaoX=posicaox;
	aux->posicaoY=posicaoy;
	aux->jogador=0;
	aux->ja_jogada=false;
	aux->next=NULL;

	if(lista==NULL)
		return aux;
	else{
		while(auxLista!=NULL){

			if(auxLista->next==NULL){
				auxLista->next=aux;
				return lista;
			}

			auxLista=auxLista->next;
		}
	}
 return lista;//está aqui só para não dar warning
}


void insereAs4inic(pfnode list,int player){

	pfnode auxlist=list;

	while(auxlist!=NULL){
		if(auxlist->posicao==28 || auxlist->posicao==37){

			inserePeca(auxlist->posicaoX,auxlist->posicaoY,1);
			auxlist->ja_jogada=true;
			auxlist->jogador=1;
		}
		if(auxlist->posicao==29 || auxlist->posicao==36){

			inserePeca(auxlist->posicaoX,auxlist->posicaoY,2);
			auxlist->ja_jogada=true;
			auxlist->jogador=2;
		}
		auxlist=auxlist->next;
	}
}


void inserePeca(int a,int b,int jogador){

	a=a+QUADRADO/2;
	b=b+QUADRADO/2;

	if(jogador==1){
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawCircle(a,b, QUADRADO/2-8);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillCircle(a,b, QUADRADO/2-9);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK); //para garantir que a estrita está a preto

	}else if(jogador==2){
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_DrawCircle(a,b, QUADRADO/2-8);
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_FillCircle(a,b, QUADRADO/2-9);
	}

}

bool seraValida(pfnode list,int posi,int player){//vai ver em todas as direções se a jogada é valida

	pfnode auxlist=list;

	int enemy=0;
	int validacoes=0;
	bool valida=false;

	if(player==1)
		enemy=2;
	else if(player==2)
		enemy=1;
	validacoes=verSeValidaHorizontal(auxlist,posi,player,enemy);
	auxlist=list;
	validacoes=verSeValidaVertical(auxlist,posi,player,enemy);
	auxlist=list;
	validacoes=verSeValidaDiagonalSubir(auxlist,posi,player,enemy);
	auxlist=list;
	validacoes=verSeValidaDiagonalDesc(auxlist,posi,player,enemy);

	if(validacoes!=0)//comentado apenas para testes
		valida=true;




return valida;
}


pfnode getPosicao(pfnode list,int x, int y){ // @suppress("No return")



	pfnode auxlist=list;

	while(auxlist!=NULL){
		if (x<auxlist->posicaoX+QUADRADO && x>LIMITE_ESQUERDO && y<auxlist->posicaoY+QUADRADO && y>LIMITE_SUPERIOR){
			return auxlist;
		}
			auxlist=auxlist->next;
		}
	return list;//so para calar o compilador
}



int verSeValidaHorizontal(pfnode list,int posi,int player, int enemy){




return 0;
}


int verSeValidaVertical(pfnode list,int posi,int player, int enemy){


	return 0;
}

int verSeValidaDiagonalSubir(pfnode list,int posi,int player, int enemy){


	return 0;
}

int verSeValidaDiagonalDesc(pfnode list,int posi,int player, int enemy){

	return 0;
}






















