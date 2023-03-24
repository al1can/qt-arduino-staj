/*
int incomingByte;
String message;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  //pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  if (Serial.available() > 0) {
    message = Serial.readString();
    Serial.print(message);

    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);      

    
  } else {
    message = "";
  }

}
*/

int inChar;
int counter = 0;
int n = 0;
String inString;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  //while (!Serial)
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  if (Serial.available() > 0) {
    
    inChar = Serial.read();
    
    if (isDigit(inChar)) {
      inString += (char)inChar;
    }

    if (inChar == '\n') {
      //digitalWrite(LED_BUILTIN, HIGH);
      n = inString.toInt();
      Serial.print("Value: ");
      Serial.println(inString.toInt());
      inString = "";

      //n = 10;
      
      for (counter = 0; counter < n; counter++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        delay(1000);
      }
    }

  }

}
