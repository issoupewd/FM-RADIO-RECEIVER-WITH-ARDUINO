// Button press handling function
void pressHandler(BfButton *KyBtn, BfButton::press_pattern_t pattern) {
  switch (pattern) {
    case BfButton::SINGLE_PRESS:
      // Go to max frequency (108.00 MHz)
      frequency = MAX_FREQ;
      break;

    case BfButton::DOUBLE_PRESS:
      // Go to min frequency (88.00 MHz)
      frequency = MIN_FREQ;
      break;
    case BfButton::LONG_PRESS:
      prs += 1;
      if (prs > 2) {
        prs = 1;  // Roll over to max frequency if below min frequency
      }
  }

  oledfreq();
  printferq();
 
}

// Encoder handling function
void handleEncoder() {
  // Read the current state of KyCLK
  currentStateCLK = digitalRead(KyCLK);

  // If the previous and the current state of the KyCLK are different then a pulse has occurred
  if (currentStateCLK != previousStateCLK) {

    // counterclockwise
    if (digitalRead(kyDT) != currentStateCLK) {
      // Adjust frequency
      if (prs == 1) {
        frequency += 10;  // by 0.1 MHz
      } else {
        frequency += 100;  //  by 1 MHz
      }

      if (frequency > MAX_FREQ) {
        frequency = MIN_FREQ;  //to min frequency if above max frequency
      }


    } else {  //clockwise
      // Adjust frequency
      if (prs == 1) {
        frequency -= 10;  // by 0.1 MHz
      } else {
        frequency -= 100;  //  by 1 MHz
      }
      if (frequency < MIN_FREQ) {
        frequency = MAX_FREQ;  //  to max frequency if below min frequency
      }
    }
    oledfreq();
  printferq();
  }

  // Update previousStateCLK
  previousStateCLK = currentStateCLK;
}