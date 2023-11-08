#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

typedef struct
{
    int fd;
} SerialPort;

int serial_open(SerialPort *port, const char *device)
{
    port->fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
    if (port->fd == -1)
    {
        perror("Unable to open port");
         printf("Unable to open port");
        return -1;
    }

    struct termios options;
    tcgetattr(port->fd, &options);
    cfsetispeed(&options, B9600); // Set baud rate to 9600 (adjust as needed)
    cfsetospeed(&options, B9600);

    options.c_cflag |= CS8;     // 8 data bits
    options.c_cflag &= ~PARENB; // No parity
    options.c_cflag &= ~CSTOPB; // One stop bit
    //options.c_cflag &= ~CSIZE;  // Mask the character size bits


    tcsetattr(port->fd, TCSANOW, &options);

    return 0;
}

void serial_close(SerialPort *port)
{
    close(port->fd);
    port->fd = -1;
}

int serial_read(SerialPort *port, char *buffer, size_t size)
{
    return read(port->fd, buffer, size);
}

ssize_t serial_write(SerialPort *port, char *buffer, size_t size)
{
    return write(port->fd, buffer, size);
}

int main(void)
{ 
    SerialPort port;
    if (serial_open(&port, "/dev/ttyACM0") == -1)
    {
        return -1;
    }
   
    char buffer[8];
    char rcv_buffer[8];    
    int rcv_int;

    serial_write(&port, "serial!", sizeof(buffer));

    // for (int i = 0; i < sizeof(rcv_buffer); i++)
    // {    
    //     printf("%d : %c",i, rcv_buffer[i]);
    // }
    
    // memset(&rcv_buffer, '\0', sizeof(rcv_buffer));

    // serial_read(&port, rcv_buffer, sizeof(rcv_buffer));

    // while (1) {
    //     rcv_int = serial_read(&port, rcv_buffer, sizeof(rcv_buffer)-1);

    //     if (rcv_int > 0) {
    //         rcv_buffer[rcv_int] = '\0';
    //         printf("Received: %s", rcv_buffer);
    //     }
    // }
    serial_close(&port);

    return 0;
}