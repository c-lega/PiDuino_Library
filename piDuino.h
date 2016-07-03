/*
*   piDuino Library
*
*   Arduino like functions for (Raspberry Pi Zero)
*   piDuino is a fork of arduPi ->
*   (https://www.cooking-hacks.com/documentation/tutorials/raspberry-pi-to-arduino-shields-connection-bridge/)
*
*   version: 1.0.0
*   author: Jorge Garza (jgarzagu@gmail.com)
*   
*/

#ifndef piDuino_h
#define piDuino_h

#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <string.h>
#include <time.h>
#include <termios.h> 
#include <ctype.h>
#include <sys/ioctl.h>
#include <limits.h>
#include <algorithm>
#include <limits.h>
#include <pthread.h>
#include <poll.h>
#include <stdarg.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/spi/spidev.h>
#include "WString.h"


// Total Number of GPIOs Pins in BCM283x SoC chips
#define SOC_GPIO_PINS   54   

// Remove some PROGMEM space macros if posible
#define PROGMEM
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#define pgm_read_word(addr) (*(const unsigned short *)(addr))
#define pgm_read_dword(addr) (*(const unsigned long *)(addr))
#define pgm_read_float(addr) (*(const float *)(addr))
#define pgm_read_ptr(addr) (*(const void *)(addr))

// All functions of unistd.h must be called like this: unistd::the_function()
namespace unistd {
    #include <unistd.h>
};


// Arduino extra types
typedef bool boolean;
typedef uint8_t byte;
typedef unsigned int word;
#define B00000000 0
#define B00000001 1
#define B00000010 2
#define B00000011 3
#define B00000100 4
#define B00000101 5
#define B00000110 6
#define B00000111 7
#define B00001000 8
#define B00001001 9
#define B00001010 10
#define B00001011 11
#define B00001100 12
#define B00001101 13
#define B00001110 14
#define B00001111 15
#define B00010000 16
#define B00010001 17
#define B00010010 18
#define B00010011 19
#define B00010100 20
#define B00010101 21
#define B00010110 22
#define B00010111 23
#define B00011000 24
#define B00011001 25
#define B00011010 26
#define B00011011 27
#define B00011100 28
#define B00011101 29
#define B00011110 30
#define B00011111 31
#define B00100000 32
#define B00100001 33
#define B00100010 34
#define B00100011 35
#define B00100100 36
#define B00100101 37
#define B00100110 38
#define B00100111 39
#define B00101000 40
#define B00101001 41
#define B00101010 42
#define B00101011 43
#define B00101100 44
#define B00101101 45
#define B00101110 46
#define B00101111 47
#define B00110000 48
#define B00110001 49
#define B00110010 50
#define B00110011 51
#define B00110100 52
#define B00110101 53
#define B00110110 54
#define B00110111 55
#define B00111000 56
#define B00111001 57
#define B00111010 58
#define B00111011 59
#define B00111100 60
#define B00111101 61
#define B00111110 62
#define B00111111 63
#define B01000000 64
#define B01000001 65
#define B01000010 66
#define B01000011 67
#define B01000100 68
#define B01000101 69
#define B01000110 70
#define B01000111 71
#define B01001000 72
#define B01001001 73
#define B01001010 74
#define B01001011 75
#define B01001100 76
#define B01001101 77
#define B01001110 78
#define B01001111 79
#define B01010000 80
#define B01010001 81
#define B01010010 82
#define B01010011 83
#define B01010100 84
#define B01010101 85
#define B01010110 86
#define B01010111 87
#define B01011000 88
#define B01011001 89
#define B01011010 90
#define B01011011 91
#define B01011100 92
#define B01011101 93
#define B01011110 94
#define B01011111 95
#define B01100000 96
#define B01100001 97
#define B01100010 98
#define B01100011 99
#define B01100100 100
#define B01100101 101
#define B01100110 102
#define B01100111 103
#define B01101000 104
#define B01101001 105
#define B01101010 106
#define B01101011 107
#define B01101100 108
#define B01101101 109
#define B01101110 110
#define B01101111 111
#define B01110000 112
#define B01110001 113
#define B01110010 114
#define B01110011 115
#define B01110100 116
#define B01110101 117
#define B01110110 118
#define B01110111 119
#define B01111000 120
#define B01111001 121
#define B01111010 122
#define B01111011 123
#define B01111100 124
#define B01111101 125
#define B01111110 126
#define B01111111 127
#define B10000000 128
#define B10000001 129
#define B10000010 130
#define B10000011 131
#define B10000100 132
#define B10000101 133
#define B10000110 134
#define B10000111 135
#define B10001000 136
#define B10001001 137
#define B10001010 138
#define B10001011 139
#define B10001100 140
#define B10001101 141
#define B10001110 142
#define B10001111 143
#define B10010000 144
#define B10010001 145
#define B10010010 146
#define B10010011 147
#define B10010100 148
#define B10010101 149
#define B10010110 150
#define B10010111 151
#define B10011000 152
#define B10011001 153
#define B10011010 154
#define B10011011 155
#define B10011100 156
#define B10011101 157
#define B10011110 158
#define B10011111 159
#define B10100000 160
#define B10100001 161
#define B10100010 162
#define B10100011 163
#define B10100100 164
#define B10100101 165
#define B10100110 166
#define B10100111 167
#define B10101000 168
#define B10101001 169
#define B10101010 170
#define B10101011 171
#define B10101100 172
#define B10101101 173
#define B10101110 174
#define B10101111 175
#define B10110000 176
#define B10110001 177
#define B10110010 178
#define B10110011 179
#define B10110100 180
#define B10110101 181
#define B10110110 182
#define B10110111 183
#define B10111000 184
#define B10111001 185
#define B10111010 186
#define B10111011 187
#define B10111100 188
#define B10111101 189
#define B10111110 190
#define B10111111 191
#define B11000000 192
#define B11000001 193
#define B11000010 194
#define B11000011 195
#define B11000100 196
#define B11000101 197
#define B11000110 198
#define B11000111 199
#define B11001000 200
#define B11001001 201
#define B11001010 202
#define B11001011 203
#define B11001100 204
#define B11001101 205
#define B11001110 206
#define B11001111 207
#define B11010000 208
#define B11010001 209
#define B11010010 210
#define B11010011 211
#define B11010100 212
#define B11010101 213
#define B11010110 214
#define B11010111 215
#define B11011000 216
#define B11011001 217
#define B11011010 218
#define B11011011 219
#define B11011100 220
#define B11011101 221
#define B11011110 222
#define B11011111 223
#define B11100000 224
#define B11100001 225
#define B11100010 226
#define B11100011 227
#define B11100100 228
#define B11100101 229
#define B11100110 230
#define B11100111 231
#define B11101000 232
#define B11101001 233
#define B11101010 234
#define B11101011 235
#define B11101100 236
#define B11101101 237
#define B11101110 238
#define B11101111 239
#define B11110000 240
#define B11110001 241
#define B11110010 242
#define B11110011 243
#define B11110100 244
#define B11110101 245
#define B11110110 246
#define B11110111 247
#define B11111000 248
#define B11111001 249
#define B11111010 250
#define B11111011 251
#define B11111100 252
#define B11111101 253
#define B11111110 254
#define B11111111 255



