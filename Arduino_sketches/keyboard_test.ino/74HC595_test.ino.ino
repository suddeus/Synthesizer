#define SER 12
#define SRCLK 13
#define SRCLR 1
#define RCLK 10
#define OE 11

void SRClear() {
  digitalWrite(SRCLR, LOW);
  delay(1);
  digitalWrite(SRCLR, HIGH);
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
