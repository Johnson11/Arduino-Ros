int trigPin = 4;
int echoPin = 2;

void setup() {
  Serial.begin(9600);
}

void loop(){
  long duration;
  float cm;
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(100);
}
float microsecondsToCentimeters(long microseconds){
  return (microseconds*0.034029)/2;
}

