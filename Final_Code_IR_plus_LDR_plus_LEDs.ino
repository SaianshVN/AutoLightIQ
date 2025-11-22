  // Smart Street Light System - Final Logic
  // NIGHT: Lights ON (IRs only log, don't control lights)
  // DAY:   Lights OFF (IRs control lights ON/OFF)

  // Sensor pins
  const int IR_START = D1;     // Start IR sensor
  const int IR_END = D2;       // End IR sensor
  const int LDR_PIN = D3;      // LDR module

  // LED pins
  const int LED1 = D5;
  const int LED2 = D6;
  const int LED3 = D7;
  const int LED4 = D8;

  // Sensor state tracking
  int lastStartState = HIGH;
  int lastEndState = HIGH;
  int lastLdrState = HIGH;

  // System state
  bool vehicleDetected = false; // Vehicle presence flag

  void setup() {
    Serial.begin(115200);
    Serial.println("\n=================================");
    Serial.println("Smart Street Light System (Final Logic)");
    Serial.println("=================================\n");

    // Initialize sensor pins
    pinMode(IR_START, INPUT);
    pinMode(IR_END, INPUT);
    pinMode(LDR_PIN, INPUT);

    // Initialize LED pins
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);

    // Turn off all LEDs initially
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);

    Serial.println("System Ready!");
    Serial.println("D1 = Start IR Sensor");
    Serial.println("D2 = End IR Sensor");
    Serial.println("D3 = LDR Module");
    Serial.println("D5-D8 = Street LEDs\n");
  }

  void loop() {
    // Read LDR sensor
    int ldrState = digitalRead(LDR_PIN);

    // Read IR sensors (we read them in both modes)
    int startState = digitalRead(IR_START);
    int endState = digitalRead(IR_END);

    // --- LOGIC SPLIT: NIGHT vs DAY ---

    if (ldrState == HIGH) {
      // --- NIGHTTIME LOGIC ---
      // Requirement: Lights ON, IR sensors log but do NOT turn lights off.

      // Check if we just transitioned to NIGHT
      if (ldrState != lastLdrState) {
        Serial.println("[LDR] NIGHT MODE - All lights ON. IR sensing is for logging only.");
        
        // Turn ON all LEDs
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, HIGH);
        
        vehicleDetected = false; // Reset flag for state hygiene
        lastLdrState = ldrState;
      }

      // --- Process IR sensors for LOGGING ONLY ---
      // Check START sensor
      if (startState != lastStartState) {
        if (startState == LOW) {
          Serial.println("[IR-START] Vehicle detected (logging only)");
          vehicleDetected = true;
        } else {
          Serial.println("[IR-START] Clear (logging only)");
        }
        lastStartState = startState;
      }

      // Check END sensor
      if (endState != lastEndState) {
        if (endState == LOW) {
          Serial.println("[IR-END] Vehicle detected (logging only)");
          if (vehicleDetected) {
            Serial.println("Vehicle passed (logging only)");
            vehicleDetected = false; // Reset for next vehicle
          }
        } else {
          Serial.println("[IR-END] Clear (logging only)");
        }
        lastEndState = endState;
      }
      // Note: No digitalWrite() calls are made here. Lights stay ON.

    } else {
      // --- DAYTIME LOGIC ---
      // Requirement: Lights OFF, unless motion is detected.
      // START IR turns lights ON. END IR turns lights OFF.

      // Check if we just transitioned to DAY
      if (ldrState != lastLdrState) {
        Serial.println("[LDR] DAY MODE - Lights OFF. IR motion detection ACTIVE.");
        
        // Turn OFF all LEDs
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        
        vehicleDetected = false; // Reset for day mode
        lastLdrState = ldrState;
      }

      // --- Process IR sensors for LIGHT CONTROL ---
      // Check START sensor
      if (startState != lastStartState) {
        if (startState == LOW) {
          // Motion detected at START, turn lights ON
          Serial.println("[IR-START] Vehicle detected - Lights ON");
          vehicleDetected = true;

          digitalWrite(LED1, HIGH);
          digitalWrite(LED2, HIGH);
          digitalWrite(LED3, HIGH);
          digitalWrite(LED4, HIGH);
        } else {
          Serial.println("[IR-START] Clear");
        }
        lastStartState = startState;
      }

      // Check END sensor (New logic)
      if (endState != lastEndState) {
        if (endState == LOW) {
          // Motion detected at END, turn lights OFF
          Serial.println("[IR-END] Vehicle detected - Lights OFF");
          
          if (vehicleDetected) {
            digitalWrite(LED1, LOW);
            digitalWrite(LED2, LOW);
            digitalWrite(LED3, LOW);
            digitalWrite(LED4, LOW);
            vehicleDetected = false; // Reset for next vehicle
          }
        } else {
          Serial.println("[IR-END] Clear");
        }
        lastEndState = endState;
      }
    }

    delay(50);  // Debounce delay
  }