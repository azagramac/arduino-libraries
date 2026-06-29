<p align="center">
  <img height="200" src="https://github.com/AzagraMac/arduino-libraries/assets/571796/98b7d23b-63ab-438d-a098-ca27784ad950">
</p>

# Arduino Libraries Collection

A curated collection of Arduino libraries and board configurations.

## 📦 Library Installation

To use these libraries, clone this repository and copy or symlink the library folders to the Arduino libraries directory on your operating system:

| Operating System | Path |
| --- | --- |
| **macOS** | `/Users/$USER/Documents/Arduino/libraries/` |
| **Linux** | `/home/$USER/Documents/Arduino/libraries/` |
| **Windows** | `C:\Users\%USERNAME%\Documents\Arduino\libraries\` |

> [!NOTE]
> All these libraries can also be found and updated directly in the **Arduino Library Manager** (`Tools > Manage Libraries`).

---

## 🛠️ Board ESP8266 Installation

To add support for ESP8266 boards in the Arduino IDE:

1. Copy the following URLs:
   ```sh
   https://arduino.esp8266.com/stable/package_esp8266com_index.json
   ```
2. In the Arduino IDE, go to **File > Preferences** (or **Arduino > Preferences** on macOS).
3. Paste the URLs into the **Additional Boards Manager URLs** field (separate multiple URLs with a comma or newline).
4. Restart the IDE, then go to **Tools > Board > Boards Manager...** to install the boards.

---

## 📚 Included Libraries

This repository contains **106** libraries:

<details>
<summary><b>Click to expand the full list of libraries</b></summary>

### Adafruit
- [Adafruit_BME280_Library](./Adafruit_BME280_Library)
- [Adafruit_BME680_Library](./Adafruit_BME680_Library)
- [Adafruit_BusIO](./Adafruit_BusIO)
- [Adafruit_Circuit_Playground](./Adafruit_Circuit_Playground)
- [Adafruit_GFX_Library](./Adafruit_GFX_Library)
- [Adafruit_GPS_Library](./Adafruit_GPS_Library)
- [Adafruit_ILI9341](./Adafruit_ILI9341)
- [Adafruit_LED_Backpack_Library](./Adafruit_LED_Backpack_Library)
- [Adafruit_seesaw_Library](./Adafruit_seesaw_Library)
- [Adafruit_SH110X](./Adafruit_SH110X)
- [Adafruit_SleepyDog_Library](./Adafruit_SleepyDog_Library)
- [Adafruit_SSD1306](./Adafruit_SSD1306)
- [Adafruit_ST7735_and_ST7789_Library](./Adafruit_ST7735_and_ST7789_Library)
- [Adafruit_STMPE610](./Adafruit_STMPE610)
- [Adafruit_TouchScreen](./Adafruit_TouchScreen)
- [Adafruit_TSC2007](./Adafruit_TSC2007)
- [Adafruit_Unified_Sensor](./Adafruit_Unified_Sensor)
- [Adafruit_Zero_DMA_Library](./Adafruit_Zero_DMA_Library)
- [Adafruit_Zero_FFT_Library](./Adafruit_Zero_FFT_Library)
- [Adafruit_Zero_PDM_Library](./Adafruit_Zero_PDM_Library)

### Arduino Official & Semi-official
- [Arduino_AdvancedAnalog](./Arduino_AdvancedAnalog)
- [Arduino_APA102](./Arduino_APA102)
- [Arduino_APDS9960](./Arduino_APDS9960)
- [Arduino_AVRSTL](./Arduino_AVRSTL)
- [ArduinoBearSSL](./ArduinoBearSSL)
- [Arduino_BHY2](./Arduino_BHY2)
- [Arduino_BHY2Host](./Arduino_BHY2Host)
- [ArduinoBLE](./ArduinoBLE)
- [Arduino_BMI270_BMM150](./Arduino_BMI270_BMM150)
- [Arduino_BQ24195](./Arduino_BQ24195)
- [Arduino_Braccio_plusplus](./Arduino_Braccio_plusplus)
- [Arduino_BuiltIn](./Arduino_BuiltIn)
- [Arduino_Cellular](./Arduino_Cellular)
- [Arduino_Cloud_Provider_Examples](./Arduino_Cloud_Provider_Examples)
- [Arduino_CloudUtils](./Arduino_CloudUtils)
- [Arduino_ConnectionHandler](./Arduino_ConnectionHandler)
- [Arduino_DebugUtils](./Arduino_DebugUtils)
- [arduino-DuinoCoin](./arduino-DuinoCoin)
- [ArduinoECCX08](./ArduinoECCX08)
- [Arduino_GigaDisplay](./Arduino_GigaDisplay)
- [Arduino_GigaDisplay_GFX](./Arduino_GigaDisplay_GFX)
- [Arduino_GigaDisplayTouch](./Arduino_GigaDisplayTouch)
- [ArduinoGraphics](./ArduinoGraphics)
- [ArduinoHttpClient](./ArduinoHttpClient)
- [ArduinoIoTCloud](./ArduinoIoTCloud)
- [ArduinoJson](./ArduinoJson)
- [Arduino_KVStore](./Arduino_KVStore)
- [Arduino_Low_Power](./Arduino_Low_Power)
- [ArduinoMqttClient](./ArduinoMqttClient)
- [Arduino_NetworkConfigurator](./Arduino_NetworkConfigurator)
- [Arduino_RouterBridge](./Arduino_RouterBridge)
- [Arduino_RPClite](./Arduino_RPClite)
- [Arduino_SE05X](./Arduino_SE05X)
- [Arduino_SecureElement](./Arduino_SecureElement)
- [Arduino_SigFox_for_MKRFox1200](./Arduino_SigFox_for_MKRFox1200)
- [Arduino_SpiNINA](./Arduino_SpiNINA)
- [ArduinoUniqueID](./ArduinoUniqueID)
- [Arduino_Uno_WiFi_Dev_Ed_Library](./Arduino_Uno_WiFi_Dev_Ed_Library)
- [Arduino_Video](./Arduino_Video)

### Other / Third-Party
- [ArxContainer](./ArxContainer)
- [ArxTypeTraits](./ArxTypeTraits)
- [AsyncTCP](./AsyncTCP)
- [DebugLog](./DebugLog)
- [DHT_sensor_library](./DHT_sensor_library)
- [EasyScheduler](./EasyScheduler)
- [ELMDuino](./ELMDuino)
- [ESP8266_and_ESP32_OLED_driver_for_SSD1306_displays](./ESP8266_and_ESP32_OLED_driver_for_SSD1306_displays)
- [ESPAsyncTCP](./ESPAsyncTCP)
- [ESP_Async_WebServer](./ESP_Async_WebServer)
- [Ethernet](./Ethernet)
- [FabGL](./FabGL)
- [Firmata](./Firmata)
- [FontCollection](./FontCollection)
- [GestureDetector](./GestureDetector)
- [GU_Elements](./GU_Elements)
- [HTTPClient](./HTTPClient)
- [Keyboard](./Keyboard)
- [LiquidCrystal](./LiquidCrystal)
- [lvgl](./lvgl)
- [Matter](./Matter)
- [MKRGSM](./MKRGSM)
- [MKRNB](./MKRNB)
- [MKRWAN](./MKRWAN)
- [Mouse](./Mouse)
- [MsgPack](./MsgPack)
- [NTPClient](./NTPClient)
- [RTClib](./RTClib)
- [RTCZero](./RTCZero)
- [SD](./SD)
- [SD_MMC](./SD_MMC)
- [Servo](./Servo)
- [SparkFun_ATECCX08a_Arduino_Library](./SparkFun_ATECCX08a_Arduino_Library)
- [Stepper](./Stepper)
- [StreamDebugger](./StreamDebugger)
- [StreamJoin](./StreamJoin)
- [TFT](./TFT)
- [TinyGSM](./TinyGSM)
- [USB](./USB)
- [WaveHC](./WaveHC)
- [WebServer](./WebServer)
- [WiFi](./WiFi)
- [WiFi101](./WiFi101)
- [WiFiClientSecure](./WiFiClientSecure)
- [WiFi_Link](./WiFi_Link)
- [WiFiNINA](./WiFiNINA)
- [Zigbee](./Zigbee)

</details>
