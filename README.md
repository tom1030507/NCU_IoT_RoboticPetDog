# BLE Beacon and RFID Controlled Robotic Pet Dog with OLED and DHT22 Integration

## Project Overview

This project is a **robotic pet dog**, designed as an interactive companion for individuals who want to experience owning a pet without the associated responsibilities. Powered by an **ESP32 microcontroller**, this robotic dog offers dynamic features such as BLE-based ball tracking, RFID-based owner authentication, OLED "mood" display, and environmental awareness through a DHT22 sensor. It can display information, "chat" with its owner, and actively seek a ball embedded with a BLE beacon when thrown.

---

## Features

1. **Simulated Pet Experience**:
   - Offers companionship by displaying "moods" and "chatting" with the owner through the OLED screen.
   - Responds to environmental changes with contextual messages.

2. **BLE Ball Tracking**:
   - The robotic dog "plays fetch" by tracking and finding a ball containing a BLE beacon. Throw the ball, and the dog will seek it out using RSSI signal strength.

3. **RFID-Based Ownership**:
   - Authenticates the owner with an RFID card, toggling its active/inactive state.

4. **Interactive OLED Display**:
   - Displays real-time updates, such as:
     - Pet dog status: Active/Inactive.
     - Environmental data: Temperature and humidity.
     - Moods: "Hi, master!", "I'm HOT!", or "I'm COLD!"
     - Fetching actions: "Finding ball..." or "I found the ball!"

5. **DHT22 Sensor Integration**:
   - Monitors the environment to display temperature and humidity, influencing the dog's "mood."

---

## Use Case Scenario

### Target Audience
This robotic pet dog is ideal for:
- Individuals who want to experience pet ownership without the long-term commitment.
- Families who want an interactive educational toy.
- Enthusiasts looking for a tech-driven robotic companion.

### Interactive Experiences
1. **Daily Companion**:
   - The robotic dog greets its owner and displays status updates like "Hi, master!" or reacts to the environment (e.g., "I'm HOT!" if the temperature is high).

2. **Playing Fetch**:
   - Insert a BLE beacon into a ball and throw it.
   - The dog tracks the ball's location using BLE RSSI and "fetches" it by moving toward the beacon.

3. **Casual Chats**:
   - The dog dynamically updates messages on its OLED screen, "chatting" with the owner and responding to current conditions.

4. **Environmental Feedback**:
   - The robotic dog reflects on its surroundings, making it more lifelike:
     - Complains when it's too hot or cold.
     - Displays calm or cheerful messages in comfortable conditions.

---

## Hardware Requirements

- **ESP32 microcontroller**
- **ESP32 Development Board**
- **MFRC522 RFID Module**
- **BLE Beacon** (embedded in the ball for fetch functionality)
- **Seeed OLED Display**
- **DHT22 Temperature and Humidity Sensor**
- **Motor driver circuit and motors** for movement

---

## Software Requirements

- Arduino IDE
- Required Arduino libraries:
  - `BLEDevice` (for BLE communication)
  - `MFRC522` (for RFID integration)
  - `SeeedOLED` (for OLED display)
  - `DHT` (for DHT22 sensor)

---

## How to Use

1. **Setup**:
   - Assemble the hardware according to the wiring in the code.
   - Update the following parameters in the code:
     - `beaconAddress`: Set the BLE beacon's MAC address (used in the ball for tracking).
     - `myUID`: Define the RFID card's UID for owner authentication.
     - `SS_PIN` and `RST_PIN`: Define the RFID module's pins.

2. **Upload the Code**:
   - Compile and upload the code to the ESP32 using Arduino IDE.

3. **Operation**:
   - Use an RFID card to authenticate and activate the robotic dog.
   - Throw a BLE-enabled ball, and the dog will seek it using BLE RSSI.
   - Enjoy real-time interaction as the dog "chats" and displays its moods on the OLED screen.

---

## Behavior Details

1. **RFID Authentication**:
   - The robotic dog authenticates its owner using an RFID card. A valid card toggles its active/inactive state.

2. **BLE Ball Tracking**:
   - Tracks the ball using a BLE beacon's signal strength:
     - Moves toward the ball when the signal is weak.
     - Stops when close enough and "finds the ball."

3. **OLED Mood and Chat Display**:
   - Dynamically updates to reflect the dog's current "mood":
     - **Idle**: Shows temperature, humidity, and casual messages.
     - **Active**: Displays fetch actions ("Finding ball..." or "I found the ball!").

4. **Environmental Feedback**:
   - Responds to temperature changes with appropriate messages.

---

## OLED Display Details

| Row  | Content                 |
|------|--------------------------|
| Row 1 | Pet dog status (`ON`/`OFF`) |
| Row 2 | Temperature (`°C`)      |
| Row 3 | Humidity (`%`)          |
| Row 4-5 | Moods or fetch actions  |

---

## Reference Materials

- [BLEDevice Library Documentation](https://github.com/nkolban/esp32-snippets)
- [MFRC522 Library Documentation](https://github.com/miguelbalboa/rfid)
- [Seeed OLED Documentation](https://wiki.seeedstudio.com/Grove-OLED_Display_0.96inch/)
- [DHT Library Documentation](https://github.com/adafruit/DHT-sensor-library)

---

Bring this robotic pet dog into your life for endless interactive fun! 🐶✨