#ifndef TWI_H
#define TWI_H

#include <stdint.h>
#include <stddef.h>

#ifndef TWI_DEFAULT_FREQUENCY
#define TWI_DEFAULT_FREQUENCY 100000UL
#endif

#ifndef TWI_BUFFER_LENGTH
#define TWI_BUFFER_LENGTH 32
#endif

#ifndef TWI_ENABLE_MASTER
#define TWI_ENABLE_MASTER 1
#endif

#ifndef TWI_ENABLE_SLAVE
#define TWI_ENABLE_SLAVE 1
#endif

#define TWI_STATE_READY     0
#define TWI_STATE_MASTER_RX 1
#define TWI_STATE_MASTER_TX 2
#define TWI_STATE_SLAVE_RX  3
#define TWI_STATE_SLAVE_TX  4

#define TWI_ERROR_NONE     0xFF
#define TWI_ERROR_OVERFLOW 0xF0
#define TWI_ERROR_WRITE    0xF1
#define TWI_ERROR_READ     0xF2

enum TWIPrescaller {
    TWI_PRESCALLER_NONE,
    TWI_PRESCALLER_DIVIDE_BY_4,
    TWI_PRESCALLER_DIVIDE_BY_16,
    TWI_PRESCALLER_DIVIDE_BY_64,
};

class TWIClass
{
public:
    /**
     * Enable TWI module
     */
    void enable();

    /**
     * Disable TWI module
     */
    void disable();

    /**
     * Get error
     *
     * @return
     */
    uint8_t getError();

    /**
     * Set slave address
     *
     * @param address
     */
    void setAddress(uint8_t address);

    /**
     * Set prescaler value
     *
     * @param value
     */
    void setPrescaler(TWIPrescaller value);

    /**
     * Set TWI frequency to update bit-rate
     *
     * @param frequency
     */
    void setFrequency(uint32_t frequency);

    /**
     * @return
     */
    uint8_t readU08();

    /**
     * @return
     */
    uint16_t readU16();

    /**
     * @return
     */
    uint32_t readU32();

    /**
     * @return
     */
    float readFL();

    /**
     * Read array from TX buffer to pointer
     *
     * @param value
     * @param length
     */
    void read(uint8_t *data, uint8_t length);

    /**
     * @param value
     */
    void writeU08(uint8_t value);

    /**
     * @param value
     */
    void writeU16(uint16_t value);

    /**
     * @param value
     */
    void writeU32(uint32_t value);

    /**
     * @param value
     */
    void writeFL(float value);

    /**
     * Write values array to TX buffer
     *
     * @param data
     * @param length
     */
    void write(uint8_t *data, uint8_t length);

    /**
     * Blocking wait for TWI module become ready
     */
    void wait();

    /**
     * Receive data from slave
     *
     * @param address
     * @param length
     */
    void receive(uint8_t address, uint8_t length);

    /**
     * Receive data from slave
     *
     * @param address
     * @param length
     * @param stop
     */
    void receive(uint8_t address, uint8_t length, bool stop);

    /**
     * Prepare transmitting
     */
    void start();

    /**
     * Transmit data to slave
     *
     * @param address
     */
    void transmit(uint8_t address);

    /**
     * Transmit data to slave
     *
     * @param address
     * @param stop
     */
    void transmit(uint8_t address, bool stop);

    /**
     * Set handler for master transmit data completed event
     *
     * @param handler_ptr
     */
    void setOnTransmitHandler(void (*handler_ptr) ());

    /**
     * Set handler for slave receive data completed event
     *
     * @param handler_ptr
     */
    void setOnReceiveHandler(void (*handler_ptr) ());

    /**
     * Set handler for slave transmit data requested event
     *
     * @param handler_ptr
     */
    void setOnRequestHandler(void (*handler_ptr) ());
};

extern TWIClass TWI;

#endif //TWI_H
