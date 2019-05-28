/*
 * jogadas.c
 *
 *  Created on: 28/05/2019
 *      Author: Diogo e Rosa
 */

#include "jogadas.h"


//variaveis globais
bool jogador=true;

pfnode addJogada(int validat,int possicao,int possicaox,int possicaoy,bool ja_jogadat,pfnode lista){

	char erro[100];
	pfnode auxLista=lista;

	pfnode aux = malloc(sizeof(fnode));
	if(aux==NULL){
		sprintf(erro, "ERROR ALOCATING MEMORY");

		BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, BSP_LCD_GetYSize()/2, (uint8_t *) erro, LEFT_MODE);
	}

	aux->valida=validat;
	aux->possicao=possicao;
	aux->possicaoX=possicaox;
	aux->possicaoX=possicaoy;
	aux->ja_jogada=ja_jogadat;
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


void insereAs4inic(pfnode list){

	pfnode auxlist=list;

	while(auxlist!=NULL){
		if(auxlist->possicao==28 || auxlist->possicao==37)
			inserePeca(auxlist->possicaoX,auxlist->possicaoY);
		if(auxlist->possicao==29 || auxlist->possicao==36)
		auxlist=auxlist->next;
	}


}


void inserePeca(int a,int b){

	a=a-QUADRADO/2;
	b=b-QUADRADO/2;

	if(jogador==true)
		jogador=false;
	else
		jogador=true;

	if(jogador==true){
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawCircle(a,b, QUADRADO/2-8);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillCircle(a,b, QUADRADO/2-9);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK); //para garantir que a estrita está a preto

	}else{
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_DrawCircle(a,b, QUADRADO/2-8);
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_FillCircle(a,b, QUADRADO/2-9);
	}

}



