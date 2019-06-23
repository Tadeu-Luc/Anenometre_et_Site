/*

Adapted from the excellent work here:

http://cactus.io/hookups/weather/anemometer/davis/hookup-arduino-to-davis-anemometer

Works with a Davis anemometer, which is available on eBay in the $110 range.

Intended to interface with the weeWX program but easily adapted for other uses.

See https://github.com/wrybread/ArduinoWeatherStation

wrybread@gmail.com


*/


#include "TimerOne.h" // Timer Interrupt set to 2 second for read sensors 
#include <math.h> 

#define WindSensorPin (2) // The pin location of the anemometer sensor 
#define WindVanePin (A4) // The pin the wind vane sensor is connected to 
#define VaneOffset 0; // define the anemometer offset from magnetic north 


int vaneValue; // raw analog value from wind vane 
int windDirection; // translated 0 - 360 direction 
int windCalDirection; // converted value with offset applied 
String windCompassDirection; // wind direction as compass points
int lastWindDirectionValue; // last direction value 
String Windnoeud2;

// sensors to be added
int temperature;
int barometer; 


volatile bool IsSampleRequired; // this is set true every 2.5s. Get wind speed 
volatile unsigned int TimerCount; // used to determine 2.5sec timer count 
volatile unsigned long Rotations; // cup rotation counter used in interrupt routine 
volatile unsigned long ContactBounceTime; // Timer to avoid contact bounce in isr 

float WindSpeed; // speed miles per hour 
float Windnoeud;




void setup() { 

  lastWindDirectionValue = 0; 
  
  IsSampleRequired = false; 
  
  TimerCount = 0; 
  Rotations = 0; // Set Rotations to 0 ready for calculations 
  
  Serial.begin(9600); 
  
  pinMode(WindSensorPin, INPUT); 

  //@@ Ooops, typo in this line from the original script
  //attachInterrupt(digitalPinToInterrupt(WindSensorPin), rotation, FALLING); 
  attachInterrupt(digitalPinToInterrupt(WindSensorPin), isr_rotation, FALLING); 
  
  Serial.println("Station Météo Eixa6 Informatique"); 
  
  // Setup the timer interupt 
  Timer1.initialize(500000);// Timer interrupt every 2.5 seconds 
  Timer1.attachInterrupt(isr_timer); 

} 

void loop() { 

  getWindDirection(); 


  // placeholders for temperature and barometer.
  temperature = 0;
  barometer = 0;

  
  // Only update the display if change greater than 5 degrees. 
  if(abs(windCalDirection - lastWindDirectionValue) > 5) { 
    lastWindDirectionValue = windCalDirection; 
  } 

  if(IsSampleRequired) { 
    // convert to mp/h using the formula V=P(2.25/T) 
    // V = P(2.25/2.5) = P * 0.9 
    WindSpeed = Rotations * 0.9; 
    Rotations = 0; // Reset count for next sample 
    
    IsSampleRequired = false; 


    Serial.print(WindSpeed); Serial.print(",");
    Serial.print(windCalDirection);  Serial.print(",");
    Serial.print(windCompassDirection);  Serial.print(",");
    Serial.print (Windnoeud2); Serial.print(",");

    Serial.println();

  } 
} 


// isr handler for timer interrupt 
void isr_timer() { 

  TimerCount++; 
  
  if(TimerCount == 6) { 
    IsSampleRequired = true; 
    TimerCount = 0; 
  } 
} 





void isr_rotation() { 

  if((millis() - ContactBounceTime) > 15 ) { // debounce the switch contact. 
    Rotations++; 
    ContactBounceTime = millis(); 
  } 

} 






// Get Wind Direction 
void getWindDirection() { 

    
  windDirection = map(vaneValue, 0, 1023, 0, 360); 
  windCalDirection = windDirection + VaneOffset; 
  
  if(windCalDirection > 360) windCalDirection = windCalDirection - 360; 
  if(windCalDirection < 0) windCalDirection = windCalDirection + 360; 


  // get the compass direction for convenience
  if (windCalDirection < 22) windCompassDirection = "Nord";
  else if (windCalDirection < 67) windCompassDirection = "Nord Est";
  else if (windCalDirection < 112) windCompassDirection = "Est";
  else if (windCalDirection < 157) windCompassDirection = "Sud Est";
  else if (windCalDirection < 212) windCompassDirection = "Sud";
  else if (windCalDirection < 247) windCompassDirection = "Sud Ouest";
  else if (windCalDirection < 292) windCompassDirection = "Ouest";
  else if (windCalDirection < 337) windCompassDirection = "Nord Ouest";
  else windCompassDirection = "Nord";  
}

void getWindnoeud2 () {
 Windnoeud= WindSpeed * 0.868976 ;
 
  if(Windnoeud >= 1 && Windnoeud < 3)
    Windnoeud2= "Très légère brise" ;
  else if(Windnoeud >= 4 && Windnoeud < 6)
    Windnoeud2= "Légère brise" ;
  else if(Windnoeud >= 7 && Windnoeud < 10)
    Windnoeud2= "Petite brise";
  else if(Windnoeud >= 11 && Windnoeud < 16)
    Windnoeud2= "Jolie brise" ;
  else if(Windnoeud >= 17 && Windnoeud < 21)
    Windnoeud2= "Bonne brise" ;
  else if(Windnoeud >= 22 && Windnoeud < 27)
    Windnoeud2= "Vent frais" ;
  else if(Windnoeud >= 28 && Windnoeud < 33)
    Windnoeud2= "Grand frais";
  else if(Windnoeud >= 34 && Windnoeud < 40)
    Windnoeud2= "Coup de vent" ;
  else if(Windnoeud >= 41 && Windnoeud < 47)
    Windnoeud2= "Fort coup de vent" ;
  else if(Windnoeud >= 48 && Windnoeud < 55)
    Windnoeud2= "Tempête";
  else if(Windnoeud >= 56 && Windnoeud < 63)
    Windnoeud2= "Violente tempête";
  else if(WindSpeed > 63)
    Windnoeud2= "Ouragan" ;
  else 
    Windnoeud2= "Calme";
} 






// Convert MPH to Knots 
float getKnots(float speed) { 
  return speed * 0.868976; 
} 
