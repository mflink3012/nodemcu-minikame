#include <Arduino.h>
#include <map>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoOTA.h>
#include <Ticker.h>
#include "include/KameRobotConfig_MSG90.h"
#include "include/KameRobot.h"
#include "include/KameRobotBehavior.h"
#include "include/KameRobotBehavior_ServosEnable.h"
#include "include/KameRobotBehavior_ServosDisable.h"
#include "include/KameRobotBehavior_ServosCenter.h"
#include "include/KameRobotBehavior_CalibrationPose.h"
#include "include/KameRobotBehavior_BodyLiftUp.h"
#include "include/KameRobotBehavior_BodyLiftDown.h"
#include "include/KameRobotBehavior_BodyCenterH.h"
#include "include/KameRobotBehavior_BodyCenterV.h"
#include "include/KameRobotBehavior_LegsWalkForward.h"
#include "include/KameRobotBehavior_LegsWalkBackward.h"
#include "include/KameRobotBehavior_LegsAlignRtl.h"
#include "include/KameRobotBehavior_LegsAlignFtb.h"
#include "wificonfig.h"

const uint16_t WEBSERVER_PORT = 80;

AsyncWebServer webserver(WEBSERVER_PORT);
KameRobotConfig_MSG90 robotConfig;
KameRobot robot;

std::map<String, KameRobotBehavior*> behaviors = {
    { "servos/enable", new KameRobotBehavior_ServosEnable(&robot) },
    { "servos/disable", new KameRobotBehavior_ServosDisable(&robot) },
    { "servos/center", new KameRobotBehavior_ServosCenter(&robot) },
    { "calibration/pose", new KameRobotBehavior_CalibrationPose(&robot) },
    { "legs/walk/forward", new KameRobotBehavior_LegsWalkForward(&robot) },
    { "legs/walk/backward", new KameRobotBehavior_LegsWalkBackward(&robot) },
    { "legs/align/r2l", new KameRobotBehavior_LegsAlignRightToLeft(&robot) },
    { "legs/align/f2b", new KameRobotBehavior_LegsAlignFrontToBack(&robot) },
    { "body/lift/up", new KameRobotBehavior_BodyLiftUp(&robot) },
    { "body/lift/down", new KameRobotBehavior_BodyLiftDown(&robot) },
    { "body/center/h", new KameRobotBehavior_BodyCenterH(&robot) },
    { "body/center/v", new KameRobotBehavior_BodyCenterV(&robot) }
};

bool isWebserverInitialized = false;
bool isOTAInitialized = false;
unsigned long previousMillis = 0;
Ticker networkTicker;

void initNetwork();
void demo();

class KameRobotUrlHandler : public AsyncWebHandler {
    public:
        KameRobotUrlHandler() : AsyncWebHandler() {}
        virtual ~KameRobotUrlHandler() {}

        bool canHandle(AsyncWebServerRequest *request) override {
            return true;
        }

        void handleRequest(AsyncWebServerRequest *request) override {
            AsyncResponseStream *response = request->beginResponseStream("text/html");
            //Serial.printf("Requested URL: %s\n", request->url().c_str());
            std::map<const String, AsyncWebParameter*> params;
            for (size_t i = 0; i < request->params(); ++i) {
                params.insert(params.end(), std::pair<String, AsyncWebParameter*>(request->getParam(i)->name(), request->getParam(i)));
            }

            if ((request->url().length() > 1) && (behaviors.find(request->url().substring(1)) != behaviors.end())) {
                if (request->hasParam("v")) {
                    behaviors[request->url().substring(1)]->run(&params["v"]->value());
                } else {
                    behaviors[request->url().substring(1)]->run();
                }
                
            } else if (request->url().compareTo("/") != 0) {
                response->setCode(501); // Not implemented
            } else {
                response->print("<!DOCTYPE html><html><head><title>Mini-Kame Documentation</title></head><body>");
                response->print("<h1>Mini-Kame Documentation</h1><dl>");

                for (std::map<String, KameRobotBehavior*>::iterator it = behaviors.begin(); it != behaviors.end(); ++it) {
                    response->printf("<dt><a href=\"http://%s/%s\">%s</a></dt><dd>%s</dd>",
                        request->host().c_str(),
                        it->first.c_str(),
                        it->second->getName().c_str(),
                        it->second->getDescription().c_str()
                    );
                }

                response->print("</dl></body></html>");
            }

            request->send(response);
        }
};

void setupOTA() {
    // Hostname defaults to esp8266-[ChipID]
    ArduinoOTA.setHostname("minikame");

    ArduinoOTA.onStart([]() {
        if (ArduinoOTA.getCommand() == U_FLASH) {
            //Serial.println("Start updating flash ...");
        } else { // U_SPIFFS
            // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
            //Serial.println("Start updating filesystem ...");
        }
        behaviors["servos/disable"]->run();
    });
    ArduinoOTA.onEnd([]() {
        //Serial.println("\nUpdate finished.");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        //Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        //Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) {
            //Serial.println("Auth Failed");
        } else if (error == OTA_BEGIN_ERROR) {
            //Serial.println("Begin Failed");
        } else if (error == OTA_CONNECT_ERROR) {
            //Serial.println("Connect Failed");
        } else if (error == OTA_RECEIVE_ERROR) {
            //Serial.println("Receive Failed");
        } else if (error == OTA_END_ERROR) {
            //Serial.println("End Failed");
        }
    });
}

void setup() {
    //Serial.begin(115200);

    robot.init(robotConfig);
    behaviors["servos/enable"]->run();
    behaviors["body/lift/up"]->run();

    WiFi.mode(WIFI_STA);

    webserver.addHandler(new KameRobotUrlHandler());

    setupOTA();

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    networkTicker.attach_ms(3000, initNetwork);
}

void connectWiFi() {
    if (WiFi.status() != WL_CONNECTED) {
        digitalWrite(LED_BUILTIN, HIGH);
        //Serial.printf("Trying to connect to WiFi-AP '%s'\n", WIFI_SSID);
        isWebserverInitialized = false;
        isOTAInitialized = false;
        WiFi.begin(WIFI_SSID, WIFI_PASSWD);
    } else if (WiFi.status() == WL_CONNECTED) {
        digitalWrite(LED_BUILTIN, LOW);
    }
}

void enableWebserver() {
    if (WiFi.status() == WL_CONNECTED && !isWebserverInitialized) {
        webserver.begin();
        //Serial.printf("Started webserver at http://%s:%i/\n", WiFi.localIP().toString().c_str(), WEBSERVER_PORT);
        isWebserverInitialized = true;
    }
}

void enableOTA() {
    if (WiFi.status() == WL_CONNECTED && !isOTAInitialized) {
        ArduinoOTA.begin();
        //Serial.println("Enabled ArduinoOTA.");
        isOTAInitialized = true;
    }
}

void initNetwork() {
    connectWiFi();
    enableOTA();
    enableWebserver();
}

long lastMillis = 0;

void loop() {
    if (isOTAInitialized) {
        ArduinoOTA.handle();
    }

    long currentMillis = millis();

    if (currentMillis - lastMillis > robotConfig.getStepDuration()) {
        // TODO: Put this into a pattern to let the behaviors decide themself - they know better ;)
        if (robot.getState() == ROBOT_STATES::WALK_FORWARD) {
            behaviors["legs/walk/forward"]->run();
        } else if (robot.getState() == ROBOT_STATES::WALK_BACKWARD) {
            behaviors["legs/walk/backward"]->run();
        }
        lastMillis = millis();
    }
}
