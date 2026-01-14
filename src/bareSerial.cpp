#include "bareSerial.h"

// Allocate memory for the static members
volatile char bareSerial::_rxBuffer[RX_BUFFER_SIZE];
volatile uint8_t bareSerial::_rxHead = 0;
volatile uint8_t bareSerial::_rxTail = 0;

// The Interrupt Service Routine
// This runs automatically whenever a byte arrives on the RX pin.
ISR(USART_RX_vect) {
    // Read the received byte from the hardware register
    char c = UDR0;

    // Calculate the next head position
    uint8_t nextHead = (bareSerial::_rxHead + 1) % RX_BUFFER_SIZE;

    // If the next position is NOT the tail, we have room.
    // If it IS the tail, the buffer is full, so we drop the byte.
    if (nextHead != bareSerial::_rxTail) {
        bareSerial::_rxBuffer[bareSerial::_rxHead] = c;
        bareSerial::_rxHead = nextHead;
    }
}