# Power-Surveillance-Project
This Arduino UNO project involves using a SIM800H module for power surveillance and sending SMS alerts in case of a power outage or restoration. 

Hardware Connections:
SIM800H Module:

•	BAT: Not connected (NC).

•	GND: Connected to Arduino UNO GND.

•	+SPKR and -SPKR: Not connected (NC).

•	RST: Not connected (NC).

•	PS: Connected to a blue LED (+) with the other end of the LED (-) connected to a power source on the Arduino UNO.

•	Key: Connected to a push button which is connected to a common ground (COM) on the Arduino.

•	RI: Not connected (NC).

•	TX: Connected to Digital PWM pin 3 on Arduino UNO.

•	RX: Connected to Digital PWM pin 2 on Arduino UNO.

•	NS: Not connected (NC).

•	VIO: Connected to a diode 1N4001, then to 5V on Arduino UNO.

Relay Module KY019RM:

•	Signal: Connected to the 5V pin on SIM800H.

•	+V: Connected to +5V on Arduino.

•	GND: Connected to GND on Arduino.

•	Normal Close contact: Connected to PWM pin D10 on Arduino UNO.

•	COM: Connected to +5V on Arduino.


The code includes the necessary libraries and initializes the components:

	Libraries:
 
o	Adafruit_FONA.h: For interfacing with the SIM800H module.

o	Wire.h: For I2C communication.

o	LiquidCrystal_I2C.h: For the LCD display.

o	Timers.h: For timer functionality.


	LCD Initialization:
LiquidCrystal_I2C lcd(0x27, 20, 4);

	Global Variables:
 
o	S1: Digital pin 10, connected to the relay contact.

o	S2: Digital pin 11, connected to a reset button.

o	D1: Digital pin 12, connected to an LED.

o	StatusS1: Status of S1, initially LOW.

o	StatusS2: Status of S2, initially LOW.

o	t1, t2, t3: Timer variables.

o	replybuffer: Buffer for storing replies from the SIM800H module.

o	fonaSerial: Serial communication object for SIM800H.

o	fona: FONA object for controlling the SIM800H module.


Setup Function:

o	Initializes the LCD.

o	Sets pin modes for S1 and D1.

o	Initializes serial communication at 115200 baud rate.

o	Initializes the SIM800H module at 4800 baud rate.

o	Prints module information and IMEI to the serial monitor and LCD.



Loop Function:

o	Continuously checks the status of S1.

o	If S1 is HIGH (indicating power outage) and the timer t1 is less than 1, unlocks the SIM card and sends an alarm SMS about the power outage.

o	If S1 remains HIGH and t1 is less than 3, sends another SMS alert
.
o	If S1 goes LOW (indicating power restoration) and t1 is greater than 0, sends an SMS indicating power is back and resets the timer.


Functional Analysis:

•	Power Outage Detection: When the relay contact (S1) detects a power outage (S1 goes HIGH), the system unlocks the SIM card and sends an SMS alert.

•	Repeated Alerts: If the outage persists, it sends additional alerts up to a certain limit (t1 < 3).

•	Power Restoration Detection: When power is restored (S1 goes LOW), it sends an SMS indicating that power is back and resets the timer (t1).


Summary:

This setup and code are designed to monitor power status and use the SIM800H module to send SMS alerts in case of a power outage or restoration. The hardware connections are straightforward, with the relay module and SIM800H connected to the Arduino UNO, and the code handles the logic for detecting power changes and sending alerts. The use of the LCD display provides real-time feedback on the system status.

Power Outage Detection:

The status of S1 is checked. If S1 is HIGH (indicating a power outage) and the timer t1 is less than 1, the SIM card is unlocked, and an SMS alert is prepared to be sent.

If S1 remains HIGH and t1 is less than 3, additional SMS alerts are sent.

The LED (D1) is used to indicate the sending status.


Power Restoration Detection:

The status of S1 is checked again. If S1 is LOW (indicating power restoration) and t1 is greater than 0, an SMS indicating that power is back is sent.

The timer t1 is reset after sending the SMS.

