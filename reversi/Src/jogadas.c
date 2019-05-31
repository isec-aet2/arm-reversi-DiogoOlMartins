/*
 * jogadas.c
 *
 *  Created on: 28/05/2019
 *      Author: Diogo e Rosa
 */

#include "jogadas.h"



fnode getPosicao(fnode list[TAMMATRIZ][TAMMATRIZ],int x, int y){

	int j;
	int i;
    for(i=1;i<9;i++){
        for(j=1;j<9;j++){
        	if( x<list[i][j].posicaoX+QUADRADO && x>list[i][j].posicaoX
        			&& y<list[i][j].posicaoY+QUADRADO && y>list[i][j].posicaoY
        	){
        		return list[i][j];
        	}
        }
    }
    return list[i][j];
}


void insereAs4inic(fnode list[][TAMMATRIZ],int player){

			inserePeca(list[3][3].posicaoX,list[3][3].posicaoY,1);
			inserePeca(list[4][4].posicaoX,list[4][4].posicaoY,1);
			list[3][3].ja_jogada=true;
			list[3][3].jogador=2;
			list[4][4].ja_jogada=true;
			list[4][4].jogador=2;

			inserePeca(list[3][4].posicaoX,list[3][4].posicaoY,2);
			inserePeca(list[4][3].posicaoX,list[4][3].posicaoY,2);
			list[3][4].ja_jogada=true;
			list[3][4].jogador=1;
			list[4][3].ja_jogada=true;
			list[4][3].jogador=1;

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



void inserePosicaoPossivel(int x,int y,int jogador){


		BSP_LCD_SetTextColor(LCD_COLOR_LIGHTCYAN);	//colorChange
		BSP_LCD_FillRect(x, y, QUADRADO, QUADRADO);
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_DrawRect(x, y, QUADRADO, QUADRADO);
		BSP_LCD_DrawRect(x, y, QUADRADO-1, QUADRADO-1);//fazer as linhas mais gordas
		BSP_LCD_DrawRect(x-1, y-1, QUADRADO, QUADRADO+1);//fazer as linhas mais gordas

}

void limpaPosicaoPossivel(int x,int y){

	BSP_LCD_SetTextColor(LCD_COLOR_DARKGREEN);	//colorChange
	BSP_LCD_FillRect(x, y, QUADRADO, QUADRADO);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawRect(x, y, QUADRADO, QUADRADO);
	BSP_LCD_DrawRect(x, y, QUADRADO-1, QUADRADO-1);//fazer as linhas mais gordas
	BSP_LCD_DrawRect(x-1, y-1, QUADRADO, QUADRADO+1);//fazer as linhas mais gordas

}



int jogouValida(int x, int y, fnode poss_listA[SIZE], int indice){

	for(int i=0;i<indice;i++){
		if (x<poss_listA[i].posicaoX+QUADRADO && x>poss_listA[i].posicaoX
		&& y<poss_listA[i].posicaoY+QUADRADO && y>poss_listA[i].posicaoY
		){
			return 1;
		}
	}
	return 0;
}






void mostraJogador(int jogador){

	char desc[SIZE]="Jogador";

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







void sendToSd(int jog, int a ,char b[SIZE]){

	char strings[SIZE];
	uint n;
	if(jog==1){
	sprintf(strings,"\n player 1 ganhou com %d pontos ",a);
	strcat(strings,b);
	}
	if(jog==2){
	sprintf(strings,"\n player 2 ganhou com %d pontos ",a);
	strcat(strings,b);
	}
	if(jog==0){
	sprintf(strings,"\n empate com %d pontos ",a);
	strcat(strings,b);
	}
	if(jog==4){
	sprintf(strings,"\n player 1 ganhou por timeout");
	strcat(strings,b);
	}
	if(jog==5){
	sprintf(strings,"\n player 1 ganhou por timeout");
	strcat(strings,b);
	}


	if (f_mount(&SDFatFS, SDPath, 0) != FR_OK){
			Error_Handler();
		}

		if (f_open(&SDFile, "reversi.txt", FA_OPEN_APPEND | FA_WRITE ) != FR_OK){
			Error_Handler();
		}
		int x=strlen(strings)*sizeof(char);
		if(f_write(&SDFile, strings, x, &n) != FR_OK){
			Error_Handler();
		}

		f_close(&SDFile);


}











