# Repository Guidelines

## Project Overview

This repository contains an ESP32 Arduino smart plant dashboard with ST7789 TFT, XPT2046 touch, LVGL v9.4, and EEZ Studio generated UI files. It also works as an Obsidian vault for project notes, Bases, Canvas diagrams, tasks, and reading references.

## Repository Structure

- `smartPlant/` - main ESP32 smart plant sketch and generated LVGL/EEZ UI source.
- `ui/` - EEZ Studio generated UI reference export.
- `DHT_Test/` - standalone DHT sensor test sketch.
- `NeoPixel_Test/` - standalone NeoPixel test sketch.
- `Bases/` - Obsidian `.base` files and `.canvas` diagrams.
- `Books/`, `Tasks/`, daily notes - Obsidian notes with frontmatter for trackers.
- `../docs/` - GitHub README translations and showcase assets.
- `../User_Setup.h` - TFT_eSPI config template to copy into Arduino libraries.
- `../lv_conf.h` - LVGL config template to copy into Arduino libraries.

## Required Config Copy

Arduino libraries read their config from the installed library folders, not from the repo root. Before compiling, copy:

```powershell
Copy-Item ..\User_Setup.h "$env:USERPROFILE\Documents\Arduino\libraries\TFT_eSPI\User_Setup.h" -Force
Copy-Item ..\lv_conf.h "$env:USERPROFILE\Documents\Arduino\libraries\lv_conf.h" -Force
```

Key TFT_eSPI values:

- `#define ST7789_DRIVER`
- `#define TFT_WIDTH  240`
- `#define TFT_HEIGHT 320`
- `#define TFT_RGB_ORDER TFT_BGR`
- `#define SPI_FREQUENCY 27000000`
- `#define TFT_CS   17`
- `#define TFT_DC   16`
- `#define TFT_RST   5`
- `#define TOUCH_CS 21`

Key LVGL values:

- `#if 1`
- `LV_COLOR_DEPTH 16`
- Keep the fonts used by the EEZ Studio UI enabled.

## Arduino IDE Setup

- Board: ESP32 Dev Module.
- Upload speed: 115200.
- Serial monitor: 115200 baud.
- Main sketch: `smartPlant/smartPlant.ino`.
- Required libraries:
  - TFT_eSPI by Bodmer
  - LVGL v9.4.x
  - XPT2046_Touchscreen by Paul Stoffregen
  - DHT sensor library by Adafruit

## Local Secrets

`smartPlant/secrets.h` is ignored by git. Create it from:

```powershell
Copy-Item smartPlant\secrets.example.h smartPlant\secrets.h
```

Do not commit WiFi credentials or generated build outputs.

## Hardware Pin Map

| Component | GPIO | Notes |
| --- | --- | --- |
| DHT11 DATA | 27 | Temperature and humidity. |
| Soil Moisture A0 | 35 | ADC, dry = 4095, wet = 1200. |
| Rain Sensor A0 | 34 | ADC mapped to 0-100%. |
| Relay Light IN | 15 | Active-low. |
| Relay Pump IN | 2 | Active-low. |
| TFT Backlight | 32 | Driven high in setup. |
| TFT CS | 17 | ST7789 chip select. |
| TFT DC | 16 | ST7789 data/command. |
| TFT RST | 5 | ST7789 reset. |
| TFT/Touch MOSI | 23 | Shared SPI MOSI. |
| TFT/Touch SCLK | 18 | Shared SPI clock. |
| Touch MISO | 19 | XPT2046 MISO. |
| Touch CS | 21 | XPT2046 chip select. |

## Development Notes

- Treat `screens.c`, `screens.h`, `ui.c`, `ui.h`, `vars.c`, `vars.h`, `styles.c`, `styles.h`, `images.c`, `images.h`, `actions.h`, `fonts.h`, and `structs.h` as generated files unless a hardware integration fix requires a local edit.
- Keep GitHub-facing documentation in the root `README.md` and `docs/README.vi.md`.
- Keep Obsidian-facing documentation in `Smart Plant System.md` and files under `Bases/`, `Tasks/`, and `Books/`.
- Avoid committing local Arduino caches, compiled binaries, or private credentials.
