#include "../../../Inc/Device/Storage/SDCard.h"

#include "fatfs.h"

#include <string.h>
#include <stdint.h>

FIL loadFileHandle;
FIL stateFileHandle;
FIL adcFileHandle;
FIL adcTimestampFileHandle;

DIR currentDirectory;

TCHAR directoryPath[16] = "";

uint8_t fileCreationMode = FA_CREATE_ALWAYS;
uint8_t fileWriteCounter = 0;

static FRESULT getFreeSpace(Storage* instance, uint16_t* totalSectors, uint16_t* freeSectors);

static FRESULT openFile(Storage* instance, TCHAR* filePath, FIL* fileHandle, uint8_t mode);

static FRESULT closeFile(Storage* instance);

static FRESULT createDirectory(Storage* instance);

void SDCard_init(Storage* instance) {
  FRESULT operationResult;
  FATFS* fatfs = (FATFS*)instance->fs;

  instance->status.value = 0;
  instance->errorStatus.value = 0;
  instance->errorStatus.bits.notInitialized = 1;

  instance->fetch = (Storage_fetch)SDCard_fetch;
  instance->store = (Storage_store)SDCard_store;
  instance->tick  = (Storage_tick)SDCard_tick;

  operationResult = f_mount(fatfs, instance->volumePath, 1);
  if (operationResult != FR_OK) {
    instance->errorStatus.bits.fs_mountFailed = 1;
    instance->state = STORAGE_STATE_ERROR;
    return;
  }

  // if it is being reinit
  if (directoryPath[0] != '\0') {
    fileCreationMode = FA_OPEN_APPEND;
    operationResult = createDirectory(instance);
    if (operationResult != FR_OK) {
      instance->errorStatus.bits.fs_createDirectoryFail = 1;
      instance->state = STORAGE_STATE_ERROR;
      return;
    }
  }

  operationResult = openFile(instance, SD_CARD_ADC_PATH, &adcFileHandle, fileCreationMode);
  if (operationResult != FR_OK) {
    instance->errorStatus.bits.fs_openFailed = 1;
    instance->state = STORAGE_STATE_ERROR;
    return;
  }

  operationResult = openFile(instance, SD_CARD_ADC_TIMESTAMP_PATH, &adcTimestampFileHandle, fileCreationMode);
  if (operationResult != FR_OK) {
    instance->errorStatus.bits.fs_openFailed = 1;
    instance->state = STORAGE_STATE_ERROR;
    return;
  }

  operationResult = openFile(instance, SD_CARD_LOAD_PATH, &loadFileHandle, fileCreationMode);
  if (operationResult != FR_OK) {
    instance->errorStatus.bits.fs_openFailed = 1;
    instance->state = STORAGE_STATE_ERROR;
    return;
  }

  operationResult = openFile(instance, SD_CARD_STATE_PATH, &stateFileHandle, fileCreationMode);
  if (operationResult != FR_OK) {
    instance->errorStatus.bits.fs_openFailed = 1;
    instance->state = STORAGE_STATE_ERROR;
    return;
  }

  operationResult = f_sync(&stateFileHandle);
  if (operationResult != FR_OK) {
    instance->errorStatus.bits.fs_syncFailed = 1;
    instance->state = STORAGE_STATE_ERROR;
    return;
  }

  instance->errorStatus.bits.notInitialized = 0;
  instance->state = STORAGE_STATE_ACTIVE;
}

