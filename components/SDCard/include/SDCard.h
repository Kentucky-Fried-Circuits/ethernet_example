#pragma once

#ifndef SDCARD_H
#define SDCARD_H

#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <errno.h>

#include "esp_log.h"
#include "driver/sdmmc_host.h"
#include "driver/sdmmc_defs.h"
#include "sdmmc_cmd.h"
#include "esp_vfs_fat.h"

#include "dataLogging.h"

#define MOUNT_POINT "/sdcard"
const char *const TAG_SD = "SD_Card";
static sdmmc_card_t *card;
static bool SDCARDMOUNTED = false;

/*functions*/
esp_err_t initi_sd_card(void);
esp_err_t unmount_sd_card(void);
int logStringToFile(const char *formattedString, char *fileName);
void memoryLogging();
bool isMounted(void);
bool SD_getFreeSpace(uint32_t *tot, uint32_t *free);
void deleteFile(char *filePath);
int hasFile(char *fileName);

#endif // SDCARD_H