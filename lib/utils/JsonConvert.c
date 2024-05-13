#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h" 


cJSON* rawDataToJSON(const char* key, const char* value) {
    // Create a cJSON object
    cJSON* json = cJSON_CreateObject();
    // Add key-value pair to JSON
    cJSON_AddStringToObject(json, key, value);

    return json;
}

cJSON* rawDatasToJSON(int numPairs, const char* keys[], const char* values[]) {
    if (numPairs <= 0 || keys == NULL || values == NULL) {
        return NULL;
    }

    // Create a cJSON object
    cJSON* json = cJSON_CreateObject();
    if (json == NULL) {
        return NULL; // Failed to create cJSON object
    }

    // Add key-value pairs to JSON
    for (int i = 0; i < numPairs; i++) {
        cJSON_AddStringToObject(json, keys[i], values[i]);
    }

    return json;
}

char* rawDatasToJSONString(int numPairs, const char* keys[], const char* values[]) {
    if (numPairs <= 0 || keys == NULL || values == NULL) {
        return NULL;
    }

    // Create a cJSON object
    cJSON* json = cJSON_CreateObject();
    if (json == NULL) {
        return NULL; // Failed to create cJSON object
    }

    // Add key-value pairs to JSON
    for (int i = 0; i < numPairs; i++) {
        // Check if the key is "MachineID"
        if (strcmp(keys[i], "MachineID") == 0) {
            // If it is, add the value as a string
            cJSON_AddStringToObject(json, keys[i], values[i]);
        } else {
            // Otherwise, try to parse the value as a double
            double numValue = atof(values[i]);
            // Check if the value is an integer
            if (numValue == (int)numValue) {
                // If it is, add as integer
                cJSON_AddNumberToObject(json, keys[i], (int)numValue);
            } else {
                // Otherwise, add as double
                cJSON_AddNumberToObject(json, keys[i], numValue);
            }
        }
    }

    // Serialize cJSON object to a single line JSON string
    char* jsonString = cJSON_PrintUnformatted(json);

    // Free cJSON object
    cJSON_Delete(json);

    return jsonString;
}