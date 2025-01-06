#pragma once

#include "Storage.h"

extern void SDCard_init(Storage* instance);

extern void SDCard_storeAccelerometerData(Storage* instance, AccelerometerPacket data);

extern void SDCard_storePressureSensorData(Storage* instance, PressureSensorPacket data);