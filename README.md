# Access Emulator

A simple emulator to simulate Wiegand protocol data for testing access control systems. 
Ideal for developers or installers needing to validate access devices using Arduino or ESP32 boards.

## Getting Started

This project allows you to emulate a Wiegand-compatible access card or tag using a microcontroller.
It can be used to test access readers or debug systems before real deployment.

### Prerequisites

* Arduino (Uno, Nano, etc) or ESP32
* Wires
* Access control device (Wiegand controller)

### Installation

1. clone the repository
2. open the project file in Arduino IDE or ESP-IDF
3. connect a microcontroller to the PC via USB
4. upload code to the microcontroller
5. wire the microcontroller with access control device

## Usage

1. Customize the Wiegand bitstream and timing in the code if needed.
2. The emulator will send predefined Wiegand codes to your access device at regular intervals.

## Reference

1. [https://en.wikipedia.org/wiki/Wiegand_interface](https://en.wikipedia.org/wiki/Wiegand_interface)
2. [https://www.idesco.com/files/articles/HID%20-%20Understanding%20card%20formats.pdf]("Understanding Card Data Formats - Technology Basics White Paper" (PDF). HID Technology. 2006. Retrieved 14 February 2023.)
