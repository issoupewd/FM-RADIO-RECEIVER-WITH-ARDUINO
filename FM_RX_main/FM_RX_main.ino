
 //FM RADIO BY ISSOUPEWD
//************************************************************************************************
#include <Wire.h>              // I2C: A4(SDA), A5(SCL)
#include <Adafruit_GFX.h>      // OLED
#include <Adafruit_SSD1306.h>  // OLED
#include <BfButton.h>          // Encoder
#include <radio.h>             //rda
#include <RDA5807.h>           //rda


//************************************************************************************************
//RDA
float frequency = 9800;         // Initial frequency
#define MIN_FREQ 8800           // 88.00 MHz
#define MAX_FREQ 10800          // 108.00 MHz
#define FIX_BAND RADIO_BAND_FM  ///< The band that will be tuned by this sketch is FM.
#define FIX_STATION 9800        ///< The station that will be tuned by this sketch is 89.30 MHz.
#define FIX_VOLUME 50
RDA5807 radio;  // Create an instance of Class for RDA5807M Chip

/*
+-10--9--8--7--6-+
|  +------+  ++  |
|  | RDA  |  ||  |
|  | 5807 |  ||  |
|  +------+  ++  |
+--1--2--3--4--5-+

1 ----> Arduino SDA
2 ----> Arduino SCL
5 ----> Vcc
6 ----> GND
7 ----> Audio out (right channel)
8 ----> Audio out (left channel) mono
10 ---> Antenna
*/


//************************************************************************************************
//Encoder KY-040
#define KyCLK 5                                                 // Encoder CLK pin
#define kyDT 4                                                  // Encoder DT pin
#define KySW 3                                                  // Encoder SW pin
BfButton KyBtn(BfButton::STANDALONE_DIGITAL, KySW, true, LOW);  // Encoder button setup
// Encoder variables
int currentStateCLK;   // Encoder CLK state
int previousStateCLK;  // Encoder CLK state
int prs = 1;

//************************************************************************************************
// OLED0.96
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1     // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3c
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Encoder button settings
  KyBtn.onPress(pressHandler)
    .onDoublePress(pressHandler)
    .onPressFor(pressHandler, 1000);  // Custom timeout for 1 second
  // Encoder pins
  pinMode(KyCLK, INPUT);
  pinMode(kyDT, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);  //oled init

  radio.setup(); //  radio init
  radio.setRDS(true);  // Turns RDS on
  radio.setVolume(FIX_VOLUME);

  // Select a station with RDS service in your place

  radio.setFrequency(frequency);

  // RDS setup
  radio.setRDS(true);
  radio.setRdsFifo(true);
  radio.setLnaPortSel(10);  // Trying to improve sensitivity.
  radio.setAFC(true);       // Sets Automatic Frequency Control

  oledstart();  //oled starting display

  // Read the initial state of KyCLK
  previousStateCLK = digitalRead(KyCLK);
}

void loop() {
  // put your main code here, to run repeatedly:
  //encoder pushbutton
  KyBtn.read();
  //encoder frequency val
  handleEncoder();
  //*********
  //   UwU  *
  //*********
}