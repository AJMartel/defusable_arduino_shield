unsigned long secTimer = 0;
unsigned long colonBlinker = 0;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

/* setup stuff */

void setupRTC() {
  delay(1000); // wait for console opening

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC :(");
    while (1);
  }

  if (rtc.lostPower()) {
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    //      April 7, 2017 at 10:06 pm you would call:
    // rtc.adjust(DateTime(2017, 4, 7, 22, 6, 0));

    Serial.println("RTC lost power, we did a time reset based on sketch!");
    Serial.println("Note: you can insert a battery in the small ");
    Serial.println("battery slot of the shield to preseve time");
  }
}

/* methods that update stuff etc */

void updateCountDown() {
  if (millis() > (secTimer + updateSpeed)) {
    secTimer = millis();
    countDown--;
    bombDisplay.setBombTime(countDown);
    if (useSoundFeedback) {
      makeBleep();
    }
  }
}

