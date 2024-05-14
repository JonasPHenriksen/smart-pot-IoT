#pragma once

#include "cJSON.h" 

cJSON* rawDataToJSON(const char* key, const char* value);
cJSON* rawDataArrayToJSON(int numPairs, const char* keys[], const char* values[]);
char* rawDatasToJSONString(int numPairs, const char* keys[], const char* values[]);