int incomingByte = 0; // for incoming serial data

int w = 6; // for forward movement
int a = 4; // for left movement
int s = 7; // for reverse movement
int d = 5; // for right movement

int i = 0;

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  
  Serial.println("Ready for serial communication."); // Prints in the Serial Monitor that is ready to receive commands

}

void loop() {

  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received the DEC value: ");
    Serial.print(incomingByte + " key ");

    switch (incomingByte){
      case 1: // for forward movement
        Serial.println("w and movement FORWARD.");

        digitalWrite(w, HIGH); // 0.8s forward
        delay(800);
        digitalWrite(w, LOW);
        digitalWrite(s, HIGH); // .02s braking
        delay(200);
        digitalWrite(s, LOW);
        
        break;
      case 2:
        Serial.println("a and movement LEFT.");

        digitalWrite(a, HIGH); // 0.62s left turn and forward
        digitalWrite(w, HIGH);
        delay(620);
        digitalWrite(a, LOW);
        digitalWrite(w, LOW);
        digitalWrite(s, HIGH); // 0.62s backwards to starting position
        delay(620);
        digitalWrite(s, LOW);
        
        break;
      case 3:
        Serial.println("s and movement REVERSE.");

        digitalWrite(s, HIGH); // 0.8s backwards
        delay(800);
        digitalWrite(s, LOW);
        digitalWrite(w, HIGH); // 0.2s braking
        delay(200);
        digitalWrite(w, LOW);
        
        break;
      case 4:
        Serial.println("d and movement RIGHT.");

        for(i = 0; i < 3; i++){ // Right turn doesn't work, so rotate car 3 times to the left to make it right
          
          digitalWrite(a, HIGH); // 0.62s left and forward
          digitalWrite(w, HIGH);
          delay(620);
          digitalWrite(a, LOW);
          digitalWrite(w, LOW);
          digitalWrite(s, HIGH); // 0.62s backwards to starting position
          delay(620);
          digitalWrite(s, LOW);
          
          delay(1500); // delay for repetition
        }

        digitalWrite(w, HIGH);
        delay(250);
        digitalWrite(w, LOW);
        
        break;
      case 5:
        Serial.println("SERIAL COMMUNICATION ENDED."); // Ending serial communication
        break;
      default:
        break;
    }

    delay(1000); // Delay between instructions
    
  }
}
