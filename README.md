# BluExtractor - Bluetooth Device Scanner

BluExtractor is a C++ program that scans for nearby Bluetooth devices, allowing the user to select a device for further interaction(extracting mac address of previous users).

## Installation

### Prerequisites

1. **Linux Operating System:** BluExtractor is designed to run on a Linux system, preferably with the BlueZ Bluetooth stack installed.

2. **C++ Compiler:** Ensure you have a C++ compiler installed on your system. You can use `g++` for compilation.

3. **BlueZ Library:** Make sure that the BlueZ Bluetooth library is installed on your system. If not, you can install it using the package manager for your distribution.

   - For Debian/Ubuntu:

     ```bash
     sudo apt-get update
     sudo apt-get install bluez
     ```

   - For Fedora:

     ```bash
     sudo dnf install bluez
     ```

### Compilation

Clone the repository and navigate to the project directory:

```bash
git clone https://github.com/Perry-Bright/bluextractor.git
cd bluextractor
```

Compile the BluExtractor program using `g++`:

```bash
g++ bluextractor.cpp -o bluextractor -lbluetooth
```

## Usage

1. Run the compiled executable:

    ```bash
    ./bluextractor
    ```

2. The program will display a list of nearby Bluetooth devices. Select the desired device by entering the corresponding number.

3. The selected Bluetooth device's MAC address will be shown.

## Notes

- Ensure that Bluetooth is enabled on your system.
- This tool is for learning purposes only, use it at your own risk, you don't know me
- Make sure your user has the necessary permissions to access Bluetooth devices.
- Adapt the BluExtractor program based on your Bluetooth speaker's characteristics and the specific logic required for retrieving connected devices.

Feel free to explore and interact with nearby Bluetooth devices using BluExtractor!
```
