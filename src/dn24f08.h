/*
  ==============================================================================
                                  DISCLAIMER
  ==============================================================================

  This software is provided "as is", without warranty of any kind, express or
  implied, including but not to the warranties of merchantability,
  fitness for a particular purpose and noninfringement. In no event shall the
  authors or copyright holders be liable for any claim, damages or other
  liability, whether in an action of contract, tort or otherwise, arising from,
  out of or in connection with the software or the use or other dealings in the
  software.

  ==============================================================================
                              PERMISSION TO USE
  ==============================================================================

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so.

  It is highly encouraged that if you find this library useful, you provide
  attribution back to the original author.
*/
#ifndef DN24F08_H
#define DN24F08_H
#include <Arduino.h>
#include <avr/pgmspace.h>
#include "bareSerial.h"

enum buttonsInputs : uint8_t {
    KEY1 = 1,
    KEY2 = 2,
    KEY3 = 3,
    KEY4 = 4
};

enum analogInputs : uint8_t {
    I1 = 0,
    I2 = 1,
    I3 = 2,
    I4 = 3,
    V1 = 4,
    V2 = 5,
    V3 = 6,
    V4 = 7
};

enum digitalInputs : uint8_t {
    IN1 = 1,
    IN2 = 2,
    IN3 = 3,
    IN4 = 4,
    IN5 = 5,
    IN6 = 6,
    IN7 = 7,
    IN8 = 8
};

enum digitalOutputs : uint8_t{
    CH1 = 1,
    CH2 = 2,
    CH3 = 3,
    CH4 = 4,
    CH5 = 5,
    CH6 = 6,
    CH7 = 7,
    CH8 = 8
};

enum engineAverageType : uint8_t{
    TIME_MS = 0,
    READINGS = 1
};

enum engineDisplayType : uint8_t{
    IDLE = 0,
    CLEAR = 1,
    ANALOG = 2,
    INTEGER = 3,
};

class dn24f08 {
    public:
        dn24f08(const float* gains = NULL, const float* offsets = NULL);
        static dn24f08* _classPointer;
        // Used to store the previous PINB value to detect a change.
        static volatile uint8_t _previousPortB;

        // Used to store the previous PIND value to detect a change.
        static volatile uint8_t _previousPortD;

        static const uint8_t _analogPins = 8;

        // Initializer if intending to use the Serial class with a start character and end character.
        void init(uint32_t baud, char startCharacter, char endCharacter, uint16_t timeout = 3000);

        // Initializer if intending to use the Serial class with only an end character.
        void init(uint32_t baud = 9600, char endCharacter = '\n', uint16_t timeout = 3000);

        // Sets the value of the 8 outputs in binary. (Updated with display engine)
        void setOutputs(uint8_t outputs);

        // Set the value of a single output. (Updated with display engine)
        void setOutput(uint8_t output, bool state);

        /*  Set the type of analog engine to be used, a time or readings based system.
            The value is either milliseconds or number oif readings.*/
        void setAnalogEngineType(engineAverageType type, uint16_t value);

        // Set if the display should be cleared, show an analog input or an integer.
        void setDisplayEngineType(engineDisplayType type);

        // Sets the analog input to display (engineDisplay must be running and type set to analog)
        void setDisplayAnalogPin(analogInputs pin);

        // Sets a integer to display (engineDisplay must be running and type set to integer)
        void setDisplayInteger(uint16_t number);

        // Used in the ISR when a button push was detected. Final check and debounce done in engineButtons.
        void setCheckButton(uint8_t pin);

        // Returns a true if a debounced button push was registered for a given button.
        bool getKeyPressed(uint8_t key);

        // Returns the 8 output values as a binary number.
        uint8_t getOutputs();

        // Returns the state of a single output.
        bool getOutput(uint8_t output);

        // Returns the 8 input values as a binary number.
        uint8_t getInputs();

        // Returns the state of a single input.
        bool getInput(uint8_t input);

        // Returns the value of single analog input.
        float getAnalog(analogInputs input);

        // Returns the averaged value of an analog input. (analog engine must be running)
        float getAnalogAverage(analogInputs input);

        // Handles the averaging of the analog inputs as per the type. (Time or readings)
        void engineAnalogAverage();

        // Handles the different display types and updating the outputs.
        void engineDisplay();

        // Handles the buttons. Checks if a buttons was pressed, including debounce.
        void engineButtons();

        // Handles incoming serial data.
        void engineCommunication();

        // Wrapper for the other engines.
        void engine();

        // Displays the float on the 7 segment display.
        void displayFloat(float number);

        // Displays the integer on the 7 segment display.
        void displayInteger(uint16_t number);

        // Clears the 7 segment display.
        void displayClear();

        void print(long number);
        void print(unsigned long number);
        void println(long number);
        void println(unsigned long number);
 