/////////////////////////////////////////////
//          SerialPi class (UART)         //
////////////////////////////////////////////

// Printing format options
#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

// Defines for setting data, parity, and stop bits
// e.g SERIAL_ABC
// A= data (5 bits, 6 bits, 7 bits, 8 bits)
// B= parity (None, Even, Odd)
// C= stop bits (1 bit, 2 bits) 
#define SERIAL_5N1 0x00
#define SERIAL_6N1 0x02
#define SERIAL_7N1 0x04
#define SERIAL_8N1 0x06 // default
#define SERIAL_5N2 0x08
#define SERIAL_6N2 0x0A
#define SERIAL_7N2 0x0C
#define SERIAL_8N2 0x0E
#define SERIAL_5E1 0x20
#define SERIAL_6E1 0x22
#define SERIAL_7E1 0x24
#define SERIAL_8E1 0x26
#define SERIAL_5E2 0x28
#define SERIAL_6E2 0x2A
#define SERIAL_7E2 0x2C
#define SERIAL_8E2 0x2E
#define SERIAL_5O1 0x30
#define SERIAL_6O1 0x32
#define SERIAL_7O1 0x34
#define SERIAL_8O1 0x36
#define SERIAL_5O2 0x38
#define SERIAL_6O2 0x3A
#define SERIAL_7O2 0x3C
#define SERIAL_8O2 0x3E

// A char not found in a valid ASCII numeric field
#define NO_IGNORE_CHAR  '\x01' 

// Serial Driver name (user can change it)
extern char GPIO_DRIVER_NAME[];


