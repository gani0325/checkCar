// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <arpa/inet.h>
// #include <sys/socket.h>

// #include <fcntl.h>
// #include <termios.h>

// #define BUF_SIZE 8
// void error_handling(char *message);

// typedef struct
// {
//     int fd;
// } SerialPort;

// int serial_open(SerialPort *port, const char *device)
// {
//     port->fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
//     if (port->fd == -1)
//     {
//         perror("Unable to open port");
//          printf("Unable to open port");
//         return -1;
//     }

//     struct termios options;
//     tcgetattr(port->fd, &options);
//     cfsetispeed(&options, B9600); // Set baud rate to 9600 (adjust as needed)
//     cfsetospeed(&options, B9600);

//     options.c_cflag |= CS8;     // 8 data bits
//     options.c_cflag &= ~PARENB; // No parity
//     options.c_cflag &= ~CSTOPB; // One stop bit
//     //options.c_cflag &= ~CSIZE;  // Mask the character size bits

//     tcsetattr(port->fd, TCSANOW, &options);

//     return 0;
// }

// void serial_close(SerialPort *port)
// {
//     close(port->fd);
//     port->fd = -1;
// }

// int serial_read(SerialPort *port, char *buffer, size_t size)
// {
//     return read(port->fd, buffer, size);
// }

// ssize_t serial_write(SerialPort *port, char *buffer, size_t size)
// {
//     return write(port->fd, buffer, size);
// }

// int main(int argc, char *argv[])
// {
//    int sock;
//    char message[BUF_SIZE];
//    int str_len;
//    struct sockaddr_in serv_adr;

//    if(argc != 3)
//    {
//       printf("Usage : %s <IP> <port> \n", argv[0]);
//       exit(1);
//    }

//    // ----------- 1. Create socket object ------------------
//    sock = socket(PF_INET, SOCK_STREAM, 0);
//    if(sock == -1)
//       error_handling("socket() error");

//    // serial port
//    SerialPort port;
//    if (serial_open(&port, "/dev/ttyACM0") == -1)
//       {
//         return -1;
//       }

//    // ------------ 2. Connect to server-- ------------------
//    memset(&serv_adr, 0, sizeof(serv_adr));

//    // Prepare the address
//    serv_adr.sin_family = AF_INET;
//    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
//    serv_adr.sin_port = htons(atoi(argv[2]));

//    if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
//       error_handling("connect() error!");
//   else
//       puts("Connect........");

//    while(1)
//    {
//       fputs("Input message(Q to quit) : ", stdout);
//       fgets(message, BUF_SIZE, stdin);

//       if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
//          break;

//       write(sock, message, strlen(message));
//       str_len = read(sock, message, BUF_SIZE - 1);
//       message[str_len] = 0;
//       printf("Message form server : %s", message);

//       serial_write(&port, message, sizeof(message));

//    }

//    close(sock);
//    return 0;
// }

// void error_handling(char *message)
// {
//    fputs(message, stderr);
//    fputc('\n', stderr);
//    exit(1);
// }

#include <stdio.h>

#include <fcntl.h>

#include <unistd.h>

#include <termios.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <sys/signal.h>

#define SPEED B19200 // SPEED

#define SPORT "/dev/ttyS1" // S PORT S의 의미는?

volatile int iBreak = 0; // volatile 컴파일시 눈에 보이는 문장만을 상대로 함부로 최적화 시키지 말아야 함, 최적화 하지 않는다.

void Handle_Serial_Sig(int);

int main()
{

   // 장치 Description

   int iDev = 0;

   // Return Value

   int iRet = 0;

   // 수신용 버퍼

   char cBuff[255];

   // 기존 Serial Port 상태 정보

   struct termios ST_OldState;

   // 새로운 Serial Port 상태 정보

   struct termios ST_NewState;

   // Signal Action 설정 (Software Interrupt 방식)

   struct sigaction ST_SigAct;

   // Serial Port Open

   iDev = open(SPORT, O_RDWR | O_NOCTTY | O_NONBLOCK);

   // 예시1 : O_NONBLOCK 옵션이 없는경우
   // 데이터를 read하면 데이터가 들어올때까지 프로그램이 블락킹 상태가 됩니다.
   // write의 경우에는 상대방이 read()로 들어갈 때까지 기다립니다.

   // 예시2 : O_NONBLOCK 옵션이 있는경우
   // 데이터가 있든 없든 기다리지 않고 나옵니다. 읽을 데이터가 있으면 읽어온 데이터를 buf에 기록하고, res에 읽어온 바이트 수를 리턴하죠. 없다면 res로 -1을 리턴합니다.
   // write의 경우에도 read와 같은 방식으로 동작합니다.

   if (iDev < 0)
   {

      perror(SPORT);

      exit(-100);
   }

   // Serial Port 설정 전 Signal Handler 등록

   // Interrupt가 발생 할때마다 Handle_Serial_Sig 함수 호출

   bzero(&ST_SigAct, sizeof(ST_SigAct));

   ST_SigAct.sa_handler = Handle_Serial_Sig;

   sigaction(SIGIO, &ST_SigAct, NULL);

   // SIGIO Signal 수신 설정

   // GETID() : 현재 실행중인 프로그램의 번호

   fcntl(iDev, F_SETOWN, getpid());

   // File Description 비동기 설정

   fcntl(iDev, F_SETFL, FASYNC);

   // 현재 Serial Port 상태 저장

   tcgetattr(iDev, &ST_OldState);

   // 구조체 초기화

   bzero(&ST_NewState, sizeof(ST_NewState));

   // SPEED    : 전송속도, cfsetispeed(), cfsetospeed()로도 설정가능

   // CS8      : 8N1 (8Bit, No Parity, 1 Stop Bit)

   // CLOCAL   : Local Connection. 제어를 하지 않음

   // CREAD    : 문자 수신 가능

   ST_NewState.c_cflag = SPEED | CRTSCTS | CS8 | CLOCAL | CREAD;

   // IGNPAR    : Parity Error가 있는 문자 Byte 무시

   // ICRNL    : CR 문자를 NL 문자로 변환 처리

   ST_NewState.c_iflag = IGNPAR | ICRNL;

   // 수신된 데이터 그대로 출력

   ST_OldState.c_oflag = 0;

   // Canonical 통신 기법 사용

   ST_NewState.c_lflag = ICANON;

   // Read시 Return되기 위한 최소 문자 개수 지정

   ST_NewState.c_cc[VMIN] = 1;

   ST_NewState.c_cc[VTIME] = 0;

   // Serial Port 수신 Queue 초기화

   tcflush(iDev, TCIFLUSH);

   // Serial Port에 새 속성 적용

   tcsetattr(iDev, TCSANOW, &ST_NewState);

   while (1)
   {

      if (iBreak == 1)
      {

         // Serial Port로 데이터 수신

         iRet = read(iDev, cBuff, 255);

         cBuff[iRet] = 0;

         printf("[%s] : [%d]\n", cBuff, iRet);

         break;
      }

      else
      {

         sleep(2);
      }

      printf("Go Sleep\n");
   }

   tcsetattr(iDev, TCSANOW, &ST_OldState);

   close(iDev);

   return 0;
}

void Handle_Serial_Sig(int Arg)
{

   printf("Receive SIGIO Signal\n");

   iBreak = 1;
}