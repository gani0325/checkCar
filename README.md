# 🚗 checkCar 🚗
![16.png](/image/555.png)
- 앞차의 상황을 알려줘~ 내 붕붕이는 잘있니~
- 앞차가 갑자기 멈춘다면 뒷차는 무슨 일이 일어났는지 모른다!
- So, 앞차가 뒷차에게 "앞에 사고가 났어", "동물 출몰!", "내 차가 고장난듯" 등 메시지를 전달하고자 한다!
- 그밖에도, 내 차가 주차되어있거나 멈춰있을 때 앱(tcp)으로 "나 잠시 주차중", "급 화장실!" 등 메시지를 전달한다!
- 우리의 최종 목표는
  - 1. 조이스틱 버튼 4개로 🔊차 사고, 🦊동물 출몰, 👧 차안에 아기 있음, ⚒️차 고장의 메시지롤 LCD 판으로 보낸다
    2. TCP 통신📤 을 통해 멀리서도 보내고 싶은 메시지를 LCD 판으로 보낸다
    3. 조이스틱 회전기🕹️로 운전대라 생각하고 전진🔵, 우/좌회전 + 전진🔵🟢, 후진🔴, 우/좌회전 + 후진🔴🟢 할 때마다 해당 LED 를 깜빡인다

### 🛎️ 2조의 규칙
**1️⃣ commit message** 

```c
➕[Feat] : 기능 추가
🚀[Chore] : 실행 파일 및 수정 시 
🚧[Refactor] : 코드 수정 (리팩토링)
📃[Memo] : 주석 수정
🚨[Alert] : 기능 오류 시
⚙️[Setting] : 초기 및 환경 설정
📤[Move] : 파일 옮기기
✂️[Remove] : 파일 삭제
```

**2️⃣ 깃허브 push 시 🚨 알리기 (충돌 발생!! Pull 하고 수정하세요!!)**

**3️⃣ 1일 1 issue 작성**

**4️⃣ dev branch 에 1차 Merge, main branch 에 최종 Merge**

# 🚗 프로젝트 🚗
### 👨‍💻 1. 프로젝트 간트 차트
- 주제 정하기 (November 3, 2023 ~ November 5, 2023)
- 로직 구상하기 (November 6, 2023)
- 통신 구현 & LCD에 출력 (November 6, 2023 ~ November 9, 2023)
- 아두이노로 값 받아오기 (November 7, 2023 ~ November 9, 2023)
- checkCar 발표 하기 (November 10, 2023)

### 👨‍💻 2. 작업순서
- 객체지향 만들기
    - 객체 joystick과 button 합성관계를 이용해 pin과 pinMode부분 캡슐화, 아두이노와 C와 C++ 통합구현
```
//arduino.ino
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "joystick.h"
#include "button.h"
#include "xystick.h"
#include "led.h"
#include "lcd.h"

// joystick 객체 생성
joystick_t *joystick;   

void setup()
{
  Serial.begin(9600);    // 시리얼 통신을 시작하며, 통신속도는 9600
  //joystick 생성
  joystick = (joystick_t *)joystick_new(); // joystick 객체 메모리 할당
  joystick_ctor(joystick);                 // joystick 객체 시그니처로 생성자 함수안에 pin과 pinMode할당이 있다.
}

void loop()
{
  joystick_control(joystick);
  joystick_lcd_print(joystick);
}
```

- 회의록
- Tasks Board 칸반보드

### 👨‍💻 3. 다이어그램
```jsx
			arduino_main() ----Serial--- client_main() -----TCP-----server_main()
                              |                            |                         |
                              |                            |                         |
                        button_click()                     |                         |
                              |                            |                         |
                              V                            |                         |  
                          LCDprint() <-------------- Serial_write() <---------->  accept()   
                               
```
- 231103
![16.png](/image/ㅂ.png)
![16.png](/image/ㅈ.png)

- 231106
![16.png](/image/q.png)

- 231107
![16.png](/image/w.png)

- 231110
![16.png](/image/6666.png)


### 👨‍💻 4. 소스코드 분석

- **network**
    
    **🚗 server.c**
    
    ```c
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
    ```
    
    **🚗 client.c**
    
    ```c
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
    ```
    
