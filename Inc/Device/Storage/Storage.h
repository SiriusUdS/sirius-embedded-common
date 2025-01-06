#pragma once

#include "../../../sirius-headers-common/Storage/StorageStatus.h"

#include "../../../sirius-headers-common/Accelerometer/AccelerometerPacket.h"
#include "../../../sirius-headers-common/PressureSensor/PressureSensorPacket.h"

struct Storage;

typedef void (*Storage_init)(struct Storage* instance);

typedef void (*Storage_storeAccelerometerData)(struct Storage* instance, AccelerometerPacket data);

typedef void (*Storage_storePressureSensorData)(struct Storage* instance, PressureSensorPacket data);

typedef struct {
  Storage_init                    init;
  Storage_storeAccelerometerData  storeAccelerometerData;
  Storage_storePressureSensorData storePressureSensorData;

  StorageStatus status;
}
Storage;

extern void Storage_initDefault(Storage* instance);

extern void Storage_storeAccelerometerDataDefault(Storage* instance, AccelerometerPacket data);

extern void Storage_storePressureSensorDataDefault(Storage* instance, PressureSensorPacket data);