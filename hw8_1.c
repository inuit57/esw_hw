#include<stdio.h>
#include"cJSON.h"

char * create_monitor1(void);
char * create_monitor2(void); 

int main(void){
	char * json; 
	FILE * fp = fopen("data1.json","w"); 
	
	if(fp==NULL){
		printf("file open error\n"); 
		return -1; 
	}
	json = create_monitor1(); 
	fprintf(fp, "%s\n", json);

	fclose(fp);

	fp = fopen("data2.json", "w"); 

	if(fp == NULL){
		printf("file open error\n"); 
		return -1; 
	}

	json = create_monitor2(); 
	fprintf(fp, "%s\n", json);
	
	fclose(fp); 

	return 0; 
}

char * create_monitor1(void)
{
	const unsigned int resolution_numbers[3] ={20,21,23};

	char *string = NULL; 
	cJSON * device = NULL; 
	cJSON * sensorType = NULL; 

	cJSON *resolutions = NULL; 
//	cJSON *resolution = NULL;
   	cJSON *values = NULL; 	

	size_t index = 0; 

	cJSON *monitor = cJSON_CreateObject(); 
	if(monitor == NULL){
		goto end; 
	}

	device = cJSON_CreateString("ESP32"); 
	if(device == NULL){
		goto end; 
	}

	cJSON_AddItemToObject(monitor,"device", device);

	sensorType = cJSON_CreateString("Temperature"); 
	if(sensorType == NULL){
		goto end; 
	}	

	cJSON_AddItemToObject(monitor,"sensorType", sensorType); 

	resolutions = cJSON_CreateArray(); 
	
	if(resolutions == NULL){
		goto end; 
	}

	cJSON_AddItemToObject(monitor, "Value", resolutions); 

	for(index = 0; index < sizeof(resolution_numbers)/ sizeof(int) ; ++index){

		values  = cJSON_CreateNumber(resolution_numbers[index]); 
		if(values == NULL){
			goto end; 
		}

		cJSON_AddItemToArray(resolutions, values); 

	}
//	string = cJSON_Print(monitor); 
	string = cJSON_PrintUnformatted(monitor); 
	if(string == NULL){
		fprintf(stderr, "Failed to print monitor.\n"); 
	}

end:
	cJSON_Delete(monitor); 
	return string; 
}

char * create_monitor2(void){
	const char * colorValues[3][2] ={ {"red","#f00"},{"green", "#0f0"},{"blue", "#00f"}}; 

	char *string; 
	cJSON * colorsArray  = NULL; 
//	cJSON * colorName = NULL; 
//	cJSON * colorValue = NULL; 

	size_t index; 

	cJSON *monitor = cJSON_CreateObject(); 

	if(monitor == NULL){
		goto end; 
	}

	colorsArray = cJSON_AddArrayToObject(monitor,"colorsArray"); 

	if(colorsArray == NULL){
		goto end; 
	}

	for(index = 0; index < 3 ; ++index){

		cJSON * resolution = cJSON_CreateObject(); 

		if(cJSON_AddStringToObject(resolution, "colorName",colorValues[index][0])== NULL){
		   goto end; 
		}
 		if(cJSON_AddStringToObject(resolution, "hexValue",colorValues[index][1])==NULL){
			goto end; 
		}
		
		cJSON_AddItemToArray(colorsArray, resolution); 
	}

//	string = cJSON_Print(monitor); 
	string = cJSON_PrintUnformatted(monitor);

	if(string ==NULL){
		fprintf(stderr, "Failed to print monitor.\n");	
	}
end : 
	cJSON_Delete(monitor); 
	return string; 

}
