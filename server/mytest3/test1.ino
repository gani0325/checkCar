// test1.ino

void printCountTest1(String data) {
  lcd.setCursor(0, 0);    // 1번째, 1라인
  lcd.print(data);
  delay(1500);
  
  lcd.clear();            // 글자를 모두 지워라
}