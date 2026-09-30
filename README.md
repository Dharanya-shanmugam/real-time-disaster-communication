# Real-Time Disaster Communication and Priority Handling System

A real-time emergency communication and priority handling system implemented using μT-Kernel 3.0 on the Renesas EK-RA8P1 microcontroller platform.

## Overview

This project accepts disaster reports from a smartphone, classifies them into emergency categories, assigns priorities, transmits the information over Ethernet, and processes the messages using a priority mailbox on the EK-RA8P1.

The demonstrated priority levels are:

| Disaster Category | Priority |
|---|---:|
| FIRE | 1 |
| MEDICAL | 2 |
| ROAD | 3 |
| NORMAL | 4 |

Lower priority number indicates higher urgency.

## System Architecture

```text
Smartphone
    |
    v
Flask Web Interface
(phone_server.py)
    |
    v
Disaster Classification
(disaster_ai.py)
    |
    v
Priority Assignment
    |
    v
Scapy Ethernet Transmission
    |
    v
Renesas EK-RA8P1 RMAC
    |
    v
μT-Kernel 3.0
    |
    v
Priority Mailbox
    |
    v
Tera Term Alert Output
Key Features
Real-time disaster message handling
Priority-based emergency dispatch
FIRE, MEDICAL, ROAD and NORMAL categories
Smartphone-based message submission
Local network communication
Ethernet communication with EK-RA8P1
μT-Kernel 3.0 priority mailbox processing
Tera Term alert output
Internet/cloud-independent communication pipeline
Demonstration on real Renesas EK-RA8P1 hardware
Hardware Requirements
Renesas EK-RA8P1
Windows PC/Laptop
Smartphone
USB Ethernet adapter
Ethernet cable
J-Link/programming connection
USB connection for serial communication
Software Requirements
e² studio
Renesas FSP
μT-Kernel 3.0
Python 3.12.9
Flask
Scapy
Tera Term
PC-Side Software
phone_server.py

Provides the Flask-based web interface through which a smartphone can submit disaster messages to the PC.

disaster_ai.py

Processes the received disaster message, determines the disaster category and assigns the corresponding priority.

The current implementation uses deterministic rule-based classification.

μT-Kernel Application

The embedded application runs on the Renesas EK-RA8P1 using μT-Kernel 3.0.

The received Ethernet data is processed and placed into the priority-based mailbox. The RTOS then handles the messages according to their assigned priority.

Setup and Operation
1. Build and Program the EK-RA8P1

Open the project in e² studio, build the project and program it to the Renesas EK-RA8P1.

2. Start Tera Term

Connect Tera Term to the serial interface of the EK-RA8P1.

3. Start the Flask Server
python phone_server.py
4. Start the Disaster Classifier
python disaster_ai.py
5. Connect the Smartphone

Connect the smartphone and PC to the same local Wi-Fi/LAN network.

Open:

http://<PC-IP>:5000
6. Submit a Disaster Message

The message is:

Received by the PC
Classified
Assigned a priority
Transmitted through Ethernet
Received by the EK-RA8P1
Processed using the μT-Kernel priority mailbox
Displayed as an alert through Tera Term
Example

Input:

Ohh no fire

Expected classification:

Category : FIRE
Priority : 1
Priority Demonstration

A NORMAL message can be submitted first followed by a FIRE message.

Although the NORMAL message arrives earlier, the priority-based processing allows the FIRE message to be dispatched before the NORMAL message.

Test Cases
Test Case	Input Category	Expected Priority
TC01	FIRE	1
TC02	MEDICAL	2
TC03	ROAD	3
TC04	NORMAL	4
Repository Structure
real-time-disaster-communication/
│
├── disaster_ai.py
├── phone_server.py
│
├── docs/
│   └── TRON_Contest_Documentation.docx
│
├── presentation/
│   └── TRON_Contest_Presentation.pptx
│
├── src/
├── ra/
├── ra_cfg/
├── ra_gen/
├── script/
├── mtk3_bsp2/
│
├── .project
├── .cproject
└── configuration.xml
Limitations
Current disaster classification is rule-based and keyword-driven.
Only four priority levels are currently implemented.
The system has not been load-tested for large-scale concurrent traffic.
Authentication and encryption are not currently implemented.
The system requires the USB Ethernet adapter and configured local network connection.
Future Improvements

Future development can extend the current classification module with machine-learning or LLM-based classification while keeping the real-time priority processing on the μT-Kernel side isolated and deterministic.

Additional improvements can include secure communication, authentication, larger-scale load testing and additional emergency categories.

Documentation

Detailed system architecture, hardware/software requirements, operation procedure, test cases and troubleshooting information are provided in:

docs/TRON_Contest_Documentation.docx

The contest presentation is available in:

presentation/TRON_Contest_Presentation.pptx

Platform
RTOS: μT-Kernel 3.0
Target Hardware: Renesas EK-RA8P1
Development Environment: e² studio
Host OS: Windows
Communication: Ethernet / Local Network
