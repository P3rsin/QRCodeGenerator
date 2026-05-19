#include "QRCodeManager.h"
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

QRCodeManager::QRCodeManager() {
    inputStr = "";
    binaryVector = populateBinaryVector();
    QRCode = "";
}

string QRCodeManager::reverseStr(string strToReverse) {
    string reversedStr = "";
    for (int i = strToReverse.size() - 1; i >= 0; i--) {
        reversedStr += strToReverse[i];
    }

    return reversedStr;
}

string QRCodeManager::charToBinary(char character) {
    int asciiValue = int(character);

    string binary = "";
    while (asciiValue != 0) {
        int x = 0;

        x = asciiValue % 2;
        asciiValue /= 2;
        binary += to_string(x);
    }

    while (binary.size() < 8) {
        binary += "0";
    }

    return reverseStr(binary);
}

string QRCodeManager::stringToBinary(string str) {
    string binaryStr = "";
    for (int i = 0; i < str.size(); i++) {
        binaryStr += charToBinary(str[i]);
    }

    return binaryStr;
}

char QRCodeManager::binaryToChar(string binary) {
    int asciiValue = 0;
    size_t binarySize = binary.size();
    string reversedBinary = reverseStr(binary);
    
    for (size_t i = 0; i < binarySize; i++) {
        if (reversedBinary[i] == '1') {
            asciiValue += static_cast<int>(pow(2, i));
        }
    }

    return char(asciiValue);
}

string QRCodeManager::intToBinary(int num) {
    string binary = "";
    while (num != 0) {
        int x = 0;

        x = num % 2;
        num /= 2;
        binary += to_string(x);
    }

    return reverseStr(binary);
}

vector<string> QRCodeManager::populateBinaryVector() {
    size_t inputSize = inputStr.size();
    vector<string> binaryVector(inputSize);

    for (size_t i = 0; i < inputSize; i++) {
        binaryVector.at(i) = charToBinary(inputStr[i]);
    }

    return binaryVector;
}

string QRCodeManager::binaryVectorToStr() {
    string binaryStr = "";

    for (size_t i = 0; i < binaryVector.size(); i++) {
        binaryStr += binaryVector[i];
    }

    return binaryStr;
}

string QRCodeManager::constructQRCode() {

    // ---------------------- header for qr code ----------------------

    string header = "";

    int inputStrSize = inputStr.size(); 
    string inputStrSizeBinary = intToBinary(inputStrSize);

    header += QRCodeSignature + inputStrSizeBinary; // + checksum (later)
    int headerSize = header.size();
    string headerSizeBinary = intToBinary(headerSize);

    if (headerSizeBinary.size() < 16) { // 16 bits for header size
        while (headerSizeBinary.size() < 16) {
            headerSizeBinary = "0" + headerSizeBinary;
        }
    }

    header = headerSizeBinary + header; // add header size to the beginning of the header

    // ----------------------------------------------------------------

    string binaryStr = header + binaryVectorToStr();
    int totalNumBits = static_cast<int>(binaryStr.size());
    int gridDimensions = 1;

    while (pow(gridDimensions, 2) < totalNumBits) {
        gridDimensions++;
    }
    gridDimensions += 2;

    cout << binaryStr << endl;

    QRCode = "";
    size_t idx = 0;
    for (int i = 0; i < gridDimensions; i++) {
        for (int j = 0; j < gridDimensions; j++) {
            if (i == 0 && j == 0) {
                QRCode += "╔";
            } else if (i == 0 && j == gridDimensions - 1) {
                QRCode += "╗";
            } else if (i == gridDimensions - 1 && j == 0) {
                QRCode += "╚";
            } else if (i == gridDimensions - 1 && j == gridDimensions - 1) {
                QRCode += "╝";
            } else if (i == 0 || i == gridDimensions - 1) {
                QRCode += "══";
            } else if (j == 0 || j == gridDimensions - 1) {
                QRCode += "║";
            } else {
                if (idx < totalNumBits) {
                    if (binaryStr[idx] == '1') {
                        QRCode += "██";
                    } else {
                        QRCode += "▒▒";
                    }
                } else {
                    QRCode += "██";
                }
                idx++;
            }
        }
        QRCode += "\n";
    }

    return QRCode;
}

string QRCodeManager::decodeQRCode() {
    // to be implemented
    // converts a qr code back to a string
}

void QRCodeManager::downloadQRCode() {
    ofstream qrCodeFile("qr_code.txt");
    if (qrCodeFile.is_open()) {
        qrCodeFile << QRCode;
        qrCodeFile.close();
        cout << "QR code downloaded successfully" << endl;
    } else {
        cout << "An error occurred while downloading.\nPlease try downloading the QR code again\n" << endl;
    }
}

vector<string> QRCodeManager::getBinaryVector() {
    return binaryVector;
}

string QRCodeManager::getInputStr() {
    return inputStr;
}

void QRCodeManager::setInputStr(string inputStr) {
    this->inputStr = inputStr;
    binaryVector = populateBinaryVector();
    QRCode = constructQRCode();
}

string QRCodeManager::getQRCode() {
    return QRCode;
}

void QRCodeManager::run() {
    string usrInput;

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
    cin >> usrInput;

    while (usrInput != "5") {
        cout << endl;
        
        if (usrInput == "1") {
            cout << "Please enter a string to convert\nMy Input: ";
            cin.ignore();
            getline(cin, inputStr);
            setInputStr(inputStr);
            cout << "\nYour QR code is now:\n" << QRCode;

        } else if (usrInput == "2") {
            if (QRCode.empty()) {
                cout << "You have not generated a QR code yet" << endl;
            } else {
                cout << "Your current string:\n" << inputStr << endl;
                cout << "\nYour QR code is:\n" << QRCode;
            }

        } else if (usrInput == "3") {
            if (QRCode.empty()) {
                cout << "You have not generated a QR code yet" << endl;
            } else {
                downloadQRCode();
            }

        } else if (usrInput == "4") {
            cout << "you have chosen to decode a QR code" << endl;

        } else {
            cout << "INVALID INPUT" << endl;
            
        }

        cout << endl << menuPrompt;
        cin >> usrInput;
    }
}