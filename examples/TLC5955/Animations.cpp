#include "Animations.h"
#include "TLC5955.h"
#include "SPI.h"

// Create TLC5955 object
TLC5955 tlc;
ANIMATION _ani;
// Pin deifnition
#define GSCLK 2
#define LAT 3
#define SPI_MOSI 13
#define SPI_CLK 12

#define L0 16// Layer 0-3
#define L1 15
#define L2  7
#define L3 11


const uint8_t TLC5955::_tlc_count = 1;          // Change to reflect number of TLC chips
float TLC5955::max_current_amps = 10;      // Maximum current output, amps
bool TLC5955::enforce_max_current = false;   // Whether to enforce max current limit

// Define dot correction, pin rgb order, and grayscale data arrays in program memory
uint8_t TLC5955::_dc_data[TLC5955::_tlc_count][TLC5955::LEDS_PER_CHIP][TLC5955::COLOR_CHANNEL_COUNT];
uint8_t TLC5955::_rgb_order[TLC5955::_tlc_count][TLC5955::LEDS_PER_CHIP][TLC5955::COLOR_CHANNEL_COUNT];
uint16_t TLC5955::_grayscale_data[TLC5955::_tlc_count][TLC5955::LEDS_PER_CHIP][TLC5955::COLOR_CHANNEL_COUNT];



void setup() {
  //Serial.begin(9600);
  // The library does not ininiate SPI for you, so as to prevent issues with other SPI libraries
  SPI.begin();
  tlc.init(LAT, SPI_MOSI, SPI_CLK, GSCLK);

  // We must set dot correction values, so set them all to the brightest adjustment
  tlc.setAllDcData(127);

  // Set Max Current Values (see TLC5955 datasheet)
  tlc.setMaxCurrent(3, 3, 3); // Go up to 7

  // Set Function Control Data Latch values. See the TLC5955 Datasheet for the purpose of this latch.
  // Order: DSPRPT, TMGRST, RFRESH, ESPWM, LSDVLT
  tlc.setFunctionData(true, true, true, true, true);

  // set all brightness levels to max (127)
  int currentR = 127;
  int currentB = 127;
  int currentG = 127;
  tlc.setBrightnessCurrent(currentR, currentB, currentG);

  // Update Control Register
  tlc.updateControl();

  // Provide LED pin order (R,G,B)
  tlc.setRgbPinOrder(0, 1, 2);

  //init layerpins as output
  pinMode(L0, OUTPUT);
  digitalWrite(L0,HIGH);
  pinMode(L1, OUTPUT);
  digitalWrite(L1,HIGH);
  pinMode(L2, OUTPUT);
  digitalWrite(L2,HIGH);  
  pinMode(L3, OUTPUT);
  digitalWrite(L3,HIGH);

  
  
}//closing setup

