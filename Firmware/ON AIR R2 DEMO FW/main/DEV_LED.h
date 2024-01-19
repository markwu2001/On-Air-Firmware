
////////////////////////////////////
//   DEVICE-SPECIFIC LED SERVICES //
////////////////////////////////////

#include <MC_MCP41010.h>

//Pin Definitions for On Air R2
#define SPI_COPI 13
#define SPI_CLK 14
#define SPI_CS 15
#define BUCKEN 16

MC_MCP41010 MCP41010(SPI_CS, SPI_CLK,SPI_COPI);

//////////////////////////////////

// Here's the new code defining DEV_DimmableLED - changes from above are noted in the comments

struct DEV_DimmableLED : Service::LightBulb {       // Dimmable LED

  int ledPin;                                   
  SpanCharacteristic *power;                        // reference to the On Characteristic
  SpanCharacteristic *level;                        // NEW! Create a reference to the Brightness Characteristic instantiated below
  
  DEV_DimmableLED(int ledPin) : Service::LightBulb(){       // constructor() method

    power=new Characteristic::On();     
                
    level=new Characteristic::Brightness(50);       // NEW! Instantiate the Brightness Characteristic with an initial value of 50% (same as we did in Example 4)
    level->setRange(0,100,1);                       // NEW! This sets the range of the Brightness to be from a min of 0%, to a max of 100%, in steps of 1% (different from Example 4 values)

    this->ledPin=ledPin;                            
    pinMode(ledPin,OUTPUT);
    digitalWrite(BUCKEN,HIGH);  
    MCP41010.Begin();                  
    
  } // end constructor

  boolean update(){                              // update() method
    // Here we set the brightness of the LED by calling ledPin->set(brightness), where brightness=0-100.
    // Note HomeKit sets the on/off status of a LightBulb separately from its brightness, which means HomeKit
    // can request a LightBulb be turned off, but still retains the brightness level so that it does not need
    // to be resent once the LightBulb is turned back on.
    
    // Multiplying the newValue of the On Characteristic ("power", which is a boolean) with the newValue of the
    // Brightness Characteristic ("level", which is an integer) is a short-hand way of creating the logic to
    // set the LED level to zero when the LightBulb is off, or to the current brightness level when it is on.
    
    // ledPin->set(power->getNewVal()*level->getNewVal());
    digitalWrite(ledPin,power->getNewVal()); 
    MCP41010.Write(map(level->getNewVal(), 0, 100, 178, 255));
   
    return(true);                               // return true
  
  } // update
};
      
//////////////////////////////////
