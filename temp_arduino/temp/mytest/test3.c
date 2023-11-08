// test3.c
void printCountTest3(int count) {
  printCountTest4ByTest3(300);
}

int flagCommand() {
   CppflagCommand();
}

int LCDmessage(int num) {
   CppLCDmessage(num);
}

int main() {
      // Command 받은 flag = 1
      flagCommand();

      LCDmessage(1004);
}