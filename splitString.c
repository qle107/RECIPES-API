//
// Created by Quang Dat on 29/05/2023.
//
#include <string.h>

#include "splitString.h"
char* splitString(const char* input) {
    char* start = strchr(input, '['); //Start of string
    char* end = strchr(input, ']'); //End of string (to compare)

    start++;
    size_t length = end - start;
    char* result = (char*)malloc(length + 1);
    if (result != NULL) {

        // Merge the split string
        strncpy(result, start, length);

        // Convert "]" into \0
        result[length] = '\0';

        //Replace ',' with down line and '-'
        for (size_t i = 0; i < length; i++) {
            if (result[i] == ',' && result[i-1]=='"') {
                result[i] = '\n';
            }
        }
    }
    return result;
}