#include <stdio.h>
#include <string.h>
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()


int main(){

    int serialPort = open("/dev/ttyUSB0",O_RDWR);

    struct termios serial;
      if(tcgetattr(serialPort, &serial) != 0) {
      printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
      return 1;
    }

    serial.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    serial.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
    serial.c_cflag &= ~CSIZE; // Clear all bits that set the data size
    serial.c_cflag |= CS8; // 8 bits per byte (most common)
    //serial.c_cflag &= ~ CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    serial.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    serial.c_lflag &= ~ICANON;
    serial.c_lflag &= ~ECHO; // Disable echo
    serial.c_lflag &= ~ECHOE; // Disable erasure
    serial.c_lflag &= ~ECHONL; // Disable new-line echo
    serial.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    serial.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    serial.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

    serial.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    serial.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
    // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

    serial.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    serial.c_cc[VMIN] = 0;

    cfsetispeed(&serial,B9600);
    cfsetospeed(&serial,B9600);
    
    if (tcsetattr(serialPort, TCSANOW, &serial) != 0) {
      printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
      return 1;
    }

    char read_buff[256];

    memset(&read_buff, '\0', sizeof(read_buff));

    int num_bytes = read(serialPort, &read_buff, sizeof(read_buff));

    if (num_bytes < 0) {
      printf("Error reading: %s", strerror(errno));
      return 1;
    }

    printf("Read %i bytes. Received message: %s", num_bytes, read_buff);

    close(serialPort);

    return 0;
}