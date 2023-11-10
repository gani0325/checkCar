#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 16

void error_handling(char *message);

int main(int argc, char *argv[])
{
   // 서버, 클라이언트 소켓 파일디스크립터 변수 선언
   int serv_sock, clnt_sock;
   char message[BUF_SIZE];
   int str_len, i;

   // sockaddr_in 구조체 변수 선언
   struct sockaddr_in serv_adr, clnt_adr;
   socklen_t clnt_adr_sz;

   if(argc != 2)
   {
      printf("Usage : %s <port>\n", argv[0]);
      exit(1);
   }


   // ----------- 1. Create socket object ------------------
   // socket() : socket 생성 & socket discriptor
   serv_sock = socket(PF_INET, SOCK_STREAM, 0);
   if(serv_sock == -1)
      error_handling("socket() error");


   // ----------- 2. Bind the socket file ------------------
   // serv_sock에 bind 로 주소 넣기 위한 밑작업
   memset(&serv_adr, 0, sizeof(serv_adr));

   // Prepare the address
   serv_adr.sin_family = AF_INET;                     // type : IPv4
   serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);      // ip주소
   serv_adr.sin_port = htons(atoi(argv[1]));          // 포트번호

   // bind()로 서버 소켓에 주소정보 할당
   if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
      error_handling("bind() error");

   // ----------- 3. Prepare backlog ------------------

   // listen()으로 서버소켓으로 오는 클라이언트 요청 대기
   if(listen(serv_sock, 5) == -1)
      error_handling("listen() error");

   clnt_adr_sz = sizeof(clnt_adr);

   for(i = 0; i < 5; i++)
   {
      printf("Listen....\n");
      
      // ----------- 4. Start accepting clients ---------

      // 클라이언트 접속 요청 대기 및 수락, 클라이언트와의 통신을 위한 새 socket 생성
      clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
      if(clnt_sock == -1)
         error_handling("accept() error");
      else
         printf("Connected client %d \n", i + 1);

      // 클라이언트로부터 전송된 자료 수신
      // read(int fd, void *buff, size_t nbytes)
      while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)
         // 클라이언트로 자료 송신
         // write(int fd, const void *buf, size_t nbytes);
         write(clnt_sock, message, str_len);
      
      // 통신을 완료하면 socket 을 소멸
      close(clnt_sock);
   }

   // 통신을 완료하면 socket 을 소멸
   close(serv_sock);
   return 0;
}

void error_handling(char *message)
{
   fputs(message, stderr);
   fputc('\n', stderr);
   exit(1);
}