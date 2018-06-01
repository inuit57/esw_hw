#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include "cJSON.h"

int parsing_monitor1(const char* const monitor); 
int parsing_monitor2(const char* const monitor); 

int main(void){
	char json[1024]; 
	int ret; 

	int fd; 
	fd = open("./data1.json", O_RDONLY); 

	if(fd <0){
	   printf("file open error\n");
   	   return -1; 
	}

	int nread; 

	printf(" first monitor check ****\n"); 
	nread = read(fd, json, sizeof(json)); 
	json[nread-1] = 0; 

	ret = parsing_monitor1(json); 

	printf("%d\n", ret); 
	close(fd); 
	
	fd = open("./data2.json", O_RDONLY); 

	if(fd <0){
		printf("file open error\n"); 
		return -1; 
	}

	printf(" second monitor check ****\n"); 
	nread = read(fd, json, sizeof(json)); 
	json[nread-1] = 0; 

	ret = parsing_monitor2(json); 

	printf("%d\n", ret); 
	close(fd); 
	return 0; 

}


int parsing_monitor1(const char * const monitor){
	const cJSON *device = NULL ; 
	const cJSON *sensorType = NULL; 
	const cJSON *values = NULL; 

	int status = 0; 

	cJSON *monitor_json = cJSON_Parse(monitor); 

	if(monitor_json ==  NULL){
		const char *error_ptr = cJSON_GetErrorPtr(); 
		if(error_ptr !=NULL){
			fprintf(stderr, "Error before : %s\n", error_ptr); 
		}
		status = 0; 
		goto end; 
	}

	device = cJSON_GetObjectItemCaseSensitive(monitor_json, "device");
	if(cJSON_IsString(device) && (device ->valuestring !=NULL)){
		printf("device \"%s\"\n", device->valuestring); 
	}

	sensorType = cJSON_GetObjectItemCaseSensitive(monitor_json,"sensorType"); 
	if(cJSON_IsString(sensorType) && (sensorType->valuestring !=NULL)){
		printf("sensorType \"%s\"\n", sensorType->valuestring); 

	}
	values = cJSON_GetObjectItemCaseSensitive(monitor_json, "Value"); 
	
	if(values == NULL){
		goto end; 
	}
	for(int i=0; i< cJSON_GetArraySize(values); i++){
		cJSON * value = cJSON_GetArrayItem(values,i); 
		if(cJSON_IsNumber(value)){
	   		printf("%d\n", value->valueint); 
			status =1; 
		}
	}	


end : 
	cJSON_Delete(monitor_json);
	return status; 
}

int parsing_monitor2(const char * const monitor){
	const cJSON * colorsArray  = NULL; 
	const cJSON * color =NULL; 
	int status = 0; 
	cJSON *monitor_json = cJSON_Parse(monitor); 

	if(monitor_json == NULL){
		const char *error_ptr = cJSON_GetErrorPtr(); 
		if(error_ptr !=NULL){
			fprintf(stderr, "Error before : %s\n", error_ptr); 
		}
		status = 0; 
		goto end; 
	}

	colorsArray = cJSON_GetObjectItemCaseSensitive(monitor_json, "colorsArray"); 
	
	for(int i=0; i< cJSON_GetArraySize(colorsArray) ; i++){
		color  = cJSON_GetArrayItem(colorsArray, i); 
		cJSON * colorName = cJSON_GetObjectItemCaseSensitive(color, "colorName"); 
		cJSON * hexValue = cJSON_GetObjectItemCaseSensitive(color, "hexValue");

		printf("%s : %s\n", colorName->valuestring, hexValue->valuestring); 
		status =1; 
	}
/*
	cJSON_ArrayForEach(color, colorsArray){
		cJSON * colorName = cJSON_GetObjectItemCaseSensitive(color, "colorName"); 
		cJSON * hexValue = cJSON_GetObjectItemCaseSensitive(color, "hexValue"); 

		if(strcmp(colorName->valuestring,"red")==0){
			printf("red : %s\n", hexValue->valuestring); 
		}
		else if(strcmp(colorName->valuestring, "green")==0){
			printf("green : %s\n", hexValue->valuestring); 
		}
		else {
			printf("blue : %s\n", hexValue->valuestring); 
		}

		status =1; 
		goto end;
	}
	*/
end :
	cJSON_Delete(monitor_json); 
	return status; 
}

