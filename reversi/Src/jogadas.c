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
	BSP_LCD_DrawCircle(a,b, QUADRADO/2-TAMMATRIZ );
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillCircle(a,b, QUADRADO/2-9);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK); //para garantir que a estrita está a preto

	}else if(jogador==2){
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_DrawCircle(a,b, QUADRADO/2-TAMMATRIZ );
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_FillCircle(a,b, QUADRADO/2-9);
	}

}

bool seraValida(pfnode list,pfnode posicao,int player){//vai ver em todas as direções se a jogada é valida

	pfnode auxlist=list;

	int enemy=0;
	int validacoes=0;
	bool valida=false;

	if(player==1)
		enemy=1;
	else if(player==2)
		enemy=2;
	validacoes+=verSeValidaHorizontal(auxlist,posicao,enemy);
	auxlist=list;
	validacoes+=verSeValidaVertical(auxlist,posicao,enemy);
	auxlist=list;
	validacoes+=verSeValidaDiagonalSubir(auxlist,posicao,enemy);
	auxlist=list;
	validacoes+=verSeValidaDiagonalDesc(auxlist,posicao,enemy);

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



int verSeValidaVertical(pfnode list,pfnode posicao, int enemy){
	pfnode auxlist=list;

	for(int i=1;i<TAMMATRIZ ;i++){
		auxlist=list;
		while(auxlist!=NULL){
			if(auxlist->posicaoX!=posicao->posicaoX ){//se nao estiver na coluna que queremos salta
				auxlist=auxlist->next;
				continue;
			}
			//se está aqui é porque está na coluna que queremos,
			//  temos agora de ver se está a sair da matriz
			if(auxlist->posicaoX+QUADRADO+1>LIMITE_INFERIOR){
				return 0;
			}
			if(auxlist->posicao==posicao->posicao+8*i && auxlist->ja_jogada==true && auxlist->jogador==enemy){

				return 1;
			}
			if(auxlist->posicao==posicao->posicao-8*i && auxlist->ja_jogada==true && auxlist->jogador==enemy){

				return 1;
			}

			auxlist=auxlist->next;
		}
	}

return 0;
}


int verSeValidaHorizontal(pfnode list,pfnode posicao, int enemy){
	pfnode auxlist=list;

	for(int i=1;i<TAMMATRIZ ;i++){
		auxlist=list;
		while(auxlist!=NULL){
			if(auxlist->posicaoY!=posicao->posicaoY ){//se não estiver na linha que queremos
				auxlist=auxlist->next;
				continue;
			}
			if(auxlist->posicaoX+QUADRADO+1>LIMITE_DIREITO){ //se está aqui é porque está na linha
				// que queremos, temos agora de ver se está a sair da matriz
				return 0;
			}
			if(auxlist->posicao==posicao->posicao+i*1 && auxlist->ja_jogada==true ){

				return 1;
			}
			if(auxlist->posicao==posicao->posicao-i*1 && auxlist->ja_jogada==true ){

				return 1;
			}

				auxlist=auxlist->next;
		}
	}


	return 0;
}

int verSeValidaDiagonalSubir(pfnode list,pfnode posicao, int enemy){
	pfnode auxlist=list;

	for(int i=1;i<TAMMATRIZ ;i++){
		auxlist=list;
		while(auxlist!=NULL){

			if(auxlist->posicaoY!=posicao->posicaoY && auxlist->posicaoX!=posicao->posicaoX){//se não estiver na linha que queremos
				auxlist=auxlist->next;
				continue;
			}
			if(auxlist->posicaoX+QUADRADO+1>LIMITE_DIREITO){ //se está aqui é porque está na linha
				// que queremos, temos agora de ver se está a sair da matriz
				return 0;
			}
			if(auxlist->posicao==posicao->posicao+7 && auxlist->ja_jogada==true){

				return 1;
			}
			if(auxlist->posicao==posicao->posicao-7 && auxlist->ja_jogada==true){

				return 1;
			}

				auxlist=auxlist->next;
		}
	}
	return 0;
}

int verSeValidaDiagonalDesc(pfnode list,pfnode posicao, int enemy){
/*
	pfnode auxlist=list;

	for(int i=1;i<TAMMATRIZ ;i++){
		auxlist=list;
		while(auxlist!=NULL){

			if(auxlist->posicaoX+QUADRADO+1>LIMITE_DIREITO){ //se está aqui é porque está na linha
				// que queremos, temos agora de ver se está a sair da matriz
				return 0;
			}
			if(auxlist->posicao==posicao->posicao+9 && auxlist->ja_jogada==true && auxlist->jogador==enemy){

				return 1;
			}
			if(auxlist->posicao==posicao->posicao-9 && auxlist->ja_jogada==true && auxlist->jogador==enemy){

				return 1;
			}

				auxlist=auxlist->next;
		}
	}
*/


	return 0;
}



void mostraJogador(int jogador){

	char desc[100]="Jogador";

	BSP_LCD_SetTextColor(LCD_COLOR_DARKGREEN);	//colorChange
	BSP_LCD_FillRect(QUADRADO*13+(QUADRADO/2), QUADRADO*3.5, QUADRADO, QUADRADO);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawRect(QUADRADO*13+(QUADRADO/2), QUADRADO*3.5, QUADRADO, QUADRADO);
	BSP_LCD_DrawRect(QUADRADO*13+(QUADRADO/2), QUADRADO*3.5, QUADRADO-1, QUADRADO-1);//fazer as linhas mais gordas
	BSP_LCD_DrawRect(QUADRADO*13-1+(QUADRADO/2),QUADRADO*3.5, QUADRADO, QUADRADO+1);//fazer as linhas mais gordas


	if(jogador==2){

		BSP_LCD_DisplayStringAt(QUADRADO*11,QUADRADO*3.75, (uint8_t *) desc, LEFT_MODE);

		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_DrawCircle(QUADRADO*14,QUADRADO*4, QUADRADO/2-TAMMATRIZ );
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillCircle(QUADRADO*14,QUADRADO*4, QUADRADO/2-9);
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

	}
	if(jogador==1){

		BSP_LCD_DisplayStringAt(QUADRADO*11,QUADRADO*3.75, (uint8_t *) desc, LEFT_MODE);

		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_DrawCircle(QUADRADO*14, QUADRADO*4, QUADRADO/2-TAMMATRIZ );
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_FillCircle(QUADRADO*14, QUADRADO*4, QUADRADO/2-9);

	}


}




void checkIfGameEnded(pfnode list){

	pfnode auxlist=list;
	int count=0;
	int countplayer1=0;
	int countplayer2=0;

	while(auxlist!=NULL){

		if(auxlist->ja_jogada==true)
			count++;
		if(auxlist->jogador==1)
			countplayer1++;

		if(auxlist->jogador==2)
			countplayer2++;

		count=60;
		countplayer1=10;
		countplayer2=11;
		if(count>=60){

			if(countplayer2>countplayer1){
				sendToSd(2,countplayer2);
			}else if(countplayer2<countplayer1){
				sendToSd(1,countplayer1);
			}else
				sendToSd(0,countplayer1);
			fazerReset();

		}
		auxlist=auxlist->next;

	}
}

void sendToSd(int jog, int a){

	char strings[100];
	uint n;
	if(jog==1){
	sprintf(strings,"player 1 ganhou com %d pontos \n",a);
	}
	if(jog==2){
	sprintf(strings,"player 2 ganhou com %d pontos \n",a);
	}
	if(jog==0){
	sprintf(strings,"empate com %d pontos \n",a);
	}

	if (f_mount(&SDFatFS, SDPath, 0) != FR_OK){
		Error_Handler();
	}

	if (f_open(&SDFile, "reversi.txt", FA_CREATE_ALWAYS | FA_WRITE ) != FR_OK){
		Error_Handler();
	}

		f_write(&SDFile, strings, strlen(strings), &n);
		f_close(&SDFile);

/**/

}











