#include <iostream>
#include "QRCodeManager.h"

using namespace std;

int main() {
	string inputStr;
    vector<string> binaryVector;

    
    getline(cin, inputStr);
    QRCodeManager qrCodeManager = QRCodeManager(inputStr);
    binaryVector = qrCodeManager.getBinaryVector();


    cout << "input: " << qrCodeManager.getInputStr() << endl;

    for (size_t i = 0; i < binaryVector.size(); i++) {
        cout << qrCodeManager.binaryToChar(binaryVector[i]) << " - " << binaryVector[i] << endl;
    }

    qrCodeManager.constructQRCode();
}