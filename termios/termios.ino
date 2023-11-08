int incomingByte = 0;    // for incoming serial data
int16_t timed_delay=0;
int16_t timed_count=0;
void setup() {
    Serial.begin(9600);    // opens serial port, sets data rate to 9600 bps
}

void loop() {
  
  // send data only when you receive data:
  if (Serial.available() > 0) {
  
    // read the incoming byte:
    incomingByte = Serial.read();
  
    // say what you got:
    Serial.print((char)incomingByte);
  }
  timed_delay++;
  if(timed_delay==INT16_MAX){
    if(timed_count==10){
      Serial.print("time\r\n");
      timed_count=0;
    }
    timed_count++;
    timed_delay=0;
  }
  
}