void SDCard_store(Storage* instance, StorageDestination destination, uint8_t* data, uint16_t size) {
  FRESULT operationResult;
  FIL* fileHandle;
  TCHAR* path;
  UINT bytes_written;

  if (instance->state = STORAGE_STATE_ACTIVE) {
    switch (destination) {
      case STORAGE_ADC_DESTINATION:
        fileHandle = &adcFileHandle;
        path = SD_CARD_ADC_PATH;
        break;
      case STORAGE_ADC_TIMESTAMP_DESTINATION:
        fileHandle = &adcTimestampFileHandle;
        path = SD_CARD_ADC_TIMESTAMP_PATH;
        break;
      case STORAGE_LOAD_DESTINATION:
        fileHandle = &loadFileHandle;
        path = SD_CARD_LOAD_PATH;
        break;
      case STORAGE_STATE_DESTINATION:
        fileHandle = &stateFileHandle;
        path = SD_CARD_STATE_PATH;
        break;
      default:
        instance->errorStatus.bits.fs_unexpectedFileName = 1;
        instance->state = STORAGE_STATE_ERROR;
        return;
    }
  
    /*uint16_t total_sectors = 0;
    uint16_t free_sectors = 0;
    operationResult = SDCard_size_free_space(instance, &total_sectors, &free_sectors);
    if (operationResult != FR_OK) {
      instance->errorStatus.bits.notInitialized = 1;
      return;
    }
    if (free_sectors < 4) {
      instance->errorStatus.bits.notInitialized = 1;
      return;
    }*/
  
    operationResult = f_write(fileHandle, data, size, &bytes_written);
    if (operationResult != FR_OK) {
      instance->errorStatus.bits.writeFailed = 1;
      instance->state = STORAGE_STATE_ERROR;
      return;
    }
  
    if (bytes_written != size) {
      instance->errorStatus.bits.incompleteWrite = 1;
      instance->state = STORAGE_STATE_ERROR;
      return;
    }
  
    if (fileWriteCounter >= SD_CARD_STORES_BETWEEN_SYNC) {
      fileWriteCounter = 0;
      operationResult = f_sync(fileHandle);
      if (operationResult != FR_OK) {
        instance->errorStatus.bits.fs_syncFailed = 1;
        instance->state = STORAGE_STATE_ERROR;
        return;
      }
    }
    fileWriteCounter++;
  }
}

void SDCard_fetch(Storage* instance, StorageDestination destination, uint8_t* data, uint16_t size) {
  /*FRESULT fr_status = SDCard_mount(instance, "");
  if (fr_status != FR_OK) {
    instance->errorStatus.bits.notInitialized = 1;
    return;
  }
  FIL file;
  fr_status = f_open(&file, "data.txt", FA_READ);
  if (fr_status != FR_OK) {
    instance->errorStatus.bits.notInitialized = 1;
    return;
  }
  UINT bytes_read;
  fr_status = f_read(&file, data, SECTOR_BYTE_SIZE, &bytes_read);
  if (fr_status != FR_OK) {
    instance->errorStatus.bits.notInitialized = 1;
    return;
  }
  if (bytes_read != SECTOR_BYTE_SIZE) {
    instance->errorStatus.bits.notInitialized = 1;
    return;
  }
  fr_status = f_close(&file);
  if (fr_status != FR_OK) {
    instance->errorStatus.bits.notInitialized = 1;
    return;
  }
  fr_status = SDCard_unmount(instance);
  if (fr_status != FR_OK) {
    instance->errorStatus.bits.notInitialized = 1;
    return;
  }*/
}

void SDCard_tick(Storage* instance, uint32_t timestamp_ms) {
  switch (instance->state) {
    case STORAGE_STATE_INIT:
      SD_HandleTypeDef* handle = (SD_HandleTypeDef*)instance->externalInstance;
      /*if (instance->status.bits.isPluggedIn == 1) {
        instance->init(instance);
      }*/
    case STORAGE_STATE_ACTIVE:
    case STORAGE_STATE_ERROR:
      SD_HandleTypeDef* handle = (SD_HandleTypeDef*)instance->externalInstance;
      //instance->state = STORAGE_STATE_INIT;
    default:
      break;
  }
}

FRESULT createDirectory(Storage* instance) {
  FRESULT operationResult;
  uint16_t directoryNumber = 0;

  for (;;) {
    itoa(directoryNumber, directoryPath, 10);

    operationResult = f_mkdir(directoryPath);

    switch (operationResult) {
      case FR_EXIST:
        directoryNumber++;
        break;
      case FR_OK:
        return operationResult;
      default:
        instance->errorStatus.bits.fs_createDirectoryFail = 1;
        instance->state = STORAGE_STATE_ERROR;
        return operationResult;
    }
  }
}

FRESULT openFile(Storage* instance, TCHAR* filePath, FIL* fileHandle, uint8_t mode) {
  TCHAR path[16] = "";
  strcpy(path, directoryPath);
  strcat(path, "/");
  strcat(path, filePath);
  return f_open(fileHandle, path, mode | FA_WRITE);
}

FRESULT getFreeSpace(Storage* instance, uint16_t* total_sectors, uint16_t* free_sectors) {
  FATFS* fatfs = (FATFS*)instance->fs;
  FATFS** pfatfs = &fatfs;
  FRESULT fr_status;
  DWORD free_clusters;
  fr_status = f_getfree("", &free_clusters, pfatfs);
  if (fr_status == FR_OK) {
    *total_sectors = (fatfs->n_fatent - 2) * fatfs->csize;
    *free_sectors = free_clusters * fatfs->csize;
  }
  return fr_status;
}