#include "../../../Inc/Device/Telecommunication/DataBridge.h"

void DATABRIDGE_init(DataBridge* instance) {
   

    instance->init = DATABRIDGE_init;
    instance->sendUSBtoUART = DATABRIDGE_sendUSBtoUART;
    instance->sendUARTtoUSB = DATABRIDGE_sendUARTtoUSB;
    instance->receiveUSB = DATABRIDGE_receiveUSB;
    instance->getCommand = DATABRIDGE_getCommand;
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



void DATABRIDGE_receiveUSB(DataBridge* instance, GSControl gsControl) {
    if (gsControl.usb->status.bits.rxDataReady == 1) {
        uint8_t* test = gsControl.usb->rxBuffer;
        gsControl.usb->status.bits.rxDataReady = 0;
      } 
}

void DATABRIDGE_getCommand(DataBridge* instance) {
    if (instance == NULL)
        return;
}
