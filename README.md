# Universal_temp_sensor
univeral temperature sensor for various resistance and thermocoupler  sensors  using ADS1115


A universial  temperature sensor reader for  many kinds of sensors in both resistance and  thermocouplers varieties 
works with  PT1000. NTC 10k and type K  that I have tried personally . but it should work with PT500 and PT100. plus various other  thermocouplers 

for resistance  type  just look up the resistance table of your sensor 
 add 3 different  temperatures and resistance from the chart  into this  

Steinhart-Hart Coefficients Calculator

http://www.nonmetalhail.com/projects/thermistor/themistor.html


for thermocoupler you will  manulaly have to determine  the values 
- enable thermocouple in the sketch and  hook it up as described here 

https://community.openenergymonitor.org/t/universal-temp-sensor-sketch-works-with-resistance-devices-ntc-ptxxx-and-thermocouples-typek-and-probably-others/19910

manual take three temperture reads  and  mark down the temperature and the Psuedo restance it had which is displayed in   displayed in the serial monitor 

once you have 3 tempertures and psuedo resistance  reads  ( the greater the spacing  between the temperatures the better  especially for the Type k )


enter them in to the Steinhart-Hart Coefficients Calculator mentioned above   and enter  those  A,B,C section  in the sketch 
