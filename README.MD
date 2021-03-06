# TWI library for ATMega devices

This library allows to connect between devices via I2C bus, all communications is interrupt based

## Usage

Configuration

```cpp
// Set custom Rx/Tx buffer size
#define TWI_BUFFER_LENGTH 32

// If you want to disable master module add next definition
// This excludes code from compilation and decrease firmware size
#define TWI_ENABLE_MASTER 0

// If you want to disable slave module add next definition
// This excludes code from compilation and decrease firmware size
#define TWI_ENABLE_SLAVE 0
```

Master example

```cpp
#include <TWI.h>
#include <stdint.h>

void onTransmit() {
    // Do something on transmission complete
    TWI.receive(0xFF, 4);
}

void onReceive() {
    // Do something with received data as example set new app state

    uint8_t value1  = TWI.readU08();// Read byte from RX buffer
    uint16_t value2 = TWI.readU16();// Read word from RX buffer
    uint32_t value3 = TWI.readU32();// Read dword from RX buffer
    float value4    = TWI.readFL();// Read float from RX buffer

    uint8_t values[4];
    TWI.read(values, 4);// Read 4 bytes array from RX buffer
}

int main() {
    // Enable TWI module
    TWI.enable();

    // Set TWI module frequency (optional)
    TWI.setFrequency(400000u);

    // Configure callbacks
    TWI.setOnTransmitHandler(onTransmit);
    TWI.setOnReceiveHandler(onReceive);

    // Configure transmission target
    TWI.start();

    TWI.writeU08(1);// Write byte to TX buffer
    TWI.writeU16(1);// Write word to TX buffer
    TWI.writeU32(1);// Write dword to TX buffer
    TWI.writeFL(1.0);// Write float to TX buffer

    uint8_t values[4];
    TWI.write(values, 4);// Write 4 bytes array to TX buffer

    // Trigger transmission process
    TWI.transmit(0xFFu);
}
```

Slave example

```cpp
#include <TWI.h>
#include <stdint.h>

void onReceive() {
    // Do something with received data as example set new app state

    uint8_t value1  = TWI.readU08();// Read byte from RX buffer
    uint16_t value2 = TWI.readU16();// Read word from RX buffer
    uint32_t value3 = TWI.readU32();// Read dword from RX buffer
    float value4    = TWI.readFL();// Read float from RX buffer

    uint8_t values[4];
    TWI.read(values, 4);// Read 4 bytes array from RX buffer
}

void onRequest() {
    // Send something to master, may depends on rx data
    // There are only need to fill buffer data

    TWI.writeU08(1);// Write byte to TX buffer
    TWI.writeU16(1);// Write word to TX buffer
    TWI.writeU32(1);// Write dword to TX buffer
    TWI.writeFL(1.0);// Write float to TX buffer

    uint8_t values[4];
    TWI.write(values, 4);// Write 4 bytes array to TX buffer
}

int main() {
    // Enable TWI module
    TWI.enable();

    // Set TWI module frequency (optional)
    TWI.setFrequency(400000u);

    // Configure slave address
    TWI.setAddress(0x0F);

    // Configure callbacks
    TWI.setOnReceiveHandler(onReceive);
    TWI.setOnRequestHandler(onRequest);
}
```
