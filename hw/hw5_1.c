#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>                                                             
#include "8x8font.h"                                                            

#define BOARD_ROW 8     // board��의 Row                                        
#define PADDING 1;     // ��문��자��간��의 ��기��본��간��격                     

uint8_t *board[BOARD_ROW];      // board                                        
int     board_size;                                                             

// board��에 ��문��자 writing, margin-��이��전 ��문��자��와��의 ��간��격        
void boardWriter(int fontidx, int margin);                                      

int main(void)                                                                  
{                                                                               
	char str[50];                                                               
	int margin = 10;                                                            
	gets(str);                                                                  

	for(int i=0; str[i]!='\0' ; i++){                                           
		if(i!=0) margin = 0 ;                                                   

		if(str[i] == ' '){                                                      
			boardWriter(62, margin);                                            
		}                                                                       
		else if(str[i] >='a'){ // 'a' == 97                                     
			boardWriter(str[i]-71,margin);                                      
		}                                                                       
		else if(str[i]>='A'){ // 'A' == 65                                      
			boardWriter(str[i]-'A',margin);                                     
		}                                                                       
		else if(str[i]>='0'){ // '0' == 48                                      
			boardWriter(str[i]+4, margin);                                      
		}                                                                       
	}                                                                           
	for(int i = 0 ; i < BOARD_ROW ; i++){                                       
		for(int j = 0 ; j < board_size ; j++)                                   
			printf("%c ", board[i][j]);                                         
		printf("\n");                                                           
	}                                                                           

	return 0;                                                                   
}                                                                               

void boardWriter(int fontidx, int margin)                                       
{                                                                               
	int i, j;                                                                   
	static int board_offset = 0; // ��현��재 ��문��자��의 offset                
	uint8_t mask;                                                               
	uint8_t *new_board[BOARD_ROW];                                              

	int new_board_size = board_offset + margin + FONT_COL + PADDING;            

	for(i = 0 ; i < BOARD_ROW ; i++){                                           
		new_board[i] = (uint8_t*)calloc(1, new_board_size);                     
		memset(new_board[i], ' ', new_board_size);                              
		memcpy(new_board[i], board[i], board_size);                             
		free(board[i]);                                                         
		board[i] = new_board[i];                                                
	}                                                                           

	board_size = new_board_size;                                                
	board_offset += margin;                                                     

	// writing on the board                                                     
	for(i = 0 ; i < FONT_ROW ; i++){      // row                                
		for(j = 0 ; j < FONT_COL ; j++){  // col                                
			mask = 0b1 << (7-j);                                                
			if((mask & FONT88[fontidx][i]))                                     
				board[i][j+board_offset] = 'o';                                 
			else                                                                
				board[i][j+board_offset] = ' ';                                 
		}                                                                       
	}                                                                           
	board_offset = board_size;;                                                 
}  