        // These handle standard ints, shorts, and bytes automatically
        void print(int number)              { print((long)number); }
        void print(unsigned int number)     { print((unsigned long)number); }
        void print(short number)            { print((long)number); }
        void print(unsigned short number)   { print((unsigned long)number); }
        void print(uint8_t number)          { print((unsigned long)number); }
        void print(bool number)             { print((unsigned long)number); }
        
        // Matching println redirects
        void println(int number)            { println((long)number); }
        void println(unsigned int number)   { println((unsigned long)number); }
        void println(short number)          { println((long)number); }
        void println(unsigned short number) { println((unsigned long)number); }
        void println(uint8_t number)        { println((unsigned long)number); }
        void println(bool number)           { println((unsigned long)number); }

        // Prints a float. Default precision is 2.
        void print(float number, uint8_t precision = 2);

        // Prints a float and newline. Default precision is 2.
        void println(float number, uint8_t precision = 2);

        void print(const __FlashStringHelper *toPrint);

        void println(const __FlashStringHelper *toPrint);

        // Print a c-string over RS485
        void print(const char *toPrint);

        // Print a c-string over RS485 with a newline
        void println(const char *toPrint);

        // Send a single character over RS485
        void write( char toPrint);

        // Returns true if the communication engine received a valid message.
        bool getDataReady();

        // Returns if there was a timeout.
        bool getTimedOut();

        // Returns the received message.
        char* getReceivedCharacters();

    private:
        // Initializer for Pin modes etc...
        void initSystem();

        // Converts float to string and stores it in _converter
        void convertFloat(float val, uint8_t precision);

        // Writes to the three 74HC595D ICs controlling the digital outputs and 7 segment display.
        void setShift(uint8_t number, uint8_t digit, bool useDecimal);

        struct systemStates{
            uint8_t useStartCharacter  : 1;
            uint8_t dataReady          : 1;
            uint8_t receivingData      : 1;
            uint8_t timedOut           : 1;
            uint8_t analogAverageType  : 1;
            uint8_t analogPinIterator  : 3;
        }_system = {0, 0, 0, 0, 0, 0};

        struct displayStates{
            uint8_t update     : 1;
            uint8_t type       : 2;
            uint8_t analogPin  : 3;
        }_display= {0, 0, 0};
        
        static const uint8_t _buttons = 4;
        static const uint8_t _keys[_buttons];
 
        volatile uint8_t _checkButtons = 0;  // This variables holds the state for all the buttons. Values are set using bitwise.
        uint8_t _pressedFlags = 0;           // This variables holds the state for all the buttons. Values are set using bitwise.
        uint16_t _checkCache_ms[_buttons] = {0, 0, 0, 0};
        static const uint16_t _debounce_ms = 100;

        static const uint8_t _inData = 2;
        static const uint8_t _inClock = 3;
        static const uint8_t _inLoad = 4;

        static const uint8_t _key1 = 5; // (PD5) (PCINT21) (PCIE2)
        static const uint8_t _key2 = 6; // (PD6) (PCINT22) (PCIE2)
        static const uint8_t _key3 = 7; // (PD7) (PCINT23) (PCIE2)
        static const uint8_t _key4 = 8; // (PB0) (PCINT0) (PCIE0)

        static const uint8_t _outData = 9;
        static const uint8_t _outEnable = 10;
        static const uint8_t _outLoad = 11;
        static const uint8_t _outClock = 12;


        static const uint8_t _segmentCharacters[37];
        static const uint8_t _digitEnable[4];

        static const uint8_t _rxTxPin = 13;

        static const uint8_t _decimalPoint = 0x1;

        static const uint8_t _analogInputPins[_analogPins];
        const float* _gains;
        const float* _offsets;
        static const float _analogToCurrent = 0.019550; // 20 / 1023
        static const float _analogToVoltage = 0.009775; // 10 / 1023

        float _averageAnalog[_analogPins] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
        uint32_t _averageSum[_analogPins] = { 0, 0, 0, 0, 0, 0, 0, 0 };
        uint16_t _averageTime_ms[_analogPins] = { 0, 0, 0, 0, 0, 0, 0, 0 };
        uint16_t _averageCounter[_analogPins] = { 0, 0, 0, 0, 0, 0, 0, 0 };

        char _converter[25];
        uint8_t _outputValue = 0;
        uint8_t _inputValue = 0;

        uint16_t _displayNumber = 0;

        uint16_t _analogAverageValue = 100;

        uint16_t _timeout;
        uint16_t _timeoutCache = millis();
        static const uint8_t _maxCharacters = 50;
        char _startCharacter;
        char _endCharacter;
        char _receivedCharacter;
        uint8_t _receivedCharacterIndex = 0;
        char _receivedCharacters[_maxCharacters];
        bareSerial _serialPort;
};
#endif