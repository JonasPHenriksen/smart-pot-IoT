#include "includes.h"
#include "cJSON.h" 


char* rawDatasToJSONString(int numPairs, const char* keys[], const char* values[]) {
  if (numPairs <= 0 || keys == NULL || values == NULL) {
    return NULL;
  }
  cJSON* json = cJSON_CreateObject();
  if (json == NULL) {
    return NULL; 
  }
  for (int i = 0; i < numPairs; i++) {
    if (strcmp(keys[i], "MachineID") == 0) {
      cJSON_AddStringToObject(json, keys[i], values[i]);
    } else {
      double numValue = atof(values[i]);
      if (numValue == (int)numValue) {
        cJSON_AddNumberToObject(json, keys[i], (int)numValue);
      } else {
        cJSON_AddNumberToObject(json, keys[i], numValue);
      }
    }
  }
  char* jsonString = cJSON_PrintUnformatted(json);
  cJSON_Delete(json);

  return jsonString;
}