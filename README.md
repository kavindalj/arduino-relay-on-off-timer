# Arduino Relay On/Off Timer with DS3231 RTC

This Arduino-based relay timer uses a DS3231 RTC module to control a relay module according to preset on/off times. It features an LCD display for time visualization and user input via push buttons to modify settings. The EEPROM stores relay on/off schedules for persistence across power cycles.

## Features

- Uses a **DS3231 RTC module** for accurate timekeeping.
- **Controls a relay module** for scheduled switching.
- **LCD display (LiquidCrystal)** to show the current time and relay status.
- **4 push buttons** (+, -, Set, Mode) to adjust the relay on/off schedule.
- **Stores up to 10 relay on/off times** in EEPROM.
- **Designed for store signboard lighting control** to save power by turning off at unnecessary hours.
- **Implemented in a real-world store** to automate lighting control.

## Hardware Requirements

- Arduino board (e.g., Arduino Uno, Nano, etc.)
- DS3231 RTC module
- Relay module
- 16x2 LCD display
- 4 push buttons (+, -, Set, Mode)
- EEPROM (built-in Arduino memory used)
- Power supply suitable for your relay and load
- Connecting wires

## Code Overview

The main functionalities include:

- Reading **real-time clock (RTC) data** from the DS3231.
- Displaying the time and configs on the **LCD screen**.
- **Adjusting relay on/off times** using push buttons.
- Storing and retrieving **relay schedules from EEPROM**.
- Turning the relay **on and off automatically** based on stored schedules.

### Code Snippet

## How to Use

1. Connect all components togethor
2. Upload the `timer.ino` code to the Arduino board.
3. Set up **relay on/off times** using the push buttons.
4. The system will automatically turn the **relay on and off** at the configured times.
5. The **EEPROM stores schedules**, so they remain saved even after power loss.
6. The **LCD displays the current time** and config settings for relay timing.

## Applications

- Store signboard lighting automation to **save power**.
- Industrial equipment scheduling.
- Home automation projects.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

