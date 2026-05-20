#include<iostream>
using namespace std;
//Device Classes
class Device {
private:
	char name[20];
	bool isOn;
	int brightness;
public:
	/*Default Constructor*/
	Device() {
		name[0] = 'U';
		name[1] = 'n';
		name[2] = 'k';
		name[3] = 'n';
		name[4] = 'o';
		name[5] = 'w';
		name[6] = 'n';
		name[7] = '\0';
		isOn = false;
		brightness = 50;
	}
	/*Overloaded Constructor*/
	Device(char n[], bool status, int b) {
		int i = 0;
		while (n[i] != '\0') {
			name[i] = n[i];
			i++;
		}
		name[i] = '\0';
		isOn = status;
		if (b >= 0 && b <= 100)
			brightness = b;
		else
			brightness = 50;
	}
	/*Destructor*/
	~Device() {
		cout << "Device" << name << " is being removed." << endl;
	}
	/*Setter & Getter*/
	void setName(char n[]) {
		int i = 0;
		while (n[i] != '\0') {
			name[i] = n[i];
			i++;
		}
		name[i] = '\0';

	}
	char* getName() {
		return name;
	}
	void setBrightness(int b) {
		if (b >= 0 && b <= 100)
			brightness = b;
	}
	int getBrightness() const {
		return brightness;
	}
	void turnOn() {
		isOn = true;
	}
	void turnOff() {
		isOn = false;
	}
	bool getStatus() const {
		return isOn;
	}
	/*Display Function*/
	void showInfo() const {
		cout << "Name:" << name << ",Status:";
		if (isOn)
			cout << "ON";
		else
			cout << "OFF";
		cout << ",Brightness: " << brightness << endl;
	}

};
//Room Class
class Room {
private:
	char roomName[20];
	Device devices[5];
	int count;
public:
	/*Consructor*/
	Room(char name[]) {
		int i = 0;
		while (name[i] != '\0') {
			roomName[i] = name[i];
			i++;
		}
		roomName[i] = '\0';
		count = 0;
	}
	/*Destructor*/
	~Room() {
		cout << "Room" << roomName << "manager closed." << endl;
	}
	void addDevice(Device d) {
		if (count < 5) {
			devices[count] = d;
			count++;
			cout << "Device added successfully." << endl;
		}
		else {
			cout << "Room is full!" << endl;
		}

	}
	void showAllDevices() const {
		if (count == 0) {
			cout << "No devices in room." << endl;
			return;
		}
		for (int i = 0;i < count;i++) {
			devices[i].showInfo();

		}
	}
	int findDevice(char name[]) {
		for (int i = 0;i < count;i++) {
			int j = 0;
			while (devices[i].getName()[j] == name[j] &&
				devices[i].getName()[j] != '\0') {
				j++;
			}
			if (devices[i].getName()[j] == '\0' && name[j] == '\0')
				return i;
		}
		return -1;
	}
	void toggleDevice(char name[]) {
		int index = findDevice(name);
		if (index == -1) {
			cout << "Device not found." << endl;
			return;
		}
		if (devices[index].getStatus())
			devices[index].turnOff();
		else
			devices[index].turnOn();
		cout << "Devices status changed." << endl;


	}
	void setDeviceBrightness(char name[], int b) {
		int index = findDevice(name);
		if (index == -1) {
			cout << "Device not found." << endl;
			return;
		}
		devices[index].setBrightness(b);
		cout << "Brightness updated." << endl;
	}
};
//Main Program
int main() {
	char roomName[] = "MyRoom";
	Room room(roomName);
	int choice;
	do {
		cout << "\n====Start Room Manager====" << endl;
		cout << "1.Add a device" << endl;
		cout << "2.Show all devices" << endl;
		cout << "3.Turn device ON/OFF" << endl;
		cout << "4.Change brightness" << endl;
		cout << "5.Exit" << endl;
		cout << "Enter choice:";
		cin >> choice;
		if (choice == 1) {
			char name[20];
			int bright;
			cout << "Enter device name:";
			cin >> name;
			cout << "Enter Brightness(0-100):";
			cin >> bright;
			Device d(name, false, bright);
			room.addDevice(d);

		}
		else if (choice == 2) {
			room.showAllDevices();
		}
		else if (choice == 3) {
			char name[20];
			cout << "Enter device name:";
			cin >> name;
			room.toggleDevice(name);
		}
		else if (choice == 4)
		{
			char name[20];
			int bright;
			cout << "Enter device name:";
			cin >> name;
			cout << "Enter new brightness:";
			cin >> bright;
			room.setDeviceBrightness(name, bright);
		}
	} while (choice != 5);
	return 0;
}
