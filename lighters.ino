class Lighter {
    public:
        const int ID;
    
    private:
        const int RED_PIN;
        const int GREEN_PIN;

    public:
      Lighter(int redPin, int greenPin,int id) : RED_PIN(redPin), GREEN_PIN(greenPin), ID(id) {
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
        pinMode(this->GREEN_PIN, OUTPUT);
        pinMode(this->RED_PIN, OUTPUT);
    }
};

// red pin, grean pin, id
Lighter firstLighter(2,4, 0);
Lighter secondLighter(5,7, 1);
Lighter thirdLighter(8,10, 2);


// CREATING LIGHTERS ARRAY
Lighter lighters[3] = {firstLighter, secondLighter, thirdLighter};

int length = sizeof(lighters)/sizeof(lighters[0]);

int getRandom (int max) {
    return random(max);
}

void sleep(int delayInMs) {
  delay(delayInMs);
}

void iteration (Lighter* lighters, int delay, int lightersAmount) {
    int random;

    do {
        random = getRandom(lightersAmount-1);
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
  for (int iterator = 0; iterator<length; iterator++) {
        lighters[iterator].init();
  }
}

void loop() {
   iteration(lighters, 5000, length);
}
