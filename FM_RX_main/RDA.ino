
void RSSIval()
{
 unsigned int rssi = radio.getRssi();
Serial.println(rssi);
 
  
   // Adjust delay as needed to control the update frequency
}


void printferq() {

  radio.setFrequency(frequency);
}

