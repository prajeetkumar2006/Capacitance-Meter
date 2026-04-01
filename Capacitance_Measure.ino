int D8 = 8;
int D9 = 9;
int D10 = 10;
int D11 = 11;

int TP1 = A0;
int TP2 = A1;
int ADC_1 = 0;
int ADC_2 = 0;

double R1 = 680+29;
double R2 = 470000+10.9;
double R3 = 680+24.8;
double R4 = 470000+5.46;

double Cx = 0;
double t = 0;
double st = 0;
float Vx = 0;

void setup() {
  Serial.begin(9600);
  pinMode(TP1, INPUT);
  pinMode(TP2, INPUT);
}


void loop() {
  discharge();
  delay(500); 
  charge();

  // FIX: Added parentheses around (R1 + R3)
  // Without parentheses, it divides t by R1 then adds R3 to the result.
  Cx = ((double)t / 1000.0) / (R2 + R3); 
  
  Serial.print("Capacitance : ");
  Serial.println(Cx * 1000000, 12);
  Serial.print("Time (ms): "); // Note: millis() gives ms, not us
  Serial.println(t, 3);
  Serial.println("--------------------------------------");
  
  delay(3000);
}

void discharge() {
  Serial.println("Discharging");
  pinMode(D8, OUTPUT);
  pinMode(D9, OUTPUT);
  pinMode(D10, OUTPUT);
  pinMode(D11, OUTPUT);

  digitalWrite(D8, LOW);
  digitalWrite(D9, LOW);
  digitalWrite(D10, LOW);
  digitalWrite(D11, LOW);

  // FIX: Using > 2 instead of > 0 to prevent code from hanging on ADC noise
  while (analogRead(TP1) > 2); 

  Serial.println("Discharging");

  pinMode(D8, INPUT);
  pinMode(D9, INPUT);
  pinMode(D10, INPUT);
  pinMode(D11, INPUT);
  delay(100);
}

void charge() {
  Serial.println("charging");
  
  pinMode(D9, OUTPUT);
  pinMode(D10, OUTPUT);
  //pinMode(D8, OUTPUT);
  //pinMode(D11, OUTPUT);

  digitalWrite(D9, HIGH);
  digitalWrite(D10, LOW);
  //digitalWrite(D8, HIGH);
  //digitalWrite(D11, LOW);

  st = millis();
  
  //Serial.println(analogRead(TP1));
  while (analogRead(TP1) < 648) { 
    ADC_1 = analogRead(TP1);
    Vx = ADC_1 * 0.004882;
    Serial.println(Vx);
  }
  
  t = millis() - st;
  
  delay(100);
  //Serial.println((float)t);
  //Vx = ADC_1 * 0.004882;
}