int q,p = 0;
uint8_t layer[] = {L0,L1,L2,L3};






  void ANIMATION::clearLeds(){
    for (int i=0; i<16; i++){ 
    tlc.setLed(i,0);
    tlc.updateLeds();
    tlc.latch();
    }
  }


  
  void ANIMATION::clearLayers(){
    digitalWrite(L0,HIGH);
    digitalWrite(L1,HIGH);
    digitalWrite(L2,HIGH);
    digitalWrite(L3,HIGH);  
  }
  
  void ANIMATION::randomLayer(){
     digitalWrite(layer[random(0,4)],LOW);
  }
  void ANIMATION::randomRED(uint16_t bright){
     tlc.setLed(random(16),random(500, bright),0,0);
  }
    
  void ANIMATION::randomGREEN(uint16_t bright){  
    tlc.setLed(random(16),0,random(500, bright),0);
  }
    
  void ANIMATION::randomBLUE(uint16_t bright){   
    tlc.setLed(random(16),0,0,random(500, bright));
  }

    //unfinished
  void ANIMATION::fadeSetLed(uint8_t channel, uint16_t maxBrightRed, uint16_t maxBrightGreen, uint16_t maxBrightBlue,uint16_t fadeResolution, uint8_t fadeDelay , bool invert){
    if(maxBrightRed < bit(16)&& maxBrightGreen < bit(16)&& maxBrightBlue < bit(16)&& fadeDelay > 2 && fadeResolution > 0){
      if(invert == 0){
        for(uint16_t i=0; i<= maxBrightRed/fadeResolution; i= i+fadeResolution){
          tlc.setLed(channel, maxBrightRed, maxBrightGreen, maxBrightBlue);
          tlc.updateLeds();
          tlc.latch();
          delay(fadeDelay);
        }
      }
      if(invert == 1){
        for(uint16_t i=maxBrightRed; i<= maxBrightRed/fadeResolution; i= i-fadeResolution){
          tlc.setLed(channel, maxBrightRed, maxBrightGreen, maxBrightBlue);
          tlc.updateLeds();
          tlc.latch();
          delay(fadeDelay);
        } 
      
      }
    } 
  }//closing fadeSetLed()


  void ANIMATION::randomBlink(){
    
      //delay timer between each iterate of new leds beeing turned on in ms
      const uint16_t ANIMATION_DELAY = 400;
      
      //turn on one random layer of all 4 layers
      _ani.randomLayer();
      
      // set one of 16 led towers in a random color
      tlc.setLedAppend(random(16),random(500,bit(16)-1), random(500,bit(16)-1),random(500,bit(16)-1));
      //update and turn on leds
      tlc.updateLeds();
      tlc.latch();
      
      // delay 
      delay(ANIMATION_DELAY);
      
      // if after a number of iterations all 4 layers have been turned on....
      if (digitalRead(L0)==LOW && digitalRead(L1)==LOW &&digitalRead(L2)==LOW &&digitalRead(L3)==LOW ){
        // all leds are turned off
        clearLayers();   
      }
      // if after q iterations not all layers randomly have been turned on...
      if (q == 32){
      //.. turn off all leds as well.
      clearLeds();
      // reset counter  
        q=0;
      }
      // else raise counter by 1
      q++;
  }// closing randomBlink()


  void ANIMATION::LedTestAnimation(){
    const uint16_t delayTime = 500; // dont go below 20 because of heat dissipation
    
    digitalWrite(L0,LOW);
    digitalWrite(L1,LOW);
    digitalWrite(L2,LOW);
    digitalWrite(L3,LOW);
   
    for (int i=0;i<16;i++){
  
        //set leds on
      tlc.setLed(i,bit(16)-1,0,0);
      tlc.updateLeds();
      tlc.latch();
      delay(delayTime);
        //set leds off
      tlc.setLed(i,0);
      tlc.updateLeds();
      tlc.latch();
      delay(delayTime);
      
       //set leds on
      tlc.setLed(i,0,bit(16)-1,0);
      tlc.updateLeds();
      tlc.latch();
      delay(delayTime);
        //set leds off
      tlc.setLed(i,0);
      tlc.updateLeds();
      tlc.latch();
      delay(delayTime);
      
        //set leds on
      tlc.setLed(i,0,0,bit(16)-1);
      tlc.updateLeds();
      tlc.latch();
      delay(delayTime);
      //set leds off
      tlc.setLed(i,0);
      tlc.updateLeds();
      tlc.latch();
      delay(delayTime);
    }
  }//LedTestAnimation closing


                                                          //    0,1,2,3
                                                          //    7,11,15,
                                                          //    14,13,12,
                                                          //    8,4,0,1
                                                          //
                                                          //    6,10,9,5
  
   void ANIMATION::spiralAnimation(){
    const uint8_t fadeResolution = 10000;
    uint8_t led_array[] = {0,1,2,3, 7,11,15, 14,13,12, 8,4,0,1,  6,10,9, 5,6,10 ,9,5,6, 10,9,4};
    uint16_t fadeMask[]={0,5000,10000,15000,20000,250000,30000,35000,40000,45000,55000,60000,65000};
  for(uint8_t i=0; i<=25; i++){
    if(i<=3){digitalWrite(L0,LOW), digitalWrite(L1,HIGH), digitalWrite(L2,HIGH),digitalWrite(L3,HIGH);}
    if(i> 3 && i<=6){digitalWrite(L0,HIGH), digitalWrite(L1,LOW), digitalWrite(L2,HIGH),digitalWrite(L3,HIGH);}
    if(i> 6 && i<=9){digitalWrite(L0,HIGH), digitalWrite(L1,HIGH), digitalWrite(L2,LOW),digitalWrite(L3,HIGH);}
    if(i> 9 && i<=13){digitalWrite(L0,HIGH), digitalWrite(L1,HIGH), digitalWrite(L2,HIGH),digitalWrite(L3,LOW);}
    
    if(i> 13 && i<=16){digitalWrite(L0,HIGH), digitalWrite(L1,HIGH), digitalWrite(L2,HIGH),digitalWrite(L3,LOW);}
    if(i> 16 && i<=19){digitalWrite(L0,HIGH), digitalWrite(L1,HIGH), digitalWrite(L2,LOW),digitalWrite(L3,HIGH);}
    if(i> 19 && i<=22){digitalWrite(L0,HIGH), digitalWrite(L1,LOW), digitalWrite(L2,HIGH),digitalWrite(L3,HIGH);}    
    if(i> 22 && i<=25){digitalWrite(L0,LOW), digitalWrite(L1,HIGH), digitalWrite(L2,HIGH),digitalWrite(L3,HIGH);}
    
    for(int j=0; j<12; j++ ){
     // tlc.setLed(led_array[i], fadeMask[random(12)],fadeMask[random(12)],fadeMask[random(12)]);
        tlc.setLed(led_array[i], bit(15),0,bit(15));
      }
      tlc.updateLeds();
      tlc.latch();
      
    
    delay(125);
    tlc.setAllLed(0);
    tlc.updateLeds();
    tlc.latch();
  } 
    
    
    
    
  }
  
