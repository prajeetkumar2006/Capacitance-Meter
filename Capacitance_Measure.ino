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
float Va = 0;
float Vb = 0;

void setup() {
  Serial.begin(9600);
  pinMode(TP1, INPUT);
  pinMode(TP2, INPUT);
}

void loop() {
  discharge();
  delay(500); 

  // Try the small capacitor measurement first
  if (charge_1_with_timeout()) {
    // If charge_1 finished within 500ms, calculate using small cap formula
    Cx = ((double)t / 1000.0) / (R2 + R3); 
    Serial.print("Range: Small | ");
  } else {
    // If it timed out, it's a big capacitor. Discharge and use charge_2
    discharge();
    delay(500);
    charge_2();
    // Your big value formula
    Cx = (double(t / 1000.0)) / ((R1 + R3) * (log((5.0 - (Va * 0.004882)) / (5.0 - (Vb * 0.004882)))));
    Serial.print("Range: Large | ");
  }

  Serial.print("Capacitance : ");
  Serial.println(Cx * 1000000, 12);
  Serial.print("Time (ms): "); 
  Serial.println(t, 3);
  Serial.println("--------------------------------------");
  
  delay(3000);
}

void discharge() {
  Serial.println("Discharging...");
  pinMode(D8, OUTPUT);
  pinMode(D9, OUTPUT);
  pinMode(D10, OUTPUT);
  pinMode(D11, OUTPUT);

  digitalWrite(D8, LOW);
  digitalWrite(D9, LOW);
  digitalWrite(D10, LOW);
  digitalWrite(D11, LOW);

  while (analogRead(TP1) > 2); 

  pinMode(D8, INPUT);
  pinMode(D9, INPUT);
  pinMode(D10, INPUT);
  pinMode(D11, INPUT);
  delay(100);
}

// Modified charge_1 to detect if the capacitor is too big
bool charge_1_with_timeout() {
  Serial.println("Testing for small capacitor...");
  
  pinMode(D9, OUTPUT);
  pinMode(D10, OUTPUT);

  digitalWrite(D9, HIGH);
  digitalWrite(D10, LOW);

  st = millis();
  
  while (analogRead(TP1) < 648) { 
    t = millis() - st;
    if (t > 500) { // If it takes longer than 0.5s, it's not a "small" capacitor
       return false; 
    }
    
    ADC_1 = analogRead(TP1);
    Vx = ADC_1 * 0.004882;
    // Serial.println(Vx); 
  }

  return true; // Successfully measured a small capacitor
}

void charge_2() { // for capacitor values more than 10uF
  Serial.println("Charging big capacitor...");
  
  pinMode(D10, OUTPUT);
  pinMode(D8, OUTPUT);

  digitalWrite(D10, LOW);
  digitalWrite(D8, HIGH);
  
  Va = analogRead(TP1);
  st = millis();
  
  while (analogRead(TP1) < 716) { 
    ADC_1 = analogRead(TP1);
    Vx = ADC_1 * 0.004882;
  }
  Vb = analogRead(TP1);
  
  t = millis() - st;
  delay(100);
}
