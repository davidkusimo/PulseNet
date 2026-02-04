#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstdint> // Required for fixed-width types (uint32_t, etc.)


constexpr uint32_t ID_GATEWAY = 0x00;
constexpr uint32_t ID_ENGINE  = 0x01;
constexpr uint32_t ID_BRAKES  = 0x02;

// 2. MESSAGE TYPES

enum class MsgType : uint8_t {
    HEARTBEAT = 0x01,
    DATA      = 0x02,
    COMMAND   = 0x03
};


// 3. THE PACKET STRUCTURE

// It tells the compiler: "Do not add any empty padding bytes between these fields."
// This ensures the struct looks identical in memory on every device.
struct __attribute__((packed)) VehicleMessage {
    uint32_t source_id;
    MsgType type;
    float payload;
    uint64_t timestamp;
};

#endif