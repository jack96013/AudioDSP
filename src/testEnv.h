#ifndef __TESTENV_H__
#define __TESTENV_H__

#include "Arduino.h"
#include "board.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

#include <ClickEncoder.h>
ClickEncoder encoder = ClickEncoder(BOARD_EC11_A_PIN,
                                    BOARD_EC11_B_PIN,
                                    BOARD_EC11_SW_PIN,
                                    4);

const uint16_t PixelCount = 24; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 2;     // make sure to set this to the correct pin, ignored for Esp8266

#define colorSaturation 128

// three element pixels, in different order and speeds
// NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod> strip(PixelCount, BOARD_RGB_LED_1_PIN);
// NeoPixelBus<NeoRgbFeature, NeoWs2812xMethod> strip2(2, BOARD_RGB_LED_2_PIN);

#include <Adafruit_NeoPixel.h>

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);

HslColor hslRed(red);
HslColor hslGreen(green);
HslColor hslBlue(blue);
HslColor hslWhite(white);
HslColor hslBlack(black);

void i2c_scanner();

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         BOARD_OLED_MOSI_PIN, BOARD_OLED_SCK_PIN, BOARD_OLED_DC_PIN, BOARD_OLED_RES_PIN, BOARD_OLED_CS_PIN);

Adafruit_NeoPixel strip(24, BOARD_RGB_LED_1_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(2, BOARD_RGB_LED_2_PIN, NEO_GRB + NEO_KHZ800);


int encoderValue = 0;

void test_setup()
{
  Serial.println();
  Serial.println("Initializing...");
  Serial.flush();

  // this resets all the neopixels to an off state
  // strip.Begin();
  // strip.Show();

  // strip2.Begin();
  // strip2.SetPixelColor(0,hslRed);
  // strip2.SetPixelColor(1,hslBlue);
  // strip2.Show();

  strip.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
  strip.setBrightness(100);

  strip.show();
  strip2.begin(); // INITIALIZE NeoPixel strip2 object (REQUIRED)
  strip2.setPixelColor(0, strip2.Color(0, 150, 0));
  strip2.setPixelColor(1, strip2.Color(150, 0, 0));
  strip2.show(); // Turn OFF all pixels ASAP

  // strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  Serial.println();
  Serial.println("Running...");

  Wire.begin();
  i2c_scanner();

  if (!display.begin(SSD1306_SWITCHCAPVCC))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5, 28);
  display.println("ECIE LAB");
  display.display();

  Serial2.begin(115200);

  pinMode(BOARD_MUX_SEL_PIN, OUTPUT);
  digitalWrite(BOARD_MUX_SEL_PIN, LOW);

  pinMode(BOARD_ASRC_MODE0_PIN, OUTPUT);
  pinMode(BOARD_ASRC_MODE1_PIN, OUTPUT);
  pinMode(BOARD_ASRC_MODE2_PIN, OUTPUT);
  digitalWrite(BOARD_ASRC_MODE0_PIN, 0);
  digitalWrite(BOARD_ASRC_MODE1_PIN, 1);
  digitalWrite(BOARD_ASRC_MODE2_PIN, 0);

  Serial2.println("AT+REBOOT");

  pinMode(BOARD_EC11_A_PIN, INPUT);
  pinMode(BOARD_EC11_B_PIN, INPUT);
  pinMode(BOARD_EC11_SW_PIN, INPUT);

  encoder.setAccelerationEnabled(true);
  encoder.setButtonHeldEnabled(true);
  encoder.setDoubleClickEnabled(true);

  // Enable the button to be on pin 0.  Normally pin 0 is not recognized as a valid pin for a button,
  // this is to maintain backward compatibility with an old version of the library
  // This version can have the button on pin zero, and this call enables the feature.
  // in this version best to use pin -1 instead of 0 to disable button functions
  encoder.setButtonOnPinZeroEnabled(true);

  pinMode(BOARD_RESET_PIN, OUTPUT);
  
  digitalWrite(BOARD_RESET_PIN, LOW);
  delay(100);
  digitalWrite(BOARD_RESET_PIN, HIGH);
}

int getWheelIndex(int i)
{
  int newValue =  18 - i;
  if (newValue < 0)
  {
    return 23 - (newValue*-1-1);
  }
  else
    return newValue;
}

void ec11_read();
void test_loop()
{
  // delay(5000);

  // for (int i = 0; i < strip.PixelCount(); i++)
  // {
  //     strip.SetPixelColor(i, hslWhite);
  //     strip.Show();
  //     delay(100);
  // }
  // delay(1500);
  // for (int i = 0; i < strip.PixelCount(); i++)
  // {
  //     strip.SetPixelColor(i, hslRed);

  // }
  // strip.Show();
  static uint32_t lastService = 0;
  if (lastService + 100 < millis())
  {
    lastService = millis();
    float percent = encoderValue / 100.0f;
    int num = 24 * percent;
    for (int i = 0; i < num; i++)
    {
      strip.setPixelColor(getWheelIndex(i), strip.Color((255 - 255.0*(i/23)), (255.0*(i/23.0)), 0));
    }
    for (int i = num; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(getWheelIndex(i), strip.Color(255, 255, 255));
    }
    strip.show();

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(5, 5);
    display.println("ECIE LAB");
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20, 35);
    display.println(String(encoderValue));
    display.display();
    
    
  }
  

  ec11_read();
}


void ec11_read()
{

  // Call Service in loop becasue using timer interrupts may affect ESP8266 WIFI
  // however call no more than 1 time per millisecond to reduce encoder bounce
  static uint32_t lastService = 0;
  if (lastService + 1000 < micros())
  {
    lastService = micros();
    encoder.service();
  }

  static int16_t last, value;
  value += encoder.getValue();

  if (value != last)
  {
    if (value < last) 
    {
      encoderValue -= last - value;
      Serial.println("-");
    }
    else
    {
      encoderValue += value - last;
      Serial.println("+");
    }
    last = value;
    
    if (encoderValue > 100)
    {
      encoderValue = 100;
      
    }
    else if (encoderValue < 0)
    {
      encoderValue = 0;
    }
    Serial.print("Encoder Value: ");
    Serial.println(value);
    Serial.print("b Value: ");
    Serial.println(encoderValue);

  }

  ClickEncoder::Button b = encoder.getButton();
  if (b != ClickEncoder::Open)
  {
    Serial.print("Button: ");
#define VERBOSECASE(label)  \
  case label:               \
    Serial.println(#label); \
    break;
    switch (b)
    {
      case ClickEncoder::Clicked:
        digitalWrite(BOARD_MUX_SEL_PIN, !digitalRead(BOARD_MUX_SEL_PIN));
        Serial.println("MUX");
      break;
      // VERBOSECASE(ClickEncoder::Pressed);
      // VERBOSECASE(ClickEncoder::Held)
      // VERBOSECASE(ClickEncoder::Released)
      // VERBOSECASE(ClickEncoder::Clicked)
      // VERBOSECASE(ClickEncoder::DoubleClicked)
      
    }
  }
}

void i2c_scanner()
{
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknow error at address 0x");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
  {
    Serial.println("No I2C devices found\n");
  }
  else
  {
    Serial.println("done\n");
  }
}

#endif

