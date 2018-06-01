#include<stdio.h>                                                               
#include<string.h>                                                              
#include<pigpio.h>                                                              
#include "74hc595_functions.h"                                                  

void dot(int row, int col){                                                     
	uint8_t row8, col8;                                                         
	uint16_t tmp;                                                               
	row8 = ~(1 << (8-row));                                                     
	col8 = 1 << (8-col);                                                        
	tmp = (row8<<8) | col8;                                                     
	set16(tmp);                                                                 
}                                                                               

int cnt;                                                                        
void callback(void){                                                            
	cnt++;                                                                      
}                                                                               


int main(int argc, char * argv[]){                                              
	FILE * fp;                                                                  

	uint8_t *mat[8];                                                            
	char temp[1000];                                                            
	int len;                                                                    
	int i, j;                                                                   

	fp = fopen(argv[1], "r");                                                   

	if(fp!=NULL){                                                               

		for(i=0; i< 8 ; i++){                                                   
			fgets(temp, sizeof(temp), fp);                                      
			len = strlen(temp);                                                 

			if(feof(fp)) break;                                                 

			mat[i] = (uint8_t *)malloc(len * sizeof(uint8_t));                  

			for(j=0; j<len ; j++){                                              
				if(temp[j] =='o') mat[i][j] = 1;                                
				else mat[i][j] = 0;                                             
			}                                                                   
		}                                                                       
		fclose(fp);                                                             
	}                                                                           
	else{                                                                       
		printf("file open error\n");                                            
	}                                                                           


	int ret;                                                                    
	ret = init();                                                               
	if(ret == 0){                                                               
		printf("error\n");                                                      
		for(i=0; i< 8; i++){                                                    
			free(mat[i]);                                                       
		}                                                                       
		return 0;                                                               
	}                                                                           

	gpioSetTimerFunc(0, 50, callback);                                          

	while(1)                                                                    
		for(i=0; i<8 ; i++){                                                    
			for(j=0; j<8; j++){                                                 
				if(mat[i][(j+cnt)%len] ==1){                                    
					dot(i+1, j+1);                                              
				}                                                               
			}                                                                   
		}                                                                       
	release();                                                                  


	for(i = 0 ; i<8 ; i++){                                                     
		free(mat[i]);                                                           
	}                                                                           

	return 0;                                                                   

}               
