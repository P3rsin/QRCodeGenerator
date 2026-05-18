#ifndef QRCODEMANAGER_H
#define QRCODEMANAGER_H

#include <string>
#include <vector>
#include <cmath>

using namespace std;

class QRCodeManager {
    public:
        QRCodeManager();
        QRCodeManager(string inputStr);
        //~QRCodeManager();
        string reverseStr(string strToReverse);
        string charToBinary(char character);
        char binaryToChar(string binary);
        vector<string> populateBinaryVector();
        string binaryVectorToStr();
        void constructQRCode();
        vector<string> getBinaryVector();
        string getInputStr();

    private:
        string inputStr;
        vector<string> binaryVector;
};

#endif