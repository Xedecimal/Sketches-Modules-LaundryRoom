// SERIAL WRITING OUTPUT WILL BREAK EVERYTHING NEVER DO IT!

#define SKETCH_NAME "ModuleLaundryRoom"
#define SKETCH_VERSION "1.0"
#define MY_BAUD_RATE 115200
#define MY_NODE_ID 41

// #define NODEMANAGER_SLEEP OFF
// #define NODEMANAGER_OTA_CONFIGURATION ON
// #define NODEMANAGER_DEBUG ON
// #define NODEMANAGER_CONDITIONAL_REPORT ON

#include <XMySensors/XMySensors.h>
#include <MySensors_NodeManager.h>

#include <sensors/SensorLDR.h>
SensorLDR ldr(A1);

#include <sensors/SensorMQ.h>
SensorMQ mq(A2);

#include <sensors/SensorRelay.h>
SensorRelay fan(5);

#include <sensors/SensorDoor.h>
SensorDoor door(3);

#include <sensors/SensorDHT11.h>
SensorDHT dht(4);

bool inited = false;

void before()
{
	fan.setInvertValueToWrite(ON);
	// Stop relay from triggering on boot.
	digitalWrite(5, HIGH);
	nodeManager.setReportIntervalSeconds(10);
	nodeManager.before();
}

void setup()
{
	nodeManager.setup();
}

void presentation()
{
	nodeManager.presentation();
}

void loop()
{
	// Must send all values at least once for HASS to show them.
	if (!inited) {
		// Light
		send(MyMessage(1, V_LIGHT_LEVEL).set(0));
		// MQ
		send(MyMessage(2, V_LEVEL).set(0));
		send(MyMessage(3, V_LEVEL).set(0));
		send(MyMessage(4, V_LEVEL).set(0));
		// Relay Fan
		send(MyMessage(5, V_STATUS).set(0));
		// Door
		send(MyMessage(6, V_TRIPPED).set(0));
		// Temperature
		send(MyMessage(7, V_TEMP).set(0));
		// Humidity
		send(MyMessage(8, V_HUM).set(0));

		inited = true;
	}
	nodeManager.loop();
}

void receive(const MyMessage &message)
{
	nodeManager.receive(message);
}
