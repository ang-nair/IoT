# IOT
# Dual-Axis Active Solar Tracking System

An Arduino-based dual-axis solar tracker that automatically aligns a solar panel directly towards the brightest light source. It uses four Light Dependent Resistors (LDRs) to detect light intensity and two servo motors to adjust the horizontal (azimuth) and vertical (elevation) angles.

## Features
* **Dual-Axis Tracking:** Moves both horizontally and vertically for maximum efficiency.
* **Ambient Light Calibration:** Includes logic to ignore ambient "ghost" light (baseline subtraction) for accurate tracking in different environments.
* **Anti-Jitter Mechanism:** Uses a customizable tolerance window to prevent the motors from twitching constantly.
* **Controlled Speed:** Motor movement is slowed down (150ms delay) to ensure smooth tracking and prevent mechanical stress.
* **Hardware Safety Limits:** Software limits prevent the servos from over-rotating and tearing the wires.

## Hardware Required
* 1x Arduino (Uno, Nano, etc.)
* 2x Servo Motors (Pan/Tilt mechanism)
* 4x LDRs (Light Dependent Resistors)
* 4x 10kΩ Resistors (for voltage dividers)
* 1x Solar Panel
* Central divider/shadow-caster (1 to 1.5 inches tall)
* Breadboard and jumper wires

## Circuit Connections

| Component | Arduino Pin |
| :--- | :--- |
| **Horizontal Servo** | Digital Pin 2 |
| **Vertical Servo** | Digital Pin 13 |
| **LDR: Top Left** | Analog A0 |
| **LDR: Bottom Left** | Analog A1 |
| **LDR: Bottom Right** | Analog A2 |
| **LDR: Top Right** | Analog A3 |

*Note: Ensure all LDRs are connected with 10kΩ pull-down resistors to GND.*

## Installation & Setup
1. Assemble the pan-tilt hardware with the LDRs separated by a central shadow-casting divider.
2. Clone this repository or download the `.ino` file.
3. Open the code in the Arduino IDE.
4. Adjust the calibration variables if necessary:
   * `tol`: Increase if the tracker jitters, decrease if it is not sensitive enough.
   * `dt`: Delay time in milliseconds. Change to adjust movement speed.
   * *Baseline Fix:* If your sensors read above `0` in a pitch-black room, update the `- 106` subtraction in the code to match your room's baseline reading.
5. Connect your Arduino and click **Upload**.

## Usage
Once powered, the tracker will initialize to its starting position (90° horizontal, 45° vertical), wait for 2.5 seconds, and then begin autonomously tracking the brightest light source. You can open the Arduino Serial Monitor (9600 baud) to view real-time sensor averages and motor positions for debugging.
