//
// Created by dat on 6/3/23.
//

#ifndef CINTERFACE_APIFOOD_H
#define CINTERFACE_APIFOOD_H
// Define pointer to store return
#include <curl/curl.h>
#include <cjson/cJSON.h>
struct dataStored {
    char *data;
    size_t size;
};

char* foodAPI(const char *q, const char *urlRecom, const char *apiKey, const char *addition);
#endif //CINTERFACE_APIFOOD_H
