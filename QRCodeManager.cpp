#include "QRCodeManager.h"

#include <cmath>
#include <fstream>
#include <iostream>

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
        int x = asciiValue % 2;
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

int QRCodeManager::binaryToInt(string binary) {
    int value = 0;
    int binarySize = binary.size();
    string reversedBinary = reverseStr(binary);

    for (int i = 0; i < binarySize; i++) {
        if (reversedBinary[i] == '1') {
            value += pow(2, i);
        }
    }

    return value;
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

string QRCodeManager::intToFixedBinary(int num, int bits) {
    string binary = "";

    while (num != 0) {
        int x = num % 2;
        num /= 2;
        binary += to_string(x);
    }

    while (binary.size() < bits) {
        binary += "0";
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
    string inputStrSizeBinary = intToFixedBinary(inputStrSize, 16);

    int checksum = checksumMaker(inputStr);
    string checksumBinary = intToFixedBinary(checksum, 16);

    // 32b sig - 16b input size - 16b checksum;
    header += stringToBinary(QRCodeSignature) + inputStrSizeBinary + checksumBinary;

    // ----------------------------------------------------------------

    string binaryStr = header + binaryVectorToStr();
    int totalNumBits = static_cast<int>(binaryStr.size());
    int gridDimensions = 1;

    while (pow(gridDimensions, 2) < totalNumBits) {
        gridDimensions++;
    }

    gridDimensions += 2;

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

string QRCodeManager::decodeQRCode(string qrCode) {
    string binaryStr = "";
    string zeroBlock = "▒▒";
    string oneBlock = "██";

    for (int i = 0; i < qrCode.size(); i++) {
        if (qrCode.substr(i, zeroBlock.size()) == zeroBlock) {
            binaryStr += "0";
            i += zeroBlock.size() - 1;
        } else if (qrCode.substr(i, oneBlock.size()) == oneBlock) {
            binaryStr += "1";
            i += oneBlock.size() - 1;
        }
    }

    string header = binaryStr.substr(0, 64);
    int inputSize = binaryToInt(header.substr(32, 16));

    string decodedMessage = "";

    for (int i = 64; i < 64 + (inputSize * 8); i += 8) {
        string charBinary = binaryStr.substr(i, 8);
        decodedMessage += binaryToChar(charBinary);
    }

    return decodedMessage;
}

int QRCodeManager::checksumMaker(string inputStr) {
    int checksum = 0;

    for (int i = 0; i < inputStr.size(); i++) {
        int charValue = inputStr[i];
        int signatureValue = QRCodeSignature[i % QRCodeSignature.size()];

        checksum += (charValue * (i + 1)) + signatureValue;
        checksum = checksum % 256;
    }

    return checksum;
}

void QRCodeManager::downloadQRCode() {
    ofstream qrCodeFile("qr_code.txt");

    if (qrCodeFile.is_open()) {
        qrCodeFile << QRCode;
        qrCodeFile.close();

        cout << "QR code downloaded successfully" << endl;
    } else {
        cout << "An error occurred while downloading.\n"
             << "Please try downloading the QR code again\n"
             << endl;
    }
}

void QRCodeManager::setInputStr(string inputStr) {
    this->inputStr = inputStr;
    binaryVector = populateBinaryVector();
    QRCode = constructQRCode();
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
        "[5] About the project\n"
        "[6] Exit\n"
        "Choice: ";

    cout << title << menuPrompt;
    cin >> usrInput;

    while (usrInput != "6") {
        cout << endl;

        if (usrInput == "1") {
            cout << "Please enter a string to convert\nMy Input: ";

            cin.ignore();
            getline(cin, inputStr);
            setInputStr(inputStr);

            cout << "\nYour QR code is now:\n" << QRCode;

            string checkSumMessage =
                "\nChecksum explanation:\n"
                "This QR code uses a position-weighted checksum.\n"
                "Each character's ASCII value is multiplied by its position, then\n"
                "mixed with the HAQR signature. This helps detect if the message\n"
                "changes while being encoded or decoded.";

            cout << "Input checksum: " << checksumMaker(inputStr) << endl;
            cout << "QR checksum: " << checksumMaker(decodeQRCode(QRCode)) << endl;

            if (checksumMaker(decodeQRCode(QRCode)) == checksumMaker(inputStr)) {
                cout << "The checksums match, so the QR code is valid." << endl;
            } else {
                cout << "The checksums do not match, so the QR code may be invalid." << endl;
            }

            cout << checkSumMessage << endl;
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
            cout << "Note, you must type \"Done\" in a NEW LINE" << endl;
            cout << "once you've pasted the QR code you want to" << endl;
            cout << "decode. Please provide the QR code:\n" << endl;

            string line;
            string fullQRCode = "";

            while (true) {
                getline(cin, line);

                if (line == "Done") {
                    break;
                }

                fullQRCode += line + "\n";
            }

            cout << "\nDecoded string: " << decodeQRCode(fullQRCode) << endl;
        } else if (usrInput == "5") {
            string projectInfo =
                "Project Info:\n"
                "This is a simple terminal-based QR Code Generator. The program takes a\n"
                "user's string input, converts each character into binary, and displays\n"
                "that binary data as a visual QR-style grid using shaded and filled blocks.\n"
                "\n"
                "The QR code also includes a small header before the message data. This\n"
                "header stores the HAQR project signature, the length of the original\n"
                "message, and a checksum. The signature helps identify the code as one\n"
                "made by my program, while the message length tells the decoder how many\n"
                "characters to read.\n"
                "\n"
                "The checksum is used to check whether the QR code was encoded and decoded\n"
                "correctly. The program calculates a checksum from the original input, then\n"
                "calculates another checksum from the decoded QR output. If both values\n"
                "match, the program reports that the QR code is valid.\n"
                "\n"
                "Users can generate a QR code, view the current QR code, download it to a\n"
                "text file, or paste a QR code back into the program to decode it.";

            cout << projectInfo << endl;
        } else {
            cout << "INVALID INPUT" << endl;
        }

        cout << endl << menuPrompt;
        cin >> usrInput;
    }
}