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
			auxlist->valida=false;
			auxlist->jogador=1;
		}
		if(auxlist->posicao==29 || auxlist->posicao==36){

			inserePeca(auxlist->posicaoX,auxlist->posicaoY,2);
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

	int enemy=0;
	int validacoes=0;
	bool valida=false;

	if(player==1)
		enemy=2;
	else if(player==2)
		enemy=1;
	validacoes+=verSeValidaHorizontal(list,posi,player,enemy);

	validacoes+=verSeValidaVertical(list,posi,player,enemy);

	validacoes+=verSeValidaDiagonalSubir(list,posi,player,enemy);

	validacoes+=verSeValidaDiagonalDesc(list,posi,player,enemy);

	if(validacoes!=0)//comentado apenas para testes
		valida=true;




return valida;
}


pfnode getPosicao(pfnode list,int posi){ // @suppress("No return")

	pfnode auxlist=list;
	while(auxlist!=NULL){
			if(auxlist->posicao==posi){
				return auxlist;
			}
			auxlist=auxlist->next;
		}
	return list;//so para calar o compilador
}



int verSeValidaHorizontal(pfnode list,int posi,int player, int enemy){

/*
	pfnode auxList=list;
	pfnode auxPos=NULL;
	//pfnode pos=getPosicao(list, posi);
	auxList=list;//reset ao aux list

for(int i=0;i<8;i++){//vai pecorrer a matris toda de 8 em 8 de cima para baixo
	auxPos=getPosicao(auxList,posi+1);
		if(auxPos->posicaoY>(BSP_LCD_GetYSize()-(BSP_LCD_GetYSize()/10)))//se chegar ao limite de baixo do ecrâ
				return 0;
		if(auxPos->jogador==enemy){
			return 1;
		}
}
auxList=list;//reset ao aux list
for(int i=0;i<8;i++){//vai pecorrer a matris toda de 8 em 8 de cima para baixo
	auxPos=getPosicao(auxList,posi-1);
		if(auxPos->posicaoY>(BSP_LCD_GetYSize()-(BSP_LCD_GetYSize()/10)))//se chegar ao limite de baixo do ecrâ
				return 0;
		if(auxPos->jogador==enemy){
			return 1;
		}
}
*/

return 0;
}


int verSeValidaVertical(pfnode list,int posi,int player, int enemy){

	pfnode auxList=list;
	pfnode auxPos=NULL;
	//pfnode pos=getPosicao(list, posi);
	auxList=list;//reset ao aux list

	for (int i = 0; i < 8; i++) { //vai pecorrer a matris toda de 8 em 8 de cima para baixo
		auxPos = getPosicao(auxList, posi + i * 8);
		if (auxPos->posicaoY > (BSP_LCD_GetYSize() - (BSP_LCD_GetYSize() / 10))) //se chegar ao limite de baixo do ecrâ
			return 0;
		if (auxPos->jogador == enemy) {
			return 1;
		}
	}
	auxList = list; //reset ao aux list
	for (int i = 0; i < 8; i++) { //vai pecorrer a matris toda de 8 em 8 de cima para baixo
		auxPos = getPosicao(auxList, posi - i * 8);
		if (auxPos->posicaoY > (BSP_LCD_GetYSize() - (BSP_LCD_GetYSize() / 10))) //se chegar ao limite de baixo do ecrâ
			return 0;
		if (auxPos->jogador == enemy) {
			return 1;
		}
	}
	return 0;
}

int verSeValidaDiagonalSubir(pfnode list,int posi,int player, int enemy){

	//pfnode auxlist=list;
	//pfnode auxposicao=NULL;
	for(int i=0;i<8;i++){
		//auxposicao=getPosicao(list,posi);


	}
return 0;
}

int verSeValidaDiagonalDesc(pfnode list,int posi,int player, int enemy){

	//pfnode auxlist=list;
	//pfnode auxposicao=NULL;
	for(int i=0;i<8;i++){
		//auxposicao=getPosicao(list,posi);


	}
return 0;
}






















