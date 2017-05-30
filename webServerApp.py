#	IMPORT STATEMENTS
from flask import Flask, render_template, request, redirect, url_for
import serial
import struct
import time

#	DEFINE GLOBALS
output0 = 0	 #R
output1 = 0 	 #G
output2 = 255	 #B
output3 = 0 	 #W

#	DEFINE SET COLOR FUNCTION
def setArduinoColor(colorInput):
	#	CONVERT HEX COLOR TO RGB
	value = colorInput.lstrip('#')
	lv = len(value)
	output0 = int(value[0:2],16)
	output1 = int(value[2:4],16)
	output2 = int(value[4:6],16)

	#	NORMALIZE RGB TO INCLUDE W
	normalize = min(output0,output1,output2)
	output3 = normalize
	output0 = output0 - normalize
	output1 = output1 - normalize
	output2 = output2 - normalize

	#	SEND COLOR TO ARDUINO
	ser.write(struct.pack('>4B',output0,output1,output2,output3))
	ser.close()
	return

#	INITIALIZE SERIAL BUS
try:
	ser = serial.Serial('/dev/ttyACM0') #OPEN SERIAL PORT
	ser.baudrate = 9600
except Exception as e:
	print(e)

#	INITIALIZE FLASK WEB SERVER
app = Flask(__name__)

@app.route('/', methods = ['POST', 'GET'])

def index():
	colorInput = '#ff0000'
	if request.method == 'POST':
		colorInput = request.form['color']
		print(setArduinoColor(colorInput))
		return render_template('index.html', color=colorInput)
	return render_template('index.html', color=colorInput)

if __name__ == "__main__":
	app.run(host='0.0.0.0')
