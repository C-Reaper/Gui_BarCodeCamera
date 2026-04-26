# Project README

## Overview
- This project is a simple GUI application for capturing and processing barcode images using OpenCV. The application features real-time video capture, barcode detection, and display.

## Features
- Real-time video capture
- Barcode detection using OpenCV
- Display of detected barcodes on the screen
- Cross-platform build support (Linux, Windows, Wine, Web)

## Project Structure
### Prerequisites
- C/C++ Compiler and Debugger (GCC, Clang)
- Make utility
- Standard development tools
- Libraries needed in specific projects:
  - X11 for GUI display
  - OpenCV for image processing

## Build & Run
### Linux Build Process
```bash
cd /home/code/Gui_BarCodeCamera/
make -f Makefile.linux all
./build/Main
```

### Windows Build Process
```bash
cd C:\path\to\Gui_BarCodeCamera\
make -f Makefile.windows all
.\build\Main.exe
```

### Wine Build Process
```bash
cd /home/code/Gui_BarCodeCamera/
make -f Makefile.wine all
wine build/Main.exe
```

### WebAssembly Build Process
```bash
cd /home/code/Gui_BarCodeCamera/
make -f Makefile.web all
emrun --no_browser --port 8080 build/index.html
```

# Project Organization
- **build/**: .exe files produced by Main.c
- **src/**: 
  - `Main.c`: Entry point
  - `*.h`: Standalone header-based C-files, without *.c files that implement them
- **Makefile.linux**: Linux build configuration
- **Makefile.windows**: Windows build configuration
- **Makefile.wine**: Wine build configuration
- **Makefile.web**: Emscripten build configuration
- **README.md**: This file