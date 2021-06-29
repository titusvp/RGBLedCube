#include "Animations.h"
ANIMATION ani;



void loop() {
//____________________________________________________________________________
//Animation 1
//____________________________________________________________________________
  unsigned long starttime = millis();
  unsigned long endtime = starttime;
  while((endtime - starttime) <= 30000) // loop runs for 30 secs
  {
    ani.LedTestAnimation(); // function to run for amount of time
    endtime = millis();
  }


  ani.clearLeds();
//____________________________________________________________________________
//Animation 2
//____________________________________________________________________________
  starttime = millis();
  endtime = starttime;
  while((endtime - starttime) <= 30000) // loop runs for 30 secs
  {
    ani.randomBlink(); // function to run for amount of time
    endtime = millis();
  }
  ani.clearLeds();
  delay(500);

//____________________________________________________________________________
//Animation 3
//____________________________________________________________________________

  starttime = millis();
  endtime = starttime;
    while((endtime - starttime) <= 30000) // loop runs for 30 secs
  {
    ani.spiralAnimation();
    endtime = millis();
  }

}// loop close 
