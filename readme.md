## Intro
This is a library to control the DN24F08, a PLC type expansion board for the Arduino Nano form factor. However, this library was written specifically for the ATmega328p version.  

I came across the board on AliExpress and was curious enough to buy one as it was was only ~€20 at the time.  

The board typically comes in a number of different forms, with or without DIN rail mount, relay or darlington array (DN23E08 or DN24F08 respectively) and 12V or 24V. The model I got was the 24V, DIN rail mount, darlington array version.  

I have optimized the to reduce RAM usage, so along with the control logic I have included an additional library for bare metal UART communication.  

![board_image](./images/DN24F08.jpg)
*The DN24F08 board.*

## Connectivity
### 1. Analog Inputs
#### 1.1 Voltage Reading:

#### 1.2 Current Reading:

### 2. Digital Inputs

### 3. Buttons

### 4. Digital Outputs

### 5. Four Character, Seven Segment Display

### 6. RS485

## Library Features

## Conclusion