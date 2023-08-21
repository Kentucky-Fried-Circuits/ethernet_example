/**
 * 08/17/2023 - Ruizhe He, since
 */
#pragma once

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <stdio.h>
#include <sys/param.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <vector>
#include <cstdint>
#include <string>
#include <cstring>
#include <map>

// TODO: Delete this in 99-2000
#include <random>

#include "esp_err.h"
#include "esp_event.h"
#include "esp_check.h"
#include <esp_event.h>
#include <esp_log.h>
#include "esp_http_server.h"
#include "cJSON.h"

#include "SDCard.h"

#define ERR_INVALID_ARG "Null argument(s)"
#define ERR_HTTP_ALLOC_MEM "Failed to allocate memory for instance"
#define ERR_HTTP_TASK "Failed to launch server task"

#define DOWNLOAD_URI "/download/"
#define DELETE_URI "/delete/"
// Max length for file name. Our file should have format of yyyyMMDD.csv
#define FILE_PATH_MAX 25

/* Max size of an individual file. Make sure this
 * value is same as that set in upload_script.html */
#define MAX_FILE_SIZE (200 * 1024) // 200 KB
#define MAX_FILE_SIZE_STR "200KB"

/* Scratch buffer size */
#define SCRATCH_BUFSIZE 8192

const char *const TAG_WEB = "Web_Server";

struct file_server_data
{
    /* Scratch buffer for temporary storage during file transfer */
    char scratch[SCRATCH_BUFSIZE];
};

// NOTE: file_server.c
void get_path_from_uri(const char *uri, char *search, char *filepath, char *filename);

struct file_server_data *initFileServer();

std::vector<std::string> getAllFileName();

// NOTE: webServer.cpp
httpd_handle_t start_webserver();

void stop_webserver(httpd_handle_t server);

// NOTE: Data2Web.cpp
class historyObj
{
public:
    float max;
    float avg;
    float min;
    std::vector<float> valueHolder;
};

std::string getDataNow(long long time);

std::string getHostInfoJson();

std::string getHistoryFiles();

std::string getDaysStats();

std::string getRecentData();

void addToRecent(std::vector<float> liveData);

#endif /* WEBSERVER_H */