class SerialPi {

private:
	int fd;
	FILE * fd_file;
	long timeOut;
	timespec timeDiff(timespec start, timespec end);
	int timedPeek();
	int peekNextDigit(bool detectDecimal);
	long timeDiffmillis(timespec start, timespec end);
	char * int2bin(int n);

public:
	SerialPi();
	void begin(int baud, unsigned char config = SERIAL_8N1);
	void begin(const char *serialPort, int baud, unsigned char config = SERIAL_8N1);
	void end();
	int available();
	int availableForWrite();
	bool find(const char *target);
	bool findUntil(const char *target, const char *terminator);
	void flush();
	long parseInt() { return parseInt(NO_IGNORE_CHAR); };
	long parseInt(char ignore);
	float parseFloat();
	int peek();
	size_t print(const String &s);
	size_t print(const char str[]);
	size_t print(char c);
	size_t print(unsigned char b, int base);
	size_t print(int n, int base);
	size_t print(unsigned int n, int base);
	size_t println(void);
	size_t println(const String &s);
	size_t println(const char c[]);
	size_t println(char c);
	size_t println(unsigned char b, int base);
	size_t println(int num, int base);
	size_t println(unsigned int num, int base);
	size_t printf(const char *fmt, ... );
	int read();
	size_t readBytes(char buffer[], size_t length);
	size_t readBytesUntil(char terminator, char buffer[], size_t length);
	String readString();
	String readStringUntil(char terminator);
	size_t readStringCommand(char terminator, char buffer[], size_t length);
	void setTimeout(long millis);
	size_t write(uint8_t c);
	size_t write(const char *str);
	size_t write(char *buffer, size_t size);
	operator bool() { return (fd == -1) ? false : true; }
	
};




/////////////////////////////////////////////
//          WirePi class (I2C)             //
////////////////////////////////////////////

#define I2C_SLAVE 0x0703
#define BUFFER_LENGTH 32

extern char I2C_DRIVER_NAME[]; 

class WirePi {
	private:
		int fd;
        static uint8_t rxBuffer[];
        static uint8_t rxBufferIndex;
        static uint8_t rxBufferLength;

        static uint8_t txBuffer[];
        static uint8_t txBufferIndex;
        static uint8_t txBufferLength;

        static uint8_t transmitting;

        int i2c_write_bytes(int file, uint8_t *txBuff, size_t numBytes);
        int i2c_read_bytes(int file, uint8_t *rxBuff, size_t numBytes);

	public:
		WirePi();
		void begin();
		void begin(const char *i2cDeviceName);
		void end();
		uint8_t  requestFrom(uint8_t address, uint8_t quantity);
		void beginTransmission(uint8_t address);
		uint8_t endTransmission();		
		size_t write(uint8_t data);
		size_t write(const char *data);
		size_t write(uint8_t *data, size_t quantity);
		int available(void);
		int read(void);
		
};




/////////////////////////////////////////////
//          SPIPi class (SPI)             //
////////////////////////////////////////////

#ifndef LSBFIRST
#define LSBFIRST 1
#endif
#ifndef MSBFIRST
#define MSBFIRST 0
#endif

// SPI Modes 
#define SPI_MODE0 SPI_MODE_0 
#define SPI_MODE1 SPI_MODE_1
#define SPI_MODE2 SPI_MODE_2
#define SPI_MODE3 SPI_MODE_3

// SPI Speed taking a 16 Mhz arduino clock speed
#define SPI_CLOCK_DIV2 8000000
#define SPI_CLOCK_DIV4 4000000
#define SPI_CLOCK_DIV8 2000000
#define SPI_CLOCK_DIV16 1000000
#define SPI_CLOCK_DIV32 500000
#define SPI_CLOCK_DIV64 250000
#define SPI_CLOCK_DIV128 125000

extern char SPI_DRIVER_NAME[]; 

class SPISettings {
	private:
		uint32_t spiClock;
		uint8_t spiBitOrder;
		uint8_t spiDataMode;
	public:
		SPISettings() {
			spiClock = 4000000;
			spiBitOrder = MSBFIRST;
			spiDataMode = SPI_MODE0;
		}

		SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {
			spiClock = clock;
			spiBitOrder = bitOrder;
			spiDataMode = dataMode;
		}

	friend class SPIPi;
};

class SPIPi {
	private:
		int fd;
		void spi_transfer_bytes(int file, uint8_t *data, size_t numBytes);
	public:
		SPIPi();
  		void begin();
  		void begin(const char *spiDeviceName);
    	void end();
    	void beginTransaction(SPISettings settings);
    	void endTransaction();
    	void setBitOrder(uint8_t bitOrder);
 		void setClockDivider(uint32_t clockDiv);
		void setDataMode(uint8_t dataMode);
 		uint8_t transfer(uint8_t data);
 		uint16_t transfer16(uint16_t data);
 		void transfer(void *buf, size_t count);
};


/////////////////////////////////////////////
//    Extra Arduino Functions for Linux/Pi //
////////////////////////////////////////////
extern void (*ARDUINO_EXIT_FUNC)(void);


class ArduinoPi {                                 
    public:
        struct timespec timestamp;
        ArduinoPi();
        static void onArduinoExit(int signumber);
};


/////////////////////////////////////////////
//          Digital I/O           		  //
////////////////////////////////////////////
// Pin logic states
#define HIGH 0x1
#define LOW  0x0

