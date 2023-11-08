#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <fcntl.h>
#include <termios.h>


#define BUF_SIZE 8
void error_handling(char *message);



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


int main(int argc, char *argv[])
{
   int sock;
   char message[BUF_SIZE];
   int str_len;
   struct sockaddr_in serv_adr;

   if(argc != 3)
   {
      printf("Usage : %s <IP> <port> \n", argv[0]);
      exit(1);
   }

   // ----------- 1. Create socket object ------------------
   sock = socket(PF_INET, SOCK_STREAM, 0);
   if(sock == -1)
      error_handling("socket() error");

   // serial port
   SerialPort port;
   if (serial_open(&port, "/dev/ttyACM0") == -1)
      {
        return -1;
      }

   // ------------ 2. Connect to server-- ------------------
   memset(&serv_adr, 0, sizeof(serv_adr));
   
   // Prepare the address
   serv_adr.sin_family = AF_INET;
   serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
   serv_adr.sin_port = htons(atoi(argv[2]));

   if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
      error_handling("connect() error!");
  else
      puts("Connect........");

   while(1)
   {
      fputs("Input message(Q to quit) : ", stdout);
      fgets(message, BUF_SIZE, stdin);

      if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
         break;

      write(sock, message, strlen(message));
      str_len = read(sock, message, BUF_SIZE - 1);
      message[str_len] = 0;
      printf("Message form server : %s", message);

      serial_write(&port, message, sizeof(message));

   }

   close(sock);
   return 0;
}

void error_handling(char *message)
{
   fputs(message, stderr);
   fputc('\n', stderr);
   exit(1);
}
