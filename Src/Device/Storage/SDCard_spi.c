#include "../../../Inc/Device/Storage/SDCard.h"
#include "SDCard_spi.h"
#include "main.h"
#include <string.h>
#include <stdint.h>



static uint8_t crc7_sd(const uint8_t *message, int length) {
    uint8_t crc = 0;
    
    for (int i = 0; i < length; i++) {
        uint8_t byte = message[i];
        for (int j = 0; j < 8; j++) {
            uint8_t bit = (byte & 0x80) ? 1 : 0;
            byte <<= 1;
            
            // If MSB of CRC XOR incoming bit is 1
            if ((crc >> 6) ^ bit) {
                // Shift left and XOR with polynomial 0x09 (x^7 + x^3 + 1)
                crc = (crc << 1) ^ 0x09;
            } else {
                // Just shift left
                crc = crc << 1;
            }
            
            // Keep only 7 bits
            crc &= 0x7F;
        }
    }
    
    // Add stop bit (1)
    return (crc << 1) | 0x01;
}

static void send_command(sd_card_t * instance, uint8_t *command, uint8_t length)
{
    // Send command to SD card
    for (uint8_t i = 0; i < length; i++)
    {
        HAL_SPI_Transmit(instance->spiHandle, &command[i], 1, HAL_MAX_DELAY);
    }
}

static void receive_response(sd_card_t * instance, uint8_t * response)
{
        HAL_SPI_Receive(instance->spiHandle, &response, 1, HAL_MAX_DELAY);
}


static void mode_idle(sd_card_t * instance)
{
    
    HAL_GPIO_WritePin(instance->ce->pinGroup, instance->ce->pinNumber, GPIO_PIN_SET);

    uint8_t cmd0[5] = {0x40, 0x00, 0x00, 0x00, 0x00};  // CMD0 with arguments
    uint8_t crc = crc7_sd(cmd0, 5); // Calculate CRC7 for the command
    uint8_t frame[6] = 
    {
        cmd0[0], // CMD0
        cmd0[1], // Argument 1
        cmd0[2], // Argument 2
        cmd0[3], // Argument 3
        cmd0[4], // Argument 4
        crc      // CRC7
    };
    uint8_t response[6] = {0}; // Buffer for response

    send_command(instance, frame, 6); // Send command frame
    HAL_Delay(1); // Wait for response

    receive_response(instance, response); // Receive response

    if(response[0] == 0x01) // Check if response is valid
    {
        instance->storage->status.value |= 0x01; // Set status to indicate idle mode
    }
    else
    {
        instance->storage->errorStatus.value |= 0x01; // Set error status
    }
    HAL_GPIO_WritePin(instance->ce->pinGroup, instance->ce->pinNumber, GPIO_PIN_RESET); // Deactivate CS pin

}

void SDCard_init(sd_card_t * instance)
{
    instance->storage->status.value = 0;
    instance->storage->errorStatus.value = 0;

    mode_idle(instance);
    
}

void SDCard_store4kbData(Storage *instance, uint8_t *data)
{
    sd_card_t *sdCard = (sd_card_t *)instance; // Cast to sd_card_t
    HAL_GPIO_WritePin(sdCard->ce->pinGroup, sdCard->ce->pinNumber, GPIO_PIN_SET); // Activate CS pin

    uint8_t cmd24[5] = {0x58, 0x00, 0x00, 0x00, 0x00}; // CMD24 with arguments
    uint8_t crc = crc7_sd(cmd24, 5); // Calculate CRC7 for the command
    uint8_t frame[6] = 
    {
        cmd24[0], // CMD24
        cmd24[1], // Argument 1
        cmd24[2], // Argument 2
        cmd24[3], // Argument 3
        cmd24[4], // Argument 4
        crc      // CRC7
    };
    
    send_command(sdCard, frame, 6); // Send command frame

    HAL_SPI_Transmit(sdCard->spiHandle, data, 4096, HAL_MAX_DELAY); // Send data

    HAL_GPIO_WritePin(sdCard->ce->pinGroup, sdCard->ce->pinNumber, GPIO_PIN_RESET); // Deactivate CS pin
}

void SDCard_fetch4kbData(Storage *instance, uint8_t *data)
{
    
    sd_card_t *sdCard = (sd_card_t *)instance; // Cast to sd_card_t
    HAL_GPIO_WritePin(sdCard->ce->pinGroup, sdCard->ce->pinNumber, GPIO_PIN_SET); // Activate CS pin

    uint8_t cmd17[5] = {0x51, 0x00, 0x00, 0x00, 0x00}; // CMD17 with arguments
    uint8_t crc = crc7_sd(cmd17, 5); // Calculate CRC7 for the command
    uint8_t frame[6] = 
    {
        cmd17[0], // CMD17
        cmd17[1], // Argument 1
        cmd17[2], // Argument 2
        cmd17[3], // Argument 3
        cmd17[4], // Argument 4
        crc      // CRC7
    };
    
    send_command(sdCard, frame, 6); // Send command frame

    HAL_SPI_Receive(sdCard->spiHandle, data, 4096, HAL_MAX_DELAY); // Receive data

    HAL_GPIO_WritePin(sdCard->ce->pinGroup, sdCard->ce->pinNumber, GPIO_PIN_RESET); // Deactivate CS pin

}