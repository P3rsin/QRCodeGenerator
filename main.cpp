#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

string reverseStr(string strToReverse) {
    string reversedStr = "";
    for (int i = strToReverse.size() - 1; i >= 0; i--) {
        reversedStr += strToReverse[i];
    }

    return reversedStr;
}

string charToBinary(char character) {
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

char binaryToChar(string binary) {
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

vector<string> populateBinaryVector(string inputStr) {
    size_t inputSize = inputStr.size();
    vector<string> binaryVector(inputSize);

    for (size_t i = 0; i < inputSize; i++) {
        binaryVector.at(i) = charToBinary(inputStr[i]);
    }

    return binaryVector;
}

string binaryVectorToStr(vector<string> binaryVector) {
    string binaryStr = "";

    for (size_t i = 0; i < binaryVector.size(); i++) {
        binaryStr += binaryVector[i];
    }

    return binaryStr;
}

void constructQRCode(vector<string> binaryVector) {
    string binaryStr = binaryVectorToStr(binaryVector);
    int binaryVectorSize = static_cast<int>(binaryVector.size());
    int totalNumChars = binaryVectorSize * 8;
    int gridDimensions = 1;

    while (pow(gridDimensions, 2) < totalNumChars) {
        gridDimensions++;
    }

    cout << "size: " << totalNumChars << " gd: " << gridDimensions << endl;

    cout << binaryStr << endl;

    size_t idx = 0;
    for (int i = 0; i < gridDimensions; i++) {
        for (int j = 0; j < gridDimensions; j++) {
            if (idx < totalNumChars) {
                cout << binaryStr[idx] << " ";
            } else {
                cout << "m ";
            }

            idx++;
        }
        cout << endl;
    }
}

int main() {
	string inputStr;
    vector<string> binaryVector;

    getline(cin, inputStr);
    binaryVector = populateBinaryVector(inputStr);

    cout << "input: " << inputStr << endl;

    for (size_t i = 0; i < binaryVector.size(); i++) {
        cout << binaryToChar(binaryVector[i]) << " - " << binaryVector[i] << endl;
    }

    constructQRCode(binaryVector);
}