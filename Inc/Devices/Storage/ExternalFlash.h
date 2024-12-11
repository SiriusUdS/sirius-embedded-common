#pragma once

#include "Storage.h"

extern void ExternalFlash_init(Storage* instance);

extern void ExternalFlash_storeAccelerometerData(Storage* instance, AccelerometerPacket data);

extern void ExternalFlash_storePressureSensorData(Storage* instance, PressureSensorPacket data);