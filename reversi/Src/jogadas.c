/*
 * jogadas.c
 *
 *  Created on: 28/05/2019
 *      Author: Diogo e Rosa
 */

#include "jogadas.h"


//variaveis globais


pfnode addJogada(bool validat,int posicao,int posicaox,int posicaoy,bool ja_jogadat,pfnode lista){

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
		if(auxlist->posicao==28 || auxlist->posicao==37){
			inserePeca(auxlist->posicaoX,auxlist->posicaoY,true);
			auxlist->valida=false;
		}
		if(auxlist->posicao==29 || auxlist->posicao==36)
			inserePeca(auxlist->posicaoX,auxlist->posicaoY,false);
		auxlist=auxlist->next;
	}


}


void inserePeca(int a,int b,bool x){

	a=a+QUADRADO/2;
	b=b+QUADRADO/2;

//	if(jogador==true)
//		jogador=false;
//	else
//		jogador=true;

	if(x==true){
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



