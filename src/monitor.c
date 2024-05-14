#include <avr/io.h>
#include "uart.h"

void monitor_init(int baudrate) {
  unsigned int ubrr = ((F_CPU / (16UL * baudrate)) - 1);
  // Set baud rate Page 203
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;

  // Enable receiver and transmitter. Page 220
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);

  // Set frame format: 8 data bits, 1 stop bit, no parity page 221
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}
void monitor_send(char *data) {
  while (*data) {
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)));

    // Put data into buffer, sends the data
    UDR0 = *data;
    data++;
  }
}

char* monitor_receive() {
  static char buffer[64];
  char *bufPtr = buffer;
  char received;

  // Clear buffer
  for (int i = 0; i < 64; i++) {
    buffer[i] = '\0';
  }

  do {
    // Wait for data to be received
    while (!(UCSR0A & (1 << RXC0)));

    // Get and return received data from buffer
    received = UDR0;
    *bufPtr++ = received;

    // Check for buffer overflow
    if (bufPtr - buffer >= 63) {
      break;
    }
  } while (received != '\n' && received != '\r');
  return buffer;
}