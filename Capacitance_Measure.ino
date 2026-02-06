//this is a prototype code, complete code will be updated

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
float t = 0;
double st = 0;
float Vx = 0;
void setup() {
Serial.begin(9600);
}

void discharge(){
  Serial.println("Discharging");
  //pinMode(D9, OUTPUT);          //470K
  //pinMode(D10, OUTPUT);         //680
  pinMode(D8, OUTPUT);            //680
  pinMode(D11, OUTPUT);           //470K

  //digitalWrite(D9, LOW);
  //digitalWrite(D10, HIGH);
  digitalWrite(D8, HIGH);
  digitalWrite(D11, LOW);
  delay(5000);
}

void charge(){
  Serial.println("charging");
  //pinMode(D9, OUTPUT);
  //pinMode(D10, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(D11, OUTPUT);

  //digitalWrite(D9, HIGH);
  //digitalWrite(D10, LOW);
  digitalWrite(D8, HIGH);
  digitalWrite(D11, LOW);
  
  st = millis();
  Serial.println(analogRead(TP1));
  while(analogRead(TP1) <= 646){
    ADC_1 = analogRead(TP1);
    Vx = ADC_1 * 0.004882;
    Serial.println(Vx);

  }
  t = millis() - st;
  //Vx = ADC_1 * 0.004882;

}

void loop(){
  discharge();
  charge();
  Cx = (t/1000)/(R1);
  Serial.println("Capacitance: "+ String(Cx, 12));
  Serial.println("Time: "+String(t));
  Serial.println("-------------------------------------------------");

}
