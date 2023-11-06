// test1.ino

void printCountTest1(int num) {
  // lcd.setCursor(0, 0);    // 1번째, 1라인 (열, 행)
  // lcd.print(num);
  // lcd.clear();            // 글자를 모두 지워라

  Serial.print(num);
}