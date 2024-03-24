#include <iostream>
#include <vector>
#include <Windows.h>
#include <BluetoothAPIs.h>
#include <Strsafe.h>

// Use the standard namespace for simplicity
using namespace std;

// Structure to hold Bluetooth device information
struct BluetoothDeviceInfo {
    wstring name;                   // Name of the Bluetooth device
    wstring address;                // Address of the Bluetooth device
    wstring type;                   // Device type
    wstring serviceCapabilities;    // Service capabilities
    wstring manufacturer;           // Manufacturer information
    BYTE batteryLevel;              // Battery level
    wstring connectionMetadata;     // Connection metadata
};

// Function to perform Bluetooth device discovery
vector<BluetoothDeviceInfo> discoverBluetoothDevices() {
    vector<BluetoothDeviceInfo> devices;

    // Initialize Bluetooth
    BLUETOOTH_DEVICE_SEARCH_PARAMS searchParams = { sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS), 1, 0, 1, 0, 0, 15, NULL };
    BLUETOOTH_DEVICE_INFO deviceInfo = { sizeof(BLUETOOTH_DEVICE_INFO), 0 };

    HANDLE hRadio;
    HBLUETOOTH_DEVICE_FIND hFind;
    BLUETOOTH_DEVICE_INFO deviceInfo = { sizeof(BLUETOOTH_DEVICE_INFO), 0 };

    // Open the first available Bluetooth radio
    hRadio = BluetoothFindFirstRadio(&searchParams, &hRadio);
    if (hRadio == NULL) {
        cerr << "Error opening Bluetooth radio" << endl;
        return devices;
    }

    // Start device discovery
    hFind = BluetoothFindFirstDevice(&searchParams, &deviceInfo);
    if (hFind == NULL) {
        cerr << "Error starting device discovery" << endl;
        CloseHandle(hRadio);
        return devices;
    }

    // Iterate through discovered devices
    do {
        BluetoothDeviceInfo device;
        device.name = deviceInfo.szName;  // Get the name of the Bluetooth device
        device.address = deviceInfo.Address; // Get the address of the Bluetooth device
        device.type = (deviceInfo.ulClassofDevice & MASK_COD_MAJOR_DEVICE) == COD_MAJOR_DEVICE_AUDIO_VIDEO ? L"Audio/Video" : L"Unknown"; // Get the device type
        device.serviceCapabilities = deviceInfo.fConnected ? L"Connected" : L"Not connected"; // Get the service capabilities
        device.manufacturer = deviceInfo.szManufacturer; // Get the manufacturer information
        device.batteryLevel = deviceInfo.fRemembered ? deviceInfo.fAuthenticated ? deviceInfo.fConnected ? BTH_DEVICE_STATE_CONNECTED : BTH_DEVICE_STATE_AUTHENTICATED : BTH_DEVICE_STATE_REMEMBERED : BTH_DEVICE_STATE_UNKNOWN; // Get the battery level information
        device.connectionMetadata = deviceInfo.szDeviceName; // Get the connection metadata
        devices.push_back(device);
    } while (BluetoothFindNextDevice(hFind, &deviceInfo));

    // Close device discovery handle and radio handle
    BluetoothFindDeviceClose(hFind);
    CloseHandle(hRadio);

    return devices;
}

int main() {
    // Discover Bluetooth devices
    vector<BluetoothDeviceInfo> devices = discoverBluetoothDevices();

    if (devices.empty()) {
        cerr << "No Bluetooth devices found" << endl;
        return 1;
    }

    // Display details of discovered Bluetooth devices
    cout << "Details of the discovered Bluetooth devices:" << endl;
    for (size_t i = 0; i < devices.size(); ++i) {
        cout << "Device " << i + 1 << ":" << endl;
        cout << "Name: " << devices[i].name << endl;
        cout << "Address: " << devices[i].address << endl;
        cout << "Device Type: " << devices[i].type << endl;
        cout << "Service Capabilities: " << devices[i].serviceCapabilities << endl;
        cout << "Manufacturer Information: " << devices[i].manufacturer << endl;
        cout << "Battery Level Information: " << static_cast<int>(devices[i].batteryLevel) << "%" << endl;
        cout << "Connection Metadata: " << devices[i].connectionMetadata << endl;
    }

    return 0;
}
