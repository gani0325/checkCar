#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <fcntl.h>
#include <termios.h>

#define BUF_SIZE 16
void error_handling(char *message);

typedef struct
{
   // 파일 디스크립터 : 어떠한 통신 포트를 열었을 때 컴퓨터가 찾아가기 쉽게 정수로 숫자 매김
   int fd;
} SerialPort;

// device : 열고 싶은 시리얼 포트의 이름
int serial_open(SerialPort *port, const char *device)
{
   // open : 문자열로 선언된 경로(device)를 받아서 파일 디스크립터(fd)로 반환하는 함수
   port->fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
   if (port->fd == -1)
   {
      perror("Unable to open port");
      return -1;
   }

   // 시리얼 통신 환경을 설정하기 위해 termios 구조체를 선언
   struct termios options;

   memset(&options, 0, sizeof(options));

   // 시리얼 포트 초기화
   tcflush(port->fd, TCIFLUSH); 

   // Terminer Control 모드 설정을 위해서 Get
   tcgetattr(port->fd, &options); 
   cfsetispeed(&options, B9600); // Set baud rate to 9600 (adjust as needed)
   cfsetospeed(&options, B9600);

   options.c_cflag |= CS8;     // 8 data bits -> 문자 크기 마스크
   options.c_cflag &= ~PARENB; // No parity -> PARENB : 출력 시 패리티 생성을 활성화하고 입력
   options.c_cflag &= ~CSTOPB; // One stop bit -> CSTOPB : Stop bit 수 1개
   // options.c_cflag &= ~CSIZE;  // Mask the character size bits
   
   // Serial Port에 새 설정 Set
   // 시리얼 포트에 설정 입력 (TCSANOW : 즉시 속성을 변경시켜라)
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
   // Serial Port로부터 데이터 수신
   // read에 의해서 실제로 읽혀진 문자의 개수를 갖게 됨
   return read(port->fd, buffer, size);
}

ssize_t serial_write(SerialPort *port, char *buffer, size_t size)
{
   // Serial Port으로 데이터 송신
   return write(port->fd, buffer, size);
}

int main(int argc, char *argv[])
{
   int sock;
   char message[BUF_SIZE] = {0, };
   int str_len;

   // sockaddr_in 구조체 변수 선언
   struct sockaddr_in serv_adr;

   if (argc != 3)
   {
      printf("Usage : %s <IP> <port> \n", argv[0]);
      exit(1);
   }

   // ----------- 1. Create socket object ------------------
   // socket() : socket 생성 & socket discriptor
   sock = socket(PF_INET, SOCK_STREAM, 0);
   if (sock == -1)
      error_handling("socket() error");

   // serial port
   SerialPort port;
   if (serial_open(&port, "/dev/ttyACM0") == -1)
   {
      return -1;
   }

   // ------------ 2. Connect to server-- ------------------
   // serv_sock에 bind 로 주소 넣기 위한 밑작업
   memset(&serv_adr, 0, sizeof(serv_adr));

   // Prepare the address
   serv_adr.sin_family = AF_INET;                     // type : IPv4
   serv_adr.sin_addr.s_addr = inet_addr(argv[1]);     // ip주소
   serv_adr.sin_port = htons(atoi(argv[2]));          // 포트번호

   // 대상 서버 소켓에 주소 할당
   // 주소 정보에 서버의 주소와 포트 번호를 지정하고 서버와 연결 시도
   if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
      error_handling("connect() error!");
   else
      puts("Connect........");

   while (1)
   {
      fputs("Input message(Q to quit) : ", stdout);
      fgets(message, BUF_SIZE, stdin);

      if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
         break;
      
      // 클라이언트로 자료를 송신한다
      // write(int fd, const void *buf, size_t nbytes);
      write(sock, message, strlen(message));

      // 클라이언트로부터 전송된 자료 수신한다
      // read(int fd, void *buff, size_t nbytes)
      str_len = read(sock, message, BUF_SIZE - 1);
      message[str_len] = 0;

      printf("Message form server : %s", message);

      // serial port 로 message 전달
      serial_write(&port, message, sizeof(message));      
   }
   
   // 통신 포트를 닫아 사용을 중지
   serial_close(&port);   

   close(sock);   
   return 0;
}

void error_handling(char *message)
{
   fputs(message, stderr);
   fputc('\n', stderr);
   exit(1);
}
