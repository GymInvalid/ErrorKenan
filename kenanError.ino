int NUM_SENSORS = 4;
int LeftAn = 11;
int LeftDig = 9;
int RightAn = 10;
int RightDig = 13;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
}

float Error() {
  int d[NUM_SENSORS] = {analogRead (0), analogRead (1), analogRead (2), analogRead (3)};
  const float w[NUM_SENSORS] = {-2, -1, 1, 2};

  float ch = 0;
  for (int i = 0; i < NUM_SENSORS; i++) {
    ch += d[i] * w[i];
  }

  float zn = 0;
  for (int i = 0; i < NUM_SENSORS; i++) {
    zn += d[i];
  }

  float error = ch / zn;

  return error;
}

int Calc(int speedL, int speedR) {
  //int k = Error() * 30; //Ехал без колебаний, медленно, но сошел с линии, ну;но повысить коэффинцент
  int k = Error() * 100; //

  digitalWrite(LeftDig, HIGH);
  digitalWrite(RightDig, HIGH);

  analogWrite(LeftAn, speedL + k);
  analogWrite(RightAn, speedR - k);
}

void loop() {
  Calc(100, 100);

  Serial.println(Error());
}
