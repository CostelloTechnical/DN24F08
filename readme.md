# DN24F08 Arduino Library

## Introduction
This is a library to control the **DN24F08**, a PLC-style expansion board for the Arduino Nano form factor.  
**Note:** This library was written specifically for the ATmega328p (Nano V3) version due to direct register manipulation.

The board typically comes in several variations: with or without DIN rail mounts, relay or Darlington array outputs (DN23E08 vs DN24F08), and 12V or 24V logic. This library was developed using the **24V, DIN rail mount, Darlington array** version.

## Library Features
* **RAM Optimization:** The library is optimized to reduce RAM usage (e.g., accessing constant arrays via `PROGMEM`).
* **Bare Metal UART:** Includes a custom "bare metal" UART library to replace the heavy Arduino `Serial` class. This allows precise control over RX/TX buffer sizes (the TX buffer was removed entirely to save memory).
* **RTOS Ready:** The low memory footprint makes this library ideal for use with RTOS implementations on the ATmega328p.

![DN24F08 Board](./extras/images/DN24F08.jpg)
*The DN24F08 board.*

## Connectivity & Hardware

### 1. Analog Inputs
The board features 8 analog inputs: 4 for current and 4 for voltage.

| Type | Board Names | Arduino Pins | Range | Conversion Method |
| :--- | :--- | :--- | :--- | :--- |
| **Current** | I1 - I4 | A0 - A3 | 0 - 20 mA | Shunt Resistor + LM324DR Buffer |
| **Voltage** | V1 - V4 | A4 - A7 | 0 - 10 V | Voltage Divider + LM324DR Buffer |

### 2. Digital Inputs
* **Acquisition:** 74HC165 (8-bit parallel-load shift register).
* **Type:** NPN (Sinking). The input must be pulled low (to ground) to register a signal.
* **Range:** 0-12V or 0-24V (depending on board model).

| Board Names | Arduino Mapping |
| :--- | :--- |
| IN1 - IN8 | Read via Shift Register |

### 3. User Buttons
There are 4 SMD buttons on the board.

| Board Name | Arduino Pin | Type |
| :--- | :--- | :--- |
| KEY1 | D5 | Input (Pull-up) |
| KEY2 | D6 | Input (Pull-up) |
| KEY3 | D7 | Input (Pull-up) |
| KEY4 | D8 | Input (Pull-up) |

### 4. Digital Outputs
The outputs are controlled by a daisy chain of **74HC595D** shift registers. The final register in the chain drives a **ULN2803** Darlington transistor array (NPN output with built-in flyback diodes).

* **Outputs:** 8
* **Board Names:** OUT1 - OUT8
* **Range:** 0-50V

### 5. Seven Segment Display
* **Size:** 4 Character, 7 Segment.
* **Control:** Driven by two 74HC595D shift registers (part of the same chain as the digital outputs).

### 6. RS485 Communication
* **Chip:** SP485.
* **Board Names:** A+ and B-.
* **Pins:** Hardwired to the Nano's RX/TX pins.
* **Control Pin:** D13 is used to toggle Receive/Transmit modes (handled automatically by the library).

**Important:**
1.  **DIP Switch:** To use RS485, the onboard DIP switch must be in the `485_ON` position.
2.  **Programming:** To upload code to the Nano via USB, you must switch the DIP switch to the `PRO` position.

---