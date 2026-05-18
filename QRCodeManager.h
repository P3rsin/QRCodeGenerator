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
        char binaryToChar(string binary);
        vector<string> populateBinaryVector();
        string binaryVectorToStr();
        string constructQRCode();
        string destructQRCode();
        void downloadQRCode();
        vector<string> getBinaryVector();
        string getInputStr();
        void setInputStr(string inputStr);
        string getQRCode();
        void run();

    private:
        string inputStr;
        vector<string> binaryVector;
        string QRCode;
};

#endif