- **arduino**
```arduino
//joystick.c
#include <stdint.h> //int x비트 같은 자료형을 쓰기위해서
#include <Arduino.h>
#include "joystick.h"
#include "button.h"
#include "xystick.h"
#include "led.h"
#include "lcd.h"

typedef struct joystick_t
{
	struct button_t *but[5]; // 버튼 4개의 주소 배열에 할당. 마지막index는 빈 return 값을 받기위함.
	struct xystick_t *xystick;
} joystick_t;

char selected_button;
uint8_t pin_status[4];
int *joystick_XYaxis_value[2];
char data[COLUMN + 1];

void *joystick_new()
{
	return (void *)malloc(sizeof(joystick_t));
}

void joystick_ctor(joystick_t *joystick_obj) // joystick 객체를 시그니처로 받음 받은 객체는 모두 obj로 명칭
{
	for (uint8_t pin = 2, index = 0; pin < 6; pin++, index++) // 배열을 하나씩 반복하며 pin과 pinMode 초기화
	{
		joystick_obj->but[index] = button_4new(); // 배열 하나에 버튼 1개에 대한 하나의 button객체 메모리할당. button객체 생성
		if (index == 0)
		{
			joystick_obj->but[index]->button_name = 'A';
		}
		else if (index == 1)
		{
			joystick_obj->but[index]->button_name = 'B';
		}
		else if (index == 2)
		{
			joystick_obj->but[index]->button_name = 'C';
		}
		else if (index == 3)
		{
			joystick_obj->but[index]->button_name = 'D';
		}
		button_4ctor(joystick_obj->but[index], pin, INPUT_PULLUP); // button객체에 pin과 pinMode할당
	}
	joystick_obj->xystick = xystick_new();
	lcd_init();
}

void joystick_lcd_print(joystick_t* joystick_obj)
{
	char clicked_button = 'E'; // 초기화
	clicked_button = joystick_digitalRead(joystick_obj);
	if (clicked_button == 'A')
	{ // if문을 이용하여 각 버튼이 눌리면 알파벳이 시리얼모니터에 출력되도록 설정
		char data[COLUMN + 1] = "front car!";
		lcd_print(data);
	}
	if (clicked_button == 'B')
	{
		char data[COLUMN + 1] = "front animal!";
		lcd_print(data);
	}
	if (clicked_button == 'C')
	{
		char data[COLUMN + 1] = "baby in car";
		lcd_print(data);
	}
	if (clicked_button == 'D')
	{
		char data[COLUMN + 1] = "broken car";
		lcd_print(data);
	}
};

char joystick_digitalRead(joystick_t *joystick_obj)
{
	for (int index = 0; index < 4; index++)
	{
		pin_status[index] = clicked_button(joystick_obj->but[index]);
	}
	if (pin_status[0] == LOW)
	{
		return joystick_obj->but[0]->button_name;
	}
	else if (pin_status[1] == LOW)
	{
		return joystick_obj->but[1]->button_name;
	}
	else if (pin_status[2] == LOW)
	{
		return joystick_obj->but[2]->button_name;
	}
	else if (pin_status[3] == LOW)
	{
		return joystick_obj->but[3]->button_name;
	}
	return 'E';
}

void joystick_control(joystick_t *joystick_obj)
{
	joystick_XYaxis_value[X_PIN_INDEX] = xstick_analogRead(joystick_obj->xystick);
	joystick_XYaxis_value[Y_PIN_INDEX] = ystick_analogRead(joystick_obj->xystick);

	if (joystick_XYaxis_value[X_PIN_INDEX] == 493)
	{
		if (joystick_XYaxis_value[Y_PIN_INDEX] > 515)
		{
			joystick_XYstick_forward(joystick_obj->xystick);
		}
	}
	if (joystick_XYaxis_value[X_PIN_INDEX] == 493)
	{
		if (joystick_XYaxis_value[Y_PIN_INDEX] < 515)
		{
			joystick_XYstick_back(joystick_obj->xystick);
		}
	}
	if (joystick_XYaxis_value[X_PIN_INDEX] < 493)
	{
		joystick_XYstick_left(joystick_obj->xystick);
	}
	if (joystick_XYaxis_value[X_PIN_INDEX] > 493)
	{
		joystick_XYstick_right(joystick_obj->xystick);
	}
	if (joystick_XYaxis_value[X_PIN_INDEX] == 493)
	{
		if (joystick_XYaxis_value[Y_PIN_INDEX] == 515)
		{
			joystick_XYstick_fixed(joystick_obj->xystick);
		}
	}
}
```

### 👨‍💻 5. 프로젝트 성과 결과
- **🚗 LCD 판에 뒷차에 상황 알리기**
    1. 조이스틱 버튼 4개로 지정된 상황 알리기
        - 조이스틱 버튼
            - A버튼 : front car!
            ![16.png](/image/car.jpg)
            - B버튼 : front animal!
            ![16.png](/image/animal.jpg)
            - C버튼 : baby in car
            ![16.png](/image/baby.jpg)
            - D버튼 : broken car
            ![16.png](/image/broken.jpg)
    2. TCP/IP 통신으로 운전뿐만 아니라 정차중에도 메시지 전달하기
    ![16.png](/image/T.jpg)

- **🚗 조이스틱 (운전대) 으로 LED 제어하기**
    1. 전진, 좌/우회전, 후진 할 때마다 LED 제어
        - 전진 : 파랑
        ![16.png](/image/전진.png)
        - 좌/전진 : 파랑/초록
        ![16.png](/image/좌회전.png)
        - 우/전진 : 파랑/초록
        ![16.png](/image/우회전.png)
        - 후진 : 빨강
        ![16.png](/image/후진.png)
        - 좌/후진 : 빨강/초록
        ![16.png](/image/좌후진.png)
        - 우/후진 : 빨강/초록
        ![16.png](/image/우후진.png)


- 객체 지향 코드로 바꿀 시 메모리 용량 비교하기

 ![16.png](/image/아두이노저장용량1.png)
 절차지향 코드로 구현 

 ![16.png](/image/아두이노저장용량2.png)
 객체지향 코드로 구현

 flush 메모리의 용량이 줄어들고 SRam용량은 늘어났다.