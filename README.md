# BlindHelpers-Stick
This project is (IoT)based on Blind helpers stick. A smart stick which helps the needy to fight daily life circumstances.
It includes IR, LDR, Water sensors, Buzzer and SOS button. IR sensor helps to measure the distances from any objects such as
walls,potholes,barriers tc. LDR sensor helps to know whether the area is lighted or not, moreover it also detects smoke in the
surroundings caused by any means. Water sensor will be useful in alerting the presence of water level in potholes.
Ultimately the stick is installed with SOS button, which when pressed will alert the needy's family members by sending them an
alert notification through email.
These features are achieved using simple Arduino board and its microcontroller. Arduino is integrated with all these sensors 
including WiFi module which sends the threshold data value to the cloud platform ThingSpeak. When a certain limit is crossed 
then IFTTT applet is triggered which then triggers an email notification.
