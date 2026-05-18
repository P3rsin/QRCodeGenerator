#include <iostream>
#include "QRCodeManager.h"

using namespace std;

int main() {
    string inputUsr;
	string inputStr;
    vector<string> binaryVector;
    QRCodeManager qrCodeManager = QRCodeManager();

    
    const string title = 
    "-----------------------\n"
    "    QR Code Manager   \n";

    const string menuPrompt =
    "-----------------------\n"
    "[1] Generate a QR code\n"
    "[2] View my QR code\n"
    "[3] Download my QR code\n"
    "[4] Decode a QR code\n"
    "[5] Exit\n"
    "Choice: ";


    cout << title << menuPrompt;
    cin >> inputUsr;

    while (inputUsr != "5") {
        cout << endl;
        
        if (inputUsr == "1") {
            cout << "Please enter a string to convert\nMy Input: ";
            cin.ignore();
            getline(cin, inputStr);
            qrCodeManager.setInputStr(inputStr);
            cout << "\nYour QR code is now:\n" << qrCodeManager.getQRCode();

        } else if (inputUsr == "2") {
            if (qrCodeManager.getQRCode().empty()) {
                cout << "You have not generated a QR code yet" << endl;
            } else {
                cout << "Your current string:\n" << qrCodeManager.getInputStr() << endl;
                cout << "\nYour QR code is:\n" << qrCodeManager.getQRCode();
            }

        } else if (inputUsr == "3") {
            if (qrCodeManager.getQRCode().empty()) {
                cout << "You have not generated a QR code yet" << endl;
            } else {
            cout << "you have chosen to download your QR code" << endl;
            }

        } else if (inputUsr == "4") {
            cout << "you have chosen to decode a QR code" << endl;

        } else {
            cout << "INVALID INPUT" << endl;
            
        }

        cout << endl << menuPrompt;
        cin >> inputUsr;
    }
}