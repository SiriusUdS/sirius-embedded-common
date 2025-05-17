#pragma once

#include "Storage.h"

void ExternalFlash_init(Storage* instance);

void ExternalFlash_store(Storage* instance, uint8_t* data, uint16_t size);

void ExternalFlash_fetch(Storage* instance, uint8_t* data, uint16_t size);

void ExternalFlash_tick(Storage* instance, uint32_t timestamp_ms);