#pragma once

#include <stdint.h>
#include "../../LowLevelDriver/UART/UART.h"
#include "../../LowLevelDriver/USB/USB.h"
#include "../../../sirius-headers-common/Telecommunication/BoardCommand.h"
#include "../sirius-gs-control-embedded/SIRIUS_GS_Control/core/Inc/GSControl.h"


struct DataBridge;

typedef void (*DataBridge_init)(struct DataBridge* instance);
typedef void (*DataBridge_sendUSBtoUART)(struct DataBridge* instance);
typedef void (*DataBridge_sendUARTtoUSB)(struct DataBridge* instance);
typedef void (*DataBridge_receiveUSB)(struct DataBridge* instance);
typedef void (*DataBridge_getCommand)(struct DataBridge* instance);

typedef struct DataBridge {
    DataBridge_init           init;
    DataBridge_sendUSBtoUART  sendUSBtoUART;
    DataBridge_sendUARTtoUSB  sendUARTtoUSB;
    DataBridge_receiveUSB     receiveUSB;
    DataBridge_getCommand     getCommand;

    UART* uart;
    USB* usb;

    BoardCommand lastCommand; // à voir
} DataBridge;

void DATABRIDGE_init(DataBridge* instance);
void DATABRIDGE_sendUSBtoUART(DataBridge* instance);
void DATABRIDGE_sendUARTtoUSB(DataBridge* instance, uint32_t previous);
void DATABRIDGE_receiveUSB(DataBridge* instance, GSControl gsControl);
void DATABRIDGE_getCommand(DataBridge* instance);
