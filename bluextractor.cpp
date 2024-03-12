//required header files, check readme to ensure you have all prerequisites
#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

using namespace std;

// Bluetooth device discovery function, initiates discovery and returns a vector of mac addresses
vector<string> discoverBluetoothDevices() {
    vector<string> deviceAddresses;

    // Open a Bluetooth socket, not forgetting error checking/handling
    int socket = hci_open_dev(hci_get_route(nullptr));
    if (socket < 0) {
        cerr << "Error opening Bluetooth socket" << endl;
        return deviceAddresses;
    }

    // some inquiry parameters and flags
    inquiry_info* devices = nullptr;
    inquiry_info* devicePtr;
    inquiry_info inquiryInfo;
    inquiryInfo.with_rssi = 0; 
    inquiryInfo.hci_filter = nullptr;
    inquiryInfo.dev_class = 0;
    inquiryInfo.dev_id = hci_get_route(nullptr);
    inquiryInfo.flags = IREQ_CACHE_FLUSH;

    // do some enquiry here...
    int numDevices = hci_inquiry(inquiryInfo.dev_id, inquiryInfo.length, 0, nullptr, &devices, inquiryInfo.flags);
    if (numDevices < 0) {
        cerr << "Error during Bluetooth inquiry" << endl;
        close(socket);
        return deviceAddresses;
    }

    // Retrieve device addresses
    for (int i = 0; i < numDevices; ++i) {
        devicePtr = devices + i;
        bdaddr_t& bdaddr = devicePtr->bdaddr;

        char address[18];
        snprintf(address, 18, "%02X:%02X:%02X:%02X:%02X:%02X", bdaddr.b[5], bdaddr.b[4], bdaddr.b[3], bdaddr.b[2], bdaddr.b[1], bdaddr.b[0]);
        deviceAddresses.push_back(address);
    }

//don't forget to clean
    free(devices);
    close(socket);

    return deviceAddresses;
}

// now here's the function that prompts the user to select a device
string selectBluetoothDevice(const vector<string>& devices) {
    cout << "Select a Bluetooth device:" << endl;

    for (size_t i = 0; i < devices.size(); ++i) {
        cout << i + 1 << ". " << devices[i] << endl;
    }
}

int main() {
    // Discover Bluetooth devices
    vector<string> devices = discoverBluetoothDevices();

    if (devices.empty()) {
        cerr << "No Bluetooth devices found" << endl;
        return 1;
    }

    // Select a Bluetooth device
    string selectedDevice = selectBluetoothDevice(devices);

    if (selectedDevice.empty()) {
        cerr << "Failed to select a Bluetooth device" << endl;
        return 1;
    }

    cout << "Selected Bluetooth device: " << selectedDevice << endl;

    return 0;
}
