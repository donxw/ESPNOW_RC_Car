# ESPNOW_RC_Car
SMARS inspired RC Car using ESPNOW to transmit signals from the remote control unit.

*Chassis_V2 v5.f3z*

![SMARS_Front2 (Small)](https://user-images.githubusercontent.com/31633408/154858392-5e5795cd-c237-4288-9b03-29d3a9e27979.JPG)

![SMARS_Front (Small)](https://user-images.githubusercontent.com/31633408/154858401-9d689487-f38e-4935-af7b-f4cb5bdc9f87.JPG)

## Credits
This project was inspired by the SMARS arduino car described at this website:  https://www.smarsfan.com/ 

Modifications were made to use ESP based microcontrollers for RC wireless signal communication using the ESPNOW protocol. This minimized any addtional hardware by using the built in wireless capabilities of the ESP boards.  

Additionally, the wheels were redesigned to use an o-ring in place of the 3D printed tank treads.

## Libraries Used
espnow.h - here is the tutorial I used:  https://randomnerdtutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
The car uses the ESP8266 commands and the Remote Control uses the ESP32 commands

No library is needed for the NodeMCU motor driver board.  The motor driver is an L293D controlled as follows:

*Motor A*
*   Direction A - Pin 0 (D3) - Boolean 0 or 1 to change direction
*   PWM A - Pin 5 (D1) - PWM 0-255 for speed

*Motor B*
*   Direction B - Pin 2 (D4) - Boolean 0 or 1 to change direction
*   PWM B - Pin 4 (D2) - PWM 0-255 for speed

## Software

### Remote Control Code: ESP32_Sender_JoystickRemote.ino

Arduino board:  ESP32 Dev Module
Code reads the joystick input and sends it to the car.

### Car Code:  NodeMCUShield_HCSR04P_RCCar_Reciever.ino

Arduino board:  NodeMCU 1.0 (ESP-12E Module)
Code recieves messages from the ESP32 and sends if forward to the motor driver to control direction and speed.  It also will beep the piezo speaker if the joystick button is pressed.  If the ultrasonic sensor detects an object in front of it, a routine backs the car up and turns it.

### MAC Address and Joystick Null 

* Program the car first (ESP8266).  Run the program and note in the serial port window what the MAC Address is.  Use this in the code for the Joystick remote control code.
* Program the remote control (ESP32).  Use the MAC address from the ESP8266.  Run the remote code and note in the serial port window the values that are being transmitted when the joystick is in the null position.
* Go back to the car code (ESP8266) and update the joystick x and y null points (valX_center, valY_center), then reprogram the car.  Turn on the joystick and watch the serial port window to assure it is recieving signals.  Tweak the null points as needed so the car is quiet when the joystick is in the neutral position.  Assure the wheels react properly to forward, back, left and right joystick.

## Hardware Used
### Car:

* ESP8266 V2.1 dev board / NodeMCU Motor Driver Shield for V2
* Good tutorial for the Shield:  https://hackaday.io/project/8856-incubator-controller/log/29291-node-mcu-motor-shield/

AliExpress:

![Hardware for Car (Small)](https://user-images.githubusercontent.com/31633408/154859309-e9f4c030-92cf-432e-9de8-466fb84d33d9.png)

* 2x N20 6V 200RPM-Gearmotor - https://www.ebay.com/itm/401942638877?hash=item5d95a5f11d:g:D0UAAOSw7qRdvGTe

![N20Gearmotor_EBAY (Small)](https://user-images.githubusercontent.com/31633408/154859640-fb53e11e-c439-4eb9-92da-47428377f409.png)

* Foam double stick tape to mount motor:  https://smile.amazon.com/gp/product/B07X6D1BZL/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1
* 1/16" neoprene self stick foam for vibration isolation of motor sides.

Padding added to N20 Motors:
![N20Motor_wPads (Small)](https://user-images.githubusercontent.com/31633408/155830298-f5caad34-54e4-4328-8d17-270b73a4433b.png)

Assemble N20 Motor to chassis and attach drive wheels:
![DriveWheels (Small)](https://user-images.githubusercontent.com/31633408/155866001-fc10577a-08ad-44d3-bd79-233628bfd824.png)

Assemble idler wheels to chassis:
![IdlerWheels (Small)](https://user-images.githubusercontent.com/31633408/155866088-3e11dcf2-f961-4e6c-8807-f3cc159a38aa.png)

Add battery door and insert 9v rechargable LiPo into the chassis:
![AddBattery (Small)](https://user-images.githubusercontent.com/31633408/155901151-37bfc5f9-eba4-4cec-b71b-7a48230eca22.png)

Add buzzer and ultrasonic sensor:
![AddBuzzer UltrasonicSensor (Small)](https://user-images.githubusercontent.com/31633408/155901176-cd845f0d-e57d-4e06-9d21-fedb42293b11.png)

Assemble NodeMCU and MotorDriverboard to the adapter:
![AssembleCPUtoAdapter (Small)](https://user-images.githubusercontent.com/31633408/155901205-b3a74923-6b38-4f60-b036-e825a29fbecd.png)

Merge CPU adapter to chassis.  Tabs on adapter board slide into the slots on the Chassis:
![MergeCPUtoChassis (Small)](https://user-images.githubusercontent.com/31633408/155901245-38da55ac-c93b-4234-b331-28e894cc3180.png)

For wiring, see below.

* 9V Li-ion rechargable battery:  https://smile.amazon.com/dp/B086GTFGPP?psc=1&smid=A3P4UZIS42PRQV&ref_=chk_typ_imgToDp

* 9V battery lead snap on connectors:  https://fr.aliexpress.com/item/4000015248753.html?spm=a2g0o.productlist.0.0.38679564Jqvdul&algo_pvid=80b28aa7-96e6-4de4-bc11-f2a06a7ae6fc&algo_exp_id=80b28aa7-96e6-4de4-bc11-f2a06a7ae6fc-7&pdp_ext_f=%7B%22sku_id%22%3A%2210000000036741911%22%7D&pdp_pi=-1%3B5.69%3B-1%3B-1%40salePrice%3BUSD%3Bsearch-mainSearch

* O-Rings used: 3mm x 70mm ID - https://www.mcmaster.com/o-rings/width~3-000mm/
* Ultrasonic Sensor:  HC-SR04P 3.3-5v version - https://www.aliexpress.com/item/1893557869.html?spm=a2g0o.productlist.0.0.41fb7eb4Qc5DIU&algo_pvid=9188cb53-b11d-4924-a6ab-ea4a412cd662&algo_exp_id=9188cb53-b11d-4924-a6ab-ea4a412cd662-0&pdp_ext_f=%7B%22sku_id%22%3A%2256091531014%22%7D&pdp_pi=-1%3B0.49%3B-1%3B-1%40salePrice%3BUSD%3Bsearch-mainSearch



### Remote Control:

*NRF_RC_Case_ESP32 v12.f3z*

![RCTransmitterCase (Small)](https://user-images.githubusercontent.com/31633408/156890848-7cf3f4e1-f651-4b78-aecb-2f8a16165dea.png)

* Battery Shield - AliExpress:  https://www.aliexpress.com/item/4000770043723.html?spm=a2g0o.order_list.0.0.21ef18023Tfavs

![BatteryShield (Small)](https://user-images.githubusercontent.com/31633408/154859715-a21fea8a-552e-4508-8b71-5048c8dc13ff.png)

* Joystick - AliExpress:  https://www.aliexpress.com/item/1005003610311766.html?spm=a2g0o.productlist.0.0.4b3e36d0UGNpYe&algo_pvid=366d3246-338a-4e07-b809-91b7a615ca41&algo_exp_id=366d3246-338a-4e07-b809-91b7a615ca41-7&pdp_ext_f=%7B%22sku_id%22%3A%2212000026482774118%22%7D&pdp_pi=-1%3B8.35%3B-1%3B-1%40salePrice%3BUSD%3Bsearch-mainSearch

![Joystick](https://user-images.githubusercontent.com/31633408/154859898-225f9219-8ac5-4464-83e6-9c9e899687ce.png)

* ESP32 DevModule - AliExpress:  https://www.aliexpress.com/item/33005643254.html?spm=a2g0o.order_list.0.0.21ef1802H9bZsF

![ESP32DevModule (Small)](https://user-images.githubusercontent.com/31633408/154870682-14bb8aa2-2308-4b67-b38d-94db83824840.png)

### Wiring
ESP32 and NodeMCU pin-outs can be found here:  https://randomnerdtutorials.com/

*Car - ESP8266 NodeMCU V2*

// Ultrasonic sensor
* trigger = GPIO 10  //SD3
* echoPin = GPIO 9  //SD2
* VCC = 3.3V
* Ground = GND

// Piezo buzzer
* buzzer + = GPIO 15  //D8
* buzzer - = GND

// 9V battery
* Positive to Motor Shield Vin (Power to Arduino)
* Negative to Motor Shield Gnd
* Jumper VM to VIN (Common Power to NodeMCU and Motor)

![SMARS_Top](https://user-images.githubusercontent.com/31633408/155014446-86ab87a4-6f71-417b-b213-48ac07698e6a.JPG)

![MotorDriverBoardPinout](https://user-images.githubusercontent.com/31633408/155901710-365a457b-1200-4539-8ff0-1ae5e9ea32b3.png)
![wiring](https://user-images.githubusercontent.com/31633408/155016361-c054e04d-26e8-4b5f-9e44-23a4b1a1fbbe.png)


*RC Unit - ESP32 DevModule*

// Joystick
* Joystick Val Y = GPIO 32
* Joystick Val X = GPIO 33
* Joystick Button = GPIO 27
* Joystick +5V = 3.3v
* Joystick GND = GND

// Battery holder
* Battery 5v = Vin

![WiringRCTransmitter](https://user-images.githubusercontent.com/31633408/156891658-d15bd741-c623-428a-8ecb-e2d937791b42.png)






# 
MIT License

Copyright (c) 2022 Don Williams

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

