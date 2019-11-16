int incomingByte = 0; // for incoming serial data

int w = 4;
int a = 5;
int s = 6;
int d = 7;

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    Serial.print("Recibi el valor DEC ");
    Serial.print(incomingByte + " tecla ");

    switch (incomingByte){
      case 1:
        Serial.println("w y el movimiento ADELANTE.");

        digitalWrite(w, HIGH);
        delay(1000);
        digitalWrite(w, LOW);
        
        break;
      case 2:
        Serial.println("a y el movimiento IZQUIERDA.");
        break;
      case 3:
        Serial.println("s y el movimiento ATRAS.");

        digitalWrite(w, HIGH);
        delay(1000);
        digitalWrite(w, LOW);
        
        break;
      case 4:
        Serial.println("d y el movimiento DERECHA.");
        break;
      case 5:
        Serial.println("Comunicacion serial terminada.");
        break;
      default:
        break;
    }
  }
}
