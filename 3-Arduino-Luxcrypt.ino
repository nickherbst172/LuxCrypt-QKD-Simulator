// LuxCrypt Physical Simulator: Alice & Bob Handshake
const int aliceLedPin = 13;   // Alice's Transmitter
const int bobLdrPin = A0;     // Bob's Receiver

void setup() {
  Serial.begin(9600);         // Must match Python's 9600 speed
  pinMode(aliceLedPin, OUTPUT);
  digitalWrite(aliceLedPin, LOW);
}

void loop() {
  // 1. Wait for Python to send a '1' (Quantum Bit detected)
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command == '1') {
      // 2. Alice fires her LED pulse
      digitalWrite(aliceLedPin, HIGH);
      
      // 3. Small delay so the LDR has time to react to the light
      delay(1000); 
      
      // 4. Bob measures the light level
      int lightLevel = analogRead(bobLdrPin);
      
      // 5. Alice turns off the LED
      digitalWrite(aliceLedPin, LOW);
      
      // 6. Send the "Evidence" back to Python to verify the key
      Serial.println(lightLevel);
    }
  }
}