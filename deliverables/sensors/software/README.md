# PeaPod Arduino Software
 
Includes all libraries and code for PeaPod's Arduino Micro.

## References

Todo.

# Development

## Requirements

- Arduino IDE

## Uploading

Open the [main sketch](./PeaPod-Arduino.ino) in the Arduino IDE. Connect the PeaPod Arduino Micro to your computer. Select Arduino Micro as the board. Select the appropriate serial port.

Verify, then upload the sketch.

## Interfacing

Open the Arduino IDE Serial Monitor (Tools > Serial Monitor). To start the PeaPod's data gathering, send it a valid "Instruction Set" JSON-formatted string where each key-value pair is an Instruction.

The currently supported Instructions are:
- Scale calibration: `"scale":weight`, i.e. `"scale":0` to tare
