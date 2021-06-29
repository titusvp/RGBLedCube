#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <stdint.h>



/*Animations defines functions to easily handle different led combinations and beeing able to chain them */

//________Macros__________________









//_________________________________
class ANIMATION{

public:
  void init();

  // clearing functions
  void clearLeds();
  void clearLayers();

  // turnon functions
  void randomLayer();
  void randomRED(uint16_t bright);
  void randomGREEN(uint16_t bright);
  void randomBLUE(uint16_t bright);
  void fadeSetLed(uint8_t channel, uint16_t maxBrightRed, uint16_t maxBrightGreen, uint16_t maxBrightBlue,uint16_t fadeResolution, uint8_t fadeDelay, bool invert );
  

  void wall(char heading,uint16_t brightRgb ); //wall of leds with heading of T(op), B(ottom), L(eft), R(ight), B(back), F(ront)
  void moveAnimtion(uint8_t steps, char heading);
  


  //complete Animations
  void LedTestAnimation();
  void randomBlink();
  void spiralAnimation();
   
    
  
  };








#endif
// class closing