// Pin modes
#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2
#define INPUT_PULLDOWN 0x3
#define PWM_OUTPUT 0x4

// GPIO Driver name (user can change it)
extern char GPIO_DRIVER_NAME[];

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t value);
int digitalRead(uint8_t pin);

/////////////////////////////////////////////
//          Analog I/O           		  //
////////////////////////////////////////////
extern char PWM_DRIVER_NAME[];
extern int PWM_DUTYCYCLE_RESOLUTION;
extern int PWM_DEFAULT_FREQUENCY;

//int analogRead (int pin); // Not implemented
//int analogReference(int type) // Not implemened
void analogWrite(uint8_t pin, uint32_t value);
void setPwmDutyCycle (uint8_t pin, uint32_t dutycycle);
void setPwmFPeriod (uint8_t pin, uint32_t microseconds);
void setPwmFrequency (uint8_t pin, uint32_t frequency);
void setPwmFrequency (uint8_t pin, uint32_t frequency, uint32_t dutycycle);

/////////////////////////////////////////////
//          Advanced I/O           		  //
////////////////////////////////////////////

void tone(uint8_t pin, uint32_t frequency, unsigned long duration = 0, uint32_t block = false);
void noTone(uint8_t pin);
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);

/////////////////////////////////////////////
//          Time      		     		  //
////////////////////////////////////////////

unsigned long millis(void);
unsigned long micros(void);
void delay(unsigned long millis);
void delayMicroseconds(unsigned int us);

/////////////////////////////////////////////
//          Math           				  //
////////////////////////////////////////////

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352


// min and max implemented as fucntions to prevent 
// std::min and std::max conflicts with <string> header
inline int min(int a, int b) { return ((a)<(b) ? (a) : (b)); }
inline float min(float a, float b) { return ((a)<(b) ? (a) : (b)); }
inline double min(double a, double b) { return ((a)<(b) ? (a) : (b)); }
inline int max(int a, int b) { return ((a)>(b) ? (a) : (b)); }
inline float max(float a, float b) { return ((a)>(b) ? (a) : (b)); }
inline double max(double a, double b) { return ((a)>(b) ? (a) : (b)); }
// #define abs(x) ((x)>0?(x):-(x)) // abs already in <stdlib.h>

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

long map(long x, long in_min, long in_max, long out_min, long out_max);
// pow() already in <math.h>...

/////////////////////////////////////////////
//          Trigonometry          		  //
////////////////////////////////////////////

// sin(rad) already in <math.h>...
// cos(rad) already in <math.h>...
// tan(rad) already in <math.h>...

/////////////////////////////////////////////
//          Characters           		  //
////////////////////////////////////////////

inline boolean isAlphaNumeric(int c) __attribute__((always_inline));
inline boolean isAlpha(int c) __attribute__((always_inline));
inline boolean isAscii(int c) __attribute__((always_inline));
inline boolean isWhitespace(int c) __attribute__((always_inline));
inline boolean isControl(int c) __attribute__((always_inline));
inline boolean isDigit(int c) __attribute__((always_inline));
inline boolean isGraph(int c) __attribute__((always_inline));
inline boolean isLowerCase(int c) __attribute__((always_inline));
inline boolean isPrintable(int c) __attribute__((always_inline));
inline boolean isPunct(int c) __attribute__((always_inline));
inline boolean isSpace(int c) __attribute__((always_inline));
inline boolean isUpperCase(int c) __attribute__((always_inline));
inline boolean isHexadecimalDigit(int c) __attribute__((always_inline));
inline int toAscii(int c) __attribute__((always_inline));
inline int toLowerCase(int c) __attribute__((always_inline));
inline int toUpperCase(int c)__attribute__((always_inline));

/////////////////////////////////////////////
//          Random Functions       		  //
////////////////////////////////////////////

void randomSeed(unsigned long);
long random(long);
long random(long, long);

/////////////////////////////////////////////
//          Bits and Bytes         		  //
////////////////////////////////////////////

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bit(b) (1UL << (b))

/////////////////////////////////////////////
//          External Interrupts    		  //
////////////////////////////////////////////

// Interrupt modes
#define CHANGE 1
#define FALLING 2
#define RISING 3

#define NOT_AN_INTERRUPT -1
#define digitalPinToInterrupt(p) ((p) >= 0 && (p) <= SOC_GPIO_PINS ? (p) : NOT_AN_INTERRUPT)

void attachInterrupt(uint8_t pin, void (*f)(void), int mode);
void detachInterrupt(uint8_t pin);

/////////////////////////////////////////////
//          Interrupts           		  //
////////////////////////////////////////////


extern ArduinoPi Arduino;
extern SerialPi Serial;
extern WirePi Wire;
extern SPIPi SPI;


#endif
