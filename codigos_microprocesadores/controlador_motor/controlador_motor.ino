#define e1 16  // pwm
#define i1 5  // digital
#define i2 4  // digital
const int pot=0;
int voltaje_pot;
void setup() {
  // put your setup code here, to run once:
  pinMode(e1, OUTPUT);
  pinMode(i1, OUTPUT);
  pinMode(i2, OUTPUT);
  Serial.begin(9600);
}

void loop(){

    voltaje_pot=digitalRead(pot);
    Serial.println(voltaje_pot);
    if(voltaje_pot>0){
      digitalWrite(e1, 255); // Activamos Motor1
      digitalWrite(i1, LOW); // Arrancamos
      digitalWrite(i2, HIGH);
      delay(4000);
    }
}
