#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7
#define PIN_8 8
#define PIN_9 9
#define PIN_10 10

typedef enum {
  RUNNING,
  STOPPED,
} TIMER_MODES;

unsigned int pin_2_button_state = 0;
unsigned int pin_3_button_state = 0;
unsigned int pin_4_button_state = 0;

unsigned int timer = 0; //timer in minutes

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_2, INPUT_PULLUP);
  pinMode(PIN_3, INPUT_PULLUP);
  pinMode(PIN_4, INPUT_PULLUP);
  pinMode(PIN_7, OUTPUT);
  pinMode(PIN_8, OUTPUT);
  pinMode(PIN_9, OUTPUT);
  pinMode(PIN_10, OUTPUT);
}

void loop() {
  pin_2_button_state = digitalRead(PIN_2);
  pin_3_button_state = digitalRead(PIN_3);
  pin_4_button_state = digitalRead(PIN_4);
  digitalWrite(PIN_8, !pin_2_button_state);
  digitalWrite(PIN_9, !pin_3_button_state);
  digitalWrite(PIN_10,!pin_4_button_state);
}
