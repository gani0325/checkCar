// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>

// int main() {
// 	int fileSize;
	
// 	{
// 		FILE *file;
// 		const char *filename = "/tmp/test.txt";
		
// 		// 파일 열기
// 		file = fopen(filename, "rb");
// 		if (file == NULL) {
// 			printf("파일 열기 오류");
// 			return 1;
// 		}
		
// 		// 파일 포인터를 파일 끝으로 이동
// 		if (fseek(file, 0, SEEK_END) != 0) {
// 			printf("파일 포인터 이동 오류");
// 			fclose(file);
// 			return 1;
// 		}
		
// 		// 파일의 현재 위치를 구해서 파일 크기를 얻기
// 		long file_size = ftell(file);
// 		if (file_size == -1) {
// 			printf("파일 크기 구하기 오류");
// 			fclose(file);
// 			return 1;
// 		}
		
// 		printf("파일 크기: %ld 바이트\n", file_size);
		
// 		// 파일 닫기
// 		fclose(file);
// 	}
	
// 	// 소켓 생성
// 	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
// 	if (clientSocket == -1) {
// 		printf("소켓 생성 실패");
// 		return 1;
// 	}

// 	// 서버 정보 설정
// 	struct sockaddr_in serverAddress;
// 	serverAddress.sin_family = AF_INET;
// 	serverAddress.sin_port = htons(9999);
// 	serverAddress.sin_addr.s_addr = inet_addr("localhost");

// 	// 서버에 연결
// 	if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
// 		printf("연결 실패");
// 		return 1;
// 	} else {
// 		printf("연결 성공\n");
// 	}

// 	// 파일 크기 메시지 전송
// 	if (send(clientSocket, &fileSize, sizeof(fileSize), 0) == -1) {
// 		printf("파일 크기 전송 실패\n");
// 		return 1;
// 	}
// 	close(clientSocket);
// 	return 0;
// }

// echo_client.c
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
