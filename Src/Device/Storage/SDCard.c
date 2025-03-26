#include "../../../Inc/Device/Storage/SDCard.h"
#include "fatfs.h"
#include <string.h>
#include <stdint.h>

static FRESULT SDCard_mount(Storage* instance,TCHAR *path) {
  FATFS fatfs;
  FRESULT fr_status;
  fr_status = f_mount(&fatfs, path, 1);
  if (fr_status != FR_OK) {
    instance->errorStatus.bits.notInitialized = 1;
  }

  return fr_status;
}

static FRESULT SDCard_unmount(Storage* instance) {
  FRESULT fr_status;
  fr_status = f_mount(NULL, "", 0);
  if (fr_status == FR_OK) {
    instance->errorStatus.bits.notInitialized = 1;
  }
  return fr_status;
}

static FRESULT SDCard_size_free_space(Storage* instance,uint32_t *total_sectors, uint32_t *free_sectors) {
  FATFS fatfs;
  FRESULT fr_status;
  DWORD free_clusters;
  fr_status = f_getfree("", free_clusters, &fatfs);
  if (fr_status == FR_OK) {
    *total_sectors = (fatfs.n_fatent - 2) * fatfs.csize;
    *free_sectors = free_clusters * fatfs.csize;
  }
  return fr_status;
}

void SDCard_init(Storage* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;
}

void SDCard_store4kbData(Storage* instance, uint8_t* data) {
  
  if(instance->errorStatus.bits.notInitialized) {
    if(SDCard_mount(instance, "accelerometer") != FR_OK)
    {
      return; // early return if mounting failed
    }
  }
  
  FATFS fatfs;
  FIL fil;
  UINT bytes_written;
  uint16_t free_sectors;
  uint16_t total_sectors;
  char buffer[100];
  uint16_t total_sectors = 0;
  uint16_t free_sectors = 0;

  SDCard_size_free_space(instance, &total_sectors, &free_sectors);
  if (free_sectors < 100) {
    return;
  }

  FRESULT status = f_open(&fil, "accelerometer.txt", FA_WRITE | FA_OPEN_APPEND);

  if (status != FR_OK) {
    return;
  }
  
  sprintf(buffer, "%d,%d,%d,%d,\n", data.packet.rawData->members.data.rawX, data.packet.rawData->members.data.rawY, data.packet.rawData->members.data.rawZ);
  f_puts(buffer, &fil);

  f_close(&fil);

  SDCard_unmount(instance);
}

void SDCard_fetch4kbData(Storage* instance, uint8_t* data) {
  
}