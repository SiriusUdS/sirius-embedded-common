#pragma once

#include "Storage.h"

extern void ExternalFlash_init(Storage* instance);

extern void ExternalFlash_store(Storage* instance, uint8_t* data, uint16_t size);

extern void ExternalFlash_fetch(Storage* instance, uint8_t* data, uint16_t size);