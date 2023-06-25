#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apiFood.h"



// Write function that will be called by libcurl when data is received
static size_t write_callback(char *ptr, size_t size, size_t nmemb, struct dataStored *result) {
    size_t total_size = size * nmemb;
    result->data = realloc(result->data, result->size + total_size + 1);
    if (result->data == NULL) {
        fprintf(stderr, "Failed to allocate memory for buffer\n");
        return 0;
    }
    memcpy(&(result->data[result->size]), ptr, total_size);
    result->size += total_size;
    result->data[result->size] = '\0';
    return total_size;
}
char* foodAPI(const char *q, const char *urlRecom, const char *apiKey, const char *addition) {
    CURL *curl;
    CURLcode res;

//    char *urlRecom = "https://api.spoonacular.com/recipes/complexSearch";
    char *urlRecip = "https://api.spoonacular.com/recipes/";
//    char *q = "salad";
//    char *apiKey = "1f42a6210ce64f739476c88249017014";
//    char *apiKey = "1f42a6210ce64f739476c88249017014";
    char query[255];
    char *id="";
    char *result = NULL;
    snprintf(query, sizeof(query), "%s%s%s%s", urlRecom, q, apiKey,addition);

//    curl = curl_easy_init();
//    if (curl) {
//        struct dataStored returnID = { NULL, 0 };
//
//        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
//        curl_easy_setopt(curl, CURLOPT_URL, query);
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback); // Set up pointer returnedData
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&returnID); // Set returned data
//        res = curl_easy_perform(curl);
//        if (res != CURLE_OK) {
//            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
//        }
//        else {
//            char *id_start = strstr(returnID.data,"id");
//            if (id_start) {
//                id_start = strchr(id_start, ':') + 1; // move the pointer to the beginning of the ID value
//                char *id_end = strpbrk(id_start, ",}"); // find the end of the ID value
//                if (id_end) {
//                    *id_end = '\0'; // terminate the string at the end of the ID value
//                    id = strtok(id_start, "\""); // extract the ID value as a string
//                }
//            }
//        }
//        curl_easy_cleanup(curl);
//        free(returnID.data); // Free the data
//    }
    //Get the recipt of ID recipt
//    snprintf(query, sizeof(query), "%s/%s/information?&apiKey=%s", urlRecip, id, apiKey);
    curl = curl_easy_init();
    if(curl){
        cJSON *jsonArray = cJSON_CreateArray();
        cJSON *jsonObject = cJSON_CreateObject();
        cJSON *originalArray = cJSON_CreateArray();
        cJSON *originalObject = cJSON_CreateObject();

        struct dataStored returnData = { NULL, 0 };
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_URL, query);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback); // Set up pointer returnedData
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&returnData); // Set returned data
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else {
            cJSON *jsonReturnedValue = cJSON_Parse(returnData.data);
            cJSON *extendedIngredients = cJSON_GetObjectItem(jsonReturnedValue,"extendedIngredients");
            cJSON *value;
            cJSON_ArrayForEach(value,extendedIngredients){

                cJSON *original = cJSON_GetObjectItem(value, "original");
                if (original != NULL && cJSON_IsString(original)) {
                    cJSON_AddItemToArray(originalArray, cJSON_CreateString(original->valuestring));
                }            }
            cJSON_Delete(jsonReturnedValue);
            cJSON_AddItemToObject(originalObject, "original", originalArray);
            cJSON_AddItemToArray(jsonArray, originalObject);
            result = cJSON_Print(originalObject);
        }
        return result;
    }
    curl_easy_cleanup(curl);
    return NULL;
}