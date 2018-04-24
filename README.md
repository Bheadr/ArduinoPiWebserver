# ArduinoPiWebserver
This project uses a Raspberry pi to host a web server using Python Flask. It provides a user input to select a color. The pi communicates to an Arduino which controls a 240 RGBW Neopixel clone LED strip. 

Arduino Pin 9 is connected to the first neopixel in the string and then all 240 LEDs are cascaded from the first pixel using the shift register. The python script is smart enough to extract the Red Green and Blue components of the selected color and convert that to White. This normalizes the color (grey is a reduced white, pink is red plus white, etc) and allows the White LED to be used. 
