#include <iostream>
#include "QRCodeManager.h"

using namespace std;

int main() {
    string inputUsr;
	string inputStr;
    vector<string> binaryVector;
    QRCodeManager qrCodeManager = QRCodeManager();

    qrCodeManager.run();
}