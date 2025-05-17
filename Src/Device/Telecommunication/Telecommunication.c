#include "../../../Inc/Device/Telecommunication/Telecommunication.h"

void Telecommunication_initDefault(Telecommunication* instance){
  instance->receiveData = (Telecommunication_receiveData)Telecommunication_receiveDataDefault;
  instance->sendData = (Telecommunication_sendData)Telecommunication_sendDataDefault;
  instance->config = (Telecommunication_config)Telecommunication_configDefault;
  instance->tick = (Telecommunication_tick)Telecommunication_tickDefault;

  instance->errorStatus.value = 0;
  instance->status.value = 0;

  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void Telecommunication_sendDataDefault(Telecommunication* instance, uint8_t* data, uint16_t size){
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}


void Telecommunication_receiveDataDefault(Telecommunication* instance, uint8_t* data, uint16_t size){
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}


void Telecommunication_configDefault(Telecommunication* instance) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
  /*uint8_t cmdmode[] = "+++++";
  instance->uart->transmit((struct UART*)instance->uart, cmdmode, sizeof(cmdmode) - 1);
  uint8_t rec[3] = "00";
  //HAL_Delay(1200); // GUARDIAN TIME DATASHEET
  //while(1){
  //  instance->uart->receive((struct UART)instance, rec, 3);
  //  if(rec[0] == 'O'){
  //    break;
  //  }
  //}

  uint8_t index = 0;
  uint8_t atCommands[3][10] = {"ATDH0000\r", "ATDLFFFF\r", "ATID2015\r"};
  for(uint8_t i=0; i < 3; i++){
    rec[0] = '0';
    rec[1] = '0';
    //for(uint8_t j=0; j < 2; j++){
    //  atCommands[i][j+4] = setup.data[index++];
    //}
    //atCommands[i][7] = '\0';
    instance->uart->transmit((struct UART*)instance->uart, atCommands[i], 9);

    HAL_Delay(200);
    instance->uart->receive((struct UART*)instance, rec, 3);
  }

  uint8_t finalCommand[2][6] = {"ATWR\r", "ATCN\r"};

  for(uint8_t i =0; i < 2; i++){
    instance->uart->transmit((struct UART*)instance->uart, finalCommand[i], 6);
  }*/
}

void Telecommunication_tickDefault(Telecommunication* instance, uint32_t timestamp_ms) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}