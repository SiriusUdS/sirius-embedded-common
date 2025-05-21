#include "../../../Inc/Device/Telecommunication/DataBridge.h"

void DATABRIDGE_init(DataBridge* instance) {
   

    instance->init = DATABRIDGE_init;
    instance->sendUSBtoUART = DATABRIDGE_sendUSBtoUART;
    instance->sendUARTtoUSB = DATABRIDGE_sendUARTtoUSB;
    instance->receiveUSB = DATABRIDGE_receiveUSB;
    instance->getCommand = DATABRIDGE_getCommand;

    if (instance->xbee != NULL) {
        XBEE_init(instance->xbee);
        XBEE_config(instance->xbee);
    }
}

void DATABRIDGE_sendUSBtoUART(DataBridge* instance, uint8_t* data, uint16_t size) {
    if (instance == NULL || instance->usb == NULL || instance->uart == NULL)
        return;

    if (instance->usb->status.bits.rxDataReady == 1) {
        instance->usb->status.bits.rxDataReady = 0;

        instance->uart->transmit((struct UART*)instance->uart, data, size);
    }
}

void DATABRIDGE_sendUARTtoUSB(DataBridge* instance, uint8_t* data, uint32_t previous) {

    if (instance == NULL || instance->usb == NULL)
        return;

    if (HAL_GetTick() - previous >= 100) {
        previous = HAL_GetTick();

        instance->usb->transmit((struct USB*)instance->usb, data, sizeof(data));
    }
}



void DATABRIDGE_receiveUSB(DataBridge* instance) {
    if (instance == NULL || instance->usb == NULL)
        return;

    if (instance->usb->status.bits.rxDataReady == 1) {
        instance->usb->status.bits.rxDataReady = 0;
        memcpy(&instance->lastCommand, instance->usb->rxBuffer, sizeof(BoardCommand));
    }
}

void DATABRIDGE_getCommand(DataBridge* instance) {
    if (instance == NULL)
        return;
}
