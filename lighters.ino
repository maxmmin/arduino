class Lighter {
    public:
        const int ID;
    
    private:
        const int RED_PIN;
        const int YELLOW_PIN;
        const int GREEN_PIN;

    public:
      Lighter(int redPin, int yellowPin, int greenPin,int id) : RED_PIN(redPin), YELLOW_PIN(yellowPin), GREEN_PIN(greenPin), ID(id) {
      }

      bool isGreen () {
        return digitalRead(GREEN_PIN)==HIGH;
      }

      void setGreenLight() {
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(RED_PIN, LOW);
      }

      void setRedLight()    {
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(RED_PIN, HIGH);
      }

      void init () {
        pinMode(GREEN_PIN, OUTPUT);
        digitalWrite(GREEN_PIN, LOW);

        pinMode(YELLOW_PIN, OUTPUT);
        digitalWrite(YELLOW_PIN, LOW);

        pinMode(RED_PIN, OUTPUT);
        digitalWrite(RED_PIN, LOW);
    }
};

/*
* CONFIG BEGIN
*/

  // red pin, yellow pin, green pin, id
  // id is not used for lighters logic but can be helpfull for debugging
  Lighter firstLighter(2,3,4, 0);
  Lighter secondLighter(5,6,7, 1);
  Lighter thirdLighter(8,9,10, 2);


  // CREATING LIGHTERS ARRAY
  Lighter lighters[] = {firstLighter, secondLighter, thirdLighter};

  const int DELAY_IN_MS = 5000;
   
  const int LENGTH = sizeof(lighters)/sizeof(lighters[0]);
/*
* CONFIG END
*/

/*
*   returns number beetween 0 and max(exclusive)
*/
int getRandom (int max) {
    return random(max);
}

void sleep(int delayInMs) {
  delay(delayInMs);
}

void iteration (Lighter* lighters, int delay, int lightersAmount) {
    int random;

    do {
        random = getRandom(lightersAmount);
    } while (lighters[random].isGreen());

    for (int iterator = 0; iterator<lightersAmount; iterator++) {
        if (iterator==random) {
            lighters[iterator].setGreenLight();
        } else {
            lighters[iterator].setRedLight();
        }
    }

    sleep(delay);
}

void setup() {
  randomSeed(analogRead(A0));
  for (int iterator = 0; iterator<LENGTH; iterator++) {
        lighters[iterator].init();
  }
  
  while (true) {
    iteration(lighters, DELAY_IN_MS, LENGTH);
    if (DELAY_IN_MS==-1) break;
  }
}

void loop() {
}
