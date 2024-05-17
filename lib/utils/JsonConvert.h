#pragma once

#include "cJSON.h" 

cJSON* rawDataToJSON(char* key, char* value);
cJSON* rawDataArrayToJSON(int numPairs, char* keys[], char* values[]);
char* rawDatasToJSONString(int numPairs, char* keys[], char* values[]);