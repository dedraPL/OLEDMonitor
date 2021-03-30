# INFO
Hardware implementation for OLED display of system info from MSI Afterburner.
Program reads Serial input and displays into on template screens. 
Displays CPU and GPU usage on buffered graph and temperature with numeric value and FPS on buffered graph.

# HARDWARE
You can run in on any ESP32 board with SSD1306 OLED display. I'm developing it on Heltec WiFi Kit 32.

# SOFTWARE

Windows software can be found on my other repo https://github.com/dedraPL/AfterburnerOLEDDisplay

<ins>You need both to work.</ins>

# PACKET
Serial input read MessagePack format packets. 

Key | Value | Description
--- | ----- | -----------
GT | uint8 | GPU Temperature
GU | uint8 | GPU Usage (buffored on graph)
CT | uint8 | CPU Temperature
CU | uint8 | CPU Usage (buffored on graph)
FR | uint8 | Framerate (buffored on graph)

# TODO

- [x] working static version
- [x] GPU, CPU, FPS screens
- [ ] comments in code
- [ ] input buttons or other form of control
- [ ] status bar
- [ ] RAM usage screen
- [ ] screens configuration via desktop app
- [ ] Blutetooth comm version