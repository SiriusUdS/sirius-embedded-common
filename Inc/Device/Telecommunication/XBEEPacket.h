#pragma once

#include <stdint.h>

#define DELIMITER 0x7E
#define MSB 0x00
#define LSB_SEND 0x3A
#define LSB_RECEIVE 0x38

#define DEFAULT_API_FRAME_TYPE_SEND 0x10
#define DEFAULT_API_FRAME_TYPE_RECEIVE 0x90
#define DEFAULT_16_BITS_SEND_ADDRESS 0xFFFE
#define DEFAULT_64_BITS_SEND_ADDRESS 0x000000000000FFFF
#define DEFAULT_BROADCAST 0x00

#define DEFAULT_SEND_OPTION 0x00
#define DEFAULT_RECEIVE_OPTION 0x01
#define DEFAULT_16_BITS_RECEIVE_ADDRESS 0xFFFE
#define DEFAULT_64_BITS_RECEIVE_ADDRESS 0xFFFFFFFFFFFFFFFF

#define SEND_PACKET_LENGHT 62
#define RECEIVE_PACKET_LENGHT 0x3C



#pragma pack(1)
typedef union
{
    struct {
        uint8_t del;
        uint8_t msb;
        uint8_t lsb;
        uint8_t apiFrameType;
        uint8_t frameID;
        uint8_t destAddr64[8];
        uint16_t destAddr16;
        uint8_t broadcast;
        uint8_t option;
        uint8_t data[LSB_SEND-0x0E];
        uint8_t checkSum;        
    } bits;

    uint8_t data[SEND_PACKET_LENGHT];
} XBeeSendAPIPacket;

#pragma pack()

#pragma pack(1)
typedef union
{
    struct {
        uint8_t del;
        uint8_t msb;
        uint8_t lsb;
        uint8_t apiFrameType;
        uint8_t sourceAddr64[8];
        uint16_t sourceAddr16;
        uint8_t option;
        uint8_t data[LSB_RECEIVE-0x0C];
        uint8_t checkSum;        
    } bits;

    uint8_t data[RECEIVE_PACKET_LENGHT];
} XBeeReceiveAPIPacket;
#pragma pack()