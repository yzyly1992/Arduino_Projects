int foo[] = {2, 6, 7, 9, 3, 12};
int maxIndex = sizeof(foo) / sizeof(foo[0]);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
}

void loop() {
  for (int i= 0; i < maxIndex; i++) {
    Serial.print(foo[i]);
    delay(200);
  }
  // put your main code here, to run repeatedly:

}
