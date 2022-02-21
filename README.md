# ESPNOW_RC_Car
SMARS inspired RC Car using ESPNOW to transmit signals from the remote control unit.

*Chassis_V2 v5.f3z*

![SMARS_Front2 (Small)](https://user-images.githubusercontent.com/31633408/154858392-5e5795cd-c237-4288-9b03-29d3a9e27979.JPG)

![SMARS_Front (Small)](https://user-images.githubusercontent.com/31633408/154858401-9d689487-f38e-4935-af7b-f4cb5bdc9f87.JPG)
![SMARS_Back (Small)](https://user-images.githubusercontent.com/31633408/154858432-4f8d7abb-6e49-4147-b6e9-5ac400514986.JPG)

## Credits
This project was inspired by the SMARS arduino car described at this website:  https://www.smarsfan.com/ 
Modifications were made to use and ESP based microcontroller to allow a simple remote control with minimal added hardware.  In addition, the wheels were redesigned to use an o-ring in place of the 3D printed tank treads.

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

Code reads the joystick input and sends it to the car.

### Car Code:  NodeMCUShield_HCSR04P_RCCar_Reciever.ino

Code recieves messages from the ESP32 and sends if forward to the motor driver to control direction and speed.  It also will beep the piezo speaker if the joystick button is pressed.  

## Hardware Used
### Car:

* ESP8266 V2.1 dev board / NodeMCU Motor Driver Board for V2

AliExpress:

![Hardware for Car (Small)](https://user-images.githubusercontent.com/31633408/154859309-e9f4c030-92cf-432e-9de8-466fb84d33d9.png)

* 2x N20 6V 200RPM-Gearmotor - https://www.ebay.com/itm/401942638877?hash=item5d95a5f11d:g:D0UAAOSw7qRdvGTe

![N20Gearmotor_EBAY (Small)](https://user-images.githubusercontent.com/31633408/154859640-fb53e11e-c439-4eb9-92da-47428377f409.png)

* 9V Li-ion rechargable battery:  https://smile.amazon.com/dp/B086GTFGPP?psc=1&smid=A3P4UZIS42PRQV&ref_=chk_typ_imgToDp

* 9V battery lead snap on connectors

### Remote Control:

*NRF_RC_Case_ESP32 v12.f3z*

![Remote (Small)](https://user-images.githubusercontent.com/31633408/154870419-98e65940-ab3a-4ba7-a9d4-0412f0565f24.JPG)

* Battery Shield - AliExpress:  https://www.aliexpress.com/item/4000770043723.html?spm=a2g0o.order_list.0.0.21ef18023Tfavs

![BatteryShield (Small)](https://user-images.githubusercontent.com/31633408/154859715-a21fea8a-552e-4508-8b71-5048c8dc13ff.png)

* Joystick - AliExpress:  https://www.aliexpress.com/item/1005003610311766.html?spm=a2g0o.productlist.0.0.4b3e36d0UGNpYe&algo_pvid=366d3246-338a-4e07-b809-91b7a615ca41&algo_exp_id=366d3246-338a-4e07-b809-91b7a615ca41-7&pdp_ext_f=%7B%22sku_id%22%3A%2212000026482774118%22%7D&pdp_pi=-1%3B8.35%3B-1%3B-1%40salePrice%3BUSD%3Bsearch-mainSearch

![Joystick](https://user-images.githubusercontent.com/31633408/154859898-225f9219-8ac5-4464-83e6-9c9e899687ce.png)

* ESP32 DevModule - AliExpress:  https://www.aliexpress.com/item/33005643254.html?spm=a2g0o.order_list.0.0.21ef1802H9bZsF

![ESP32DevModule (Small)](https://user-images.githubusercontent.com/31633408/154870682-14bb8aa2-2308-4b67-b38d-94db83824840.png)




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

