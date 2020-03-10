#define WIFI_NAME "----------WI-FI-------------"
#define WIFI_PASSWORD "----password-WI-FI------"
#define DEVICE_ID 8
#define DEVICE_NAME "-------------"
#define TOKEN "----------------"


#include <RemoteMe.h>
#include <RemoteMeSocketConnector.h>

#include <ESP8266WiFi.h>


RemoteMe& remoteMe = RemoteMe::getInstance(TOKEN, DEVICE_ID);

//*************** CODE FOR COMFORTABLE VARIABLE SET *********************

inline void setLed(boolean b) {remoteMe.getVariables()->setBoolean("restart", b); }

//*************** IMPLEMENT FUNCTIONS BELOW *********************

void onLedChange(boolean b) {
	Serial.printf("onLedChange: b: %d\n",b);
	digitalWrite(D1, b?HIGH:LOW);
}


void setup() {
	Serial.begin(9600);
	pinMode(D1, OUTPUT);
	  
	WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

	while (WiFi.status() != WL_CONNECTED) {
		delay(100);
	}

	remoteMe.getVariables()->observeBoolean("restart" ,onLedChange);
	remoteMe.setConnector(new RemoteMeSocketConnector());
	remoteMe.sendRegisterDeviceMessage(DEVICE_NAME);
}


void loop() {
	remoteMe.loop();
}
