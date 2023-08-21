/**
 * 08/16/2023 - Ruizhe He, this file will support webServer.cpp. All the
 * functions are presented to support functionalities of the webserver
 * and create a file server that web server can use. File server is
 * used when users open the historical data page, and it should
 * display all csv files that are in the SD card. Users should be
 * able to download or view the desired csv file for a specific date
 */

#include "webServer.h"

/* Copies the full path into destination buffer and returns
 * pointer to path (skipping the preceding base path) */
void get_path_from_uri(const char *uri, char *search, char *filepath, char *filename)
{
    std::string csvFile;
    std::string baseURI(uri);
    std::string searchingString(search);
    std::string replace(MOUNT_POINT);
    size_t pos = baseURI.find(search);

    csvFile = baseURI.substr(pos + searchingString.length());
    replace.append("/").append(csvFile);

    strcpy(filename, csvFile.c_str());
    strcpy(filepath, replace.c_str());
}

struct file_server_data *initFileServer()
{
    struct file_server_data *server_data = NULL;

    /* Allocate memory for server data */
    server_data = (struct file_server_data *)calloc(1, sizeof(struct file_server_data));
    if (!server_data)
    {
        ESP_LOGE(TAG_WEB, "Failed to allocate memory for server data");
        return NULL;
    }

    return server_data;
}

/**
 * Return a vector of strings that are all the files' name in the sd card. 
*/
std::vector<std::string> getAllFileName()
{
    char entrypath[16];
    char entrysize[16];

    std::vector<std::string> stringVet;

    struct dirent *entry;
    struct stat entry_stat;

    DIR *dir = opendir(MOUNT_POINT);
    const size_t dirpath_len = strlen(MOUNT_POINT);

    strlcpy(entrypath, MOUNT_POINT, sizeof(entrypath));

    if (!dir)
    {
        ESP_LOGE("TAG_SD", "Failed to stat dir : %s", MOUNT_POINT);
        /* Respond with 404 Not Found */
    }

    while ((entry = readdir(dir)) != NULL)
    {
        std::string entryName;
        std::string filePath;
        filePath.append(MOUNT_POINT).append("/").append(entry->d_name);

        if (entry->d_type == DT_DIR)
            continue;

        strlcpy(entrypath + dirpath_len, entry->d_name, sizeof(entrypath) - dirpath_len);
        if (stat(filePath.c_str(), &entry_stat) == -1)
        {
            ESP_LOGE("TAG_SD", "Failed to stat file : %s", entry->d_name);
            continue;
        }
        sprintf(entrysize, "%ld", entry_stat.st_size);
        ESP_LOGI("TAG_SD", "Found file : %s (%s bytes)", entry->d_name, entrysize);

        entryName.append(entry->d_name);
        stringVet.push_back(entryName);
    }
    closedir(dir);

    return stringVet;
}