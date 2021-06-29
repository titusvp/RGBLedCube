//  
//#include "TLC5955.h"
//  
//  void clearLeds(){
//    for (int i=0; i<16; i++){ 
//    tlc.setLed(i,0);
//    tlc.updateLeds();
//    tlc.latch();
//    }
//  }
//
//
//  
//  void clearLayers(){
//    digitalWrite(L0,HIGH);
//    digitalWrite(L1,HIGH);
//    digitalWrite(L2,HIGH);
//    digitalWrite(L3,HIGH);  
//  }
//  
//  void randomLayer(){
//     digitalWrite(layer[random(0,4)],LOW);
//  }
//  void randomRED(uint16_t bright){
//     tlc.setLed(random(16),random(500, bright),0,0);
//  }
//    
//  void randomGREEN(uint16_t bright){  
//    tlc.setLed(random(16),0,random(500, bright),0);
//  }
//    
//  void randomBLUE(uint16_t bright){   
//    tlc.setLed(random(16),0,0,random(500, bright));
//  }
//
//
//      
//  void moveAnimtion(uint8_t steps, char heading){
//      channelVals[16];
//
//      if (heading == "T"){
//        for(int i=0; i<16; i++){
//          tlc.setLed(i+4,tlc.getChannelValue(i,r), tlc.getChannelValue(i,g), tlc.getChannelValue(i,b))
//        }
//      }
//
//      if(heading == "B")
//        for(int i=0; i<16; i++){
//          tlc.setLed(i-4,tlc.getChannelValue(i,r), tlc.getChannelValue(i,g), tlc.getChannelValue(i,b))
//        }        
//      
//      if(heading == "F")
//      }
//    
//    
//    } 
//}  




  
