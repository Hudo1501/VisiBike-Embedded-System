# VisiBike: Smart Bicycle Embedded Signaling System

## Overview
VisiBike is a modular embedded system designed to be easily mounted on bicycles, significantly improving rider safety through enhanced visibility and signaling capabilities. This project bridges the gap between software logic and hardware execution, utilizing the Mbed platform to process rider inputs and control physical lighting circuits in real-time.

## Tools & Technologies
* **Platform & Framework:** Mbed OS
* **Programming Language:** C/C++
* **Microcontroller:**  STM32 Nucleo
* **Hardware Prototyping:** Breadboard, Jumper Wires
* **Components:** [Nhập linh kiện thực tế, ví dụ: Push Buttons, Red/Yellow LEDs, Resistors...]

## System Architecture & Firmware Logic
The core of VisiBike revolves around a control logic written in C/C++ that manages inputs and timing functions without blocking the main execution loop.
* **Inputs:** Rider intent is captured via tactile switches (e.g., for left/right turns or braking). Hardware debouncing and software polling/interrupt techniques were implemented to ensure signal reliability.
* **Processing:** The Mbed microcontroller processes these inputs to determine the current signaling state (e.g., Idle, Turning Left, Turning Right, Warning).
* **Outputs:** The GPIO pins drive the corresponding LED arrays to visually communicate the rider's intent clearly to surrounding traffic.

*(Paste your block diagram or software flowchart image here)*
![System Architecture](link_anh_so_do_khoi_cua_ban.png)

## Hardware Implementation (Breadboard Prototype)
Before committing to a physical PCB, the circuit was successfully assembled and verified on a breadboard. The implementation focused on correct GPIO interfacing, managing power distribution for multiple LED indicators, and ensuring robust wiring for a dynamic, vibration-prone environment like a moving bicycle.

*(Paste your breadboard circuit images here)*
![Breadboard Prototype](link_anh_mach_breadboard_thuc_te.png)

## My Contribution
Working within a 5-member cross-functional team, my core responsibilities included:
* **Firmware Development:** Writing and debugging the C/C++ control logic using the Mbed compiler.
* **Hardware Prototyping:** Wiring the breadboard circuit and interfacing the Mbed microcontroller with external input/output peripherals.
* **System Integration:** Validating the communication between software commands and hardware responses to ensure zero-latency signaling.
