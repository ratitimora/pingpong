/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "cellular_hal.h"

const pin_t MY_LED = D7;

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Set ellular credentials
STARTUP(cellular_credentials_set("hologram", "", "", NULL));

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

// Set let D7 on/off
int ledToggle(String command)
{
    if (command.equals("on"))
    {
        digitalWrite(MY_LED, HIGH);
        Log.info("MY_LED = ON");
        Particle.publish("ballStatus", "SBH9905");
        return 1;
    }
    else if (command.equals("off"))
    {
        digitalWrite(MY_LED, LOW);
        Log.info("MY_LED = OFF");
        Particle.publish("ballStatus", "8FLJ829");
        return 0;
    }
    else
    {
        Log.info("UNKNOWN OPTION");
        return -1;
    }
}
// Function called when the cloud tells us that an event is published.
void myHandler(const char *event, const char *data)
{
    if (strcmp(data, "SBH9905") == 0)
        {
            Log.info("Playing SBH9905");
        }
        else if (strcmp(data, "8FLJ829") == 0)
        {
            Log.info("Playing 8FLJ829");
        }
        else
        {
            Log.info("UNKNOWN OPTION in event");
        }
}
// setup() runs once, when the device is first turned on
void setup() {
    pinMode(MY_LED, OUTPUT);
    Particle.function("led", ledToggle);
    Particle.subscribe("ballStatus", myHandler);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  
  // Example: Publish event to cloud every 10 seconds. Uncomment the next 3 lines to try it!
   //Log.info("Sending Hello World to the cloud!");
   //Particle.publish("Hello world!");
   //delay( 10 * 1000 ); // milliseconds and blocking - see docs for more info!
}