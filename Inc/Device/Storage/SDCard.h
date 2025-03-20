#pragma once

#include "Storage.h"

extern void SDCard_init(Storage* instance);

extern void SDCard_store4kbDataDefault(Storage* instance, uint8_t* data);

extern void SDCard_fetch4kbDataDefault(Storage* instance, uint8_t* data);