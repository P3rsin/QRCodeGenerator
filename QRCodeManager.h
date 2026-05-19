#ifndef QRCODEMANAGER_H
#define QRCODEMANAGER_H

#include <string>
#include <vector>

using namespace std;

class QRCodeManager {
public:
    QRCodeManager();

    string reverseStr(string strToReverse);
    string charToBinary(char character);
    string stringToBinary(string str);
    int binaryToInt(string binary);
    char binaryToChar(string binary);
    string intToFixedBinary(int num, int bits);

    vector<string> populateBinaryVector();
    string binaryVectorToStr();
    string constructQRCode();
    string decodeQRCode(string qrCode);
    void downloadQRCode();

    int checksumMaker(string inputStr);

    void setInputStr(string inputStr);

    void run();

private:
    string inputStr;
    vector<string> binaryVector;
    string QRCode;

    const string QRCodeSignature = "HAQR";
};

#endif