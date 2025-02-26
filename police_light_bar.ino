
#define RED_LIGHT_BAR_PIN 6
#define BLUE_LIGHT_BAR_PIN 7

#define FAST_STROBE_INPUT_PIN 10
#define STROBE_INPUT_PIN 11

#define FS_INDICATOR_PIN 2
#define S_INDICATOR_PIN 3

bool fastStrobeActive = false;
bool strobeActive = false;
bool lastFastStrobeButtonState = HIGH;
bool lastStrobeButtonState = HIGH;

void setup() {
  pinMode(RED_LIGHT_BAR_PIN, OUTPUT);
  pinMode(BLUE_LIGHT_BAR_PIN, OUTPUT);
  
  pinMode(FS_INDICATOR_PIN, OUTPUT);
  pinMode(S_INDICATOR_PIN, OUTPUT);

  pinMode(FAST_STROBE_INPUT_PIN, INPUT_PULLUP);
  pinMode(STROBE_INPUT_PIN, INPUT_PULLUP);

  // Ensure indicators start off
  digitalWrite(FS_INDICATOR_PIN, LOW);
  digitalWrite(S_INDICATOR_PIN, LOW);
}

void fastStrobe() {
  for (int i = 0; i < 3; i++) { // Quick bursts
    digitalWrite(RED_LIGHT_BAR_PIN, HIGH);
    delay(40);
    digitalWrite(RED_LIGHT_BAR_PIN, LOW);
    delay(40);
  }
  
  delay(50); // Small pause between bursts

  for (int i = 0; i < 3; i++) { // Faster flashes
    digitalWrite(BLUE_LIGHT_BAR_PIN, HIGH);
    delay(40);
    digitalWrite(BLUE_LIGHT_BAR_PIN, LOW);
    delay(40);
  }
  
  delay(80); // Longer pause before repeating
}

void strobe(){
  digitalWrite(RED_LIGHT_BAR_PIN, HIGH);
  delay(100);
  digitalWrite(RED_LIGHT_BAR_PIN, LOW);
  delay(40);
  digitalWrite(BLUE_LIGHT_BAR_PIN, HIGH);
  delay(100);
  digitalWrite(BLUE_LIGHT_BAR_PIN, LOW);
  delay(40);
}

void loop() {
   // Read button states
  bool fastStrobeButtonState = digitalRead(FAST_STROBE_INPUT_PIN);
  bool strobeButtonState = digitalRead(STROBE_INPUT_PIN);

  // Toggle Fast Strobe
  if (fastStrobeButtonState == LOW && lastFastStrobeButtonState == HIGH) {
    fastStrobeActive = !fastStrobeActive; // Toggle state
    strobeActive = false; // Turn off the other mode
  }

  // Toggle Strobe
  if (strobeButtonState == LOW && lastStrobeButtonState == HIGH) {
    strobeActive = !strobeActive; // Toggle state
    fastStrobeActive = false; // Turn off the other mode
  }

  // Update indicator lights
  digitalWrite(FS_INDICATOR_PIN, fastStrobeActive ? HIGH : LOW);
  digitalWrite(S_INDICATOR_PIN, strobeActive ? HIGH : LOW);

  // Run the active strobe pattern
  if (fastStrobeActive) {
    fastStrobe();
  } 
  else if (strobeActive) {
    strobe();
  } 
  else {
    digitalWrite(RED_LIGHT_BAR_PIN, LOW);
    digitalWrite(BLUE_LIGHT_BAR_PIN, LOW);
  }

  // Store last button states
  lastFastStrobeButtonState = fastStrobeButtonState;
  lastStrobeButtonState = strobeButtonState;

  delay(50); // Basic debounce delay
}
