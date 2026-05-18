#include "QRCodeManager.h"
#include <iostream>
#include <cmath>

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

    while (binary.size() != 8) {
        binary += "0";
    }

    return reverseStr(binary);
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
    string binaryStr = binaryVectorToStr();
    int binaryVectorSize = static_cast<int>(binaryVector.size());
    int totalNumChars = binaryVectorSize * 8;
    int gridDimensions = 1;

    while (pow(gridDimensions, 2) < totalNumChars) {
        gridDimensions++;
    }

    //cout << "size: " << totalNumChars << " gd: " << gridDimensions << endl;

    //cout << binaryStr << endl;

    QRCode = "";
    size_t idx = 0;
    for (int i = 0; i < gridDimensions; i++) {
        for (int j = 0; j < gridDimensions; j++) {
            if (idx < totalNumChars) {
                //cout << binaryStr[idx] << " ";
                QRCode += binaryStr[idx];
                QRCode += " ";
            } else {
                // cout << "m ";
                QRCode += "m ";
            }

            idx++;
        }
        // cout << endl;
        QRCode += "\n";
    }

    return QRCode;
}

string QRCodeManager::destructQRCode() {
    // to be implemented
    // converts a qr code back to a string
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