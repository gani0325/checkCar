// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <arpa/inet.h>

// int main() {
// 	int server_fd, client_fd;
// 	struct sockaddr_in server_addr, client_addr;
// 	socklen_t addr_len = sizeof(client_addr);
	
// 	// 서버 소켓 생성
// 	server_fd = socket(AF_INET, SOCK_STREAM, 0);
// 	if (server_fd == -1) {
// 		printf("소켓 생성 오류\n");
// 		exit(1);
// 	}
	
// 	// 서버 주소 설정
// 	memset(&server_addr, 0, sizeof(server_addr));
// 	server_addr.sin_family = AF_INET;
// 	server_addr.sin_addr.s_addr = INADDR_ANY;
// 	server_addr.sin_port = htons(9999);
	
// 	// 서버에 주소 할당
// 	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
// 		printf("주소 할당 오류\n");
// 		close(server_fd);
// 		exit(1);
// 	}
	
// 	// 클라이언트의 연결 대기
// 	if (listen(server_fd, 5) == -1) {
// 		printf("연결 대기 오류\n");
// 		close(server_fd);
// 		exit(1);
// 	}
	
// 	printf("서버가 대기 중...\n");
	
// 	// 클라이언트와 연결
// 	client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
// 	if (client_fd == -1) {
// 		printf("연결 오류\n");
// 		close(server_fd);
// 		exit(1);
// 	}
	
// 	// 파일 크기 읽기
// 	uint32_t file_size;
// 	if (read(client_fd, &file_size, sizeof(file_size)) != sizeof(file_size)) {
// 		printf("파일 크기 읽기 오류\n");
// 		close(client_fd);
// 		close(server_fd);
// 		exit(1);
// 	}
	
// 	printf("수신된 파일 크기: %u 바이트\n", file_size);
	
// 	// 버퍼 동적 할당
// 	void *buffer = malloc(file_size);
// 	if (buffer == NULL) {
// 		printf("메모리 할당 오류\n");
// 		close(client_fd);
// 		close(server_fd);
// 		exit(1);
// 	}
	
// 	printf("생성된 버퍼 주소 : %p\n", buffer);
    
// 	// 연결 종료
// 	close(client_fd);
// 	close(server_fd);
	
// 	// 할당된 메모리 해제
// 	free(buffer);
	
// 	return 0;
// }

// echo.server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
   int serv_sock, clnt_sock;
   char message[BUF_SIZE];
   int str_len, i;

   struct sockaddr_in serv_adr, clnt_adr;
   socklen_t clnt_adr_sz;

   if(argc != 2)
   {
      printf("Usage : %s <port>\n", argv[0]);
      exit(1);
   }

  // ----------- 1. Create socket object ------------------
   serv_sock = socket(PF_INET, SOCK_STREAM, 0);
   if(serv_sock == -1)
      error_handling("socket() error");


   // ----------- 2. Bind the socket file ------------------
   memset(&serv_adr, 0, sizeof(serv_adr));

   // Prepare the address
   serv_adr.sin_family = AF_INET;
   serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
   serv_adr.sin_port = htons(atoi(argv[1]));

   if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
      error_handling("bind() error");

   // ----------- 3. Prepare backlog ------------------
   if(listen(serv_sock, 5) == -1)
      error_handling("listen() error");

   clnt_adr_sz = sizeof(clnt_adr);

   for(i = 0; i < 5; i++)
   {
      // ----------- 4. Start accepting clients ---------
      clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
      if(clnt_sock == -1)
         error_handling("accept() error");
      else
         printf("Connected client %d \n", i + 1);
      while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)
         write(clnt_sock, message, str_len);

      close(clnt_sock);
   }
   close(serv_sock);
   return 0;
}

void error_handling(char *message)
{
   fputs(message, stderr);
   fputc('\n', stderr);
   exit(1);
}