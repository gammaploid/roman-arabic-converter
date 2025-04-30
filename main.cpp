#include <iostream>
#include <string>
#include <cctype>

using namespace std;


string units[10] = {
    "",
    "I",
    "II",
    "III",
    "IV",
    "V",
    "VI",
    "VII",
    "VIII",
    "IX"
};


string tens[10] = {
    "",
    "X",
    "XX",
    "XXX",
    "XL",
    "L",
    "LX",
    "LXX",
    "LXXX",
    "XC"
};

string hundreds[10] = {
    "",
    "C",
    "CC",
    "CCC",
    "CD",
    "D",
    "DC",
    "DCC",
    "DCCC",
    "CM"
};

string thousands[4] = {
    "",
    "M",
    "MM",
    "MMM"
};




string numberToRoman(int num) {
    string result = "";
    int thousandsDigit = (num / 1000) % 10;
    int hundredsDigit = (num / 100) % 10;
    int tensDigit = (num / 10) % 10;
    int unitsDigit = num % 10;
    result += thousands[thousandsDigit];
    result += hundreds[hundredsDigit];
    result += tens[tensDigit];
    result += units[unitsDigit];
    return result;
}
string romanToArabic(string roman) {
    int result = 0;
    for ( char &c : roman) {
        c = toupper(c);
    }
    for (int i =0; i < roman.length(); i++) {
        if (roman[i] == 'M') result += 1000;
        else if (roman[i] == 'D') result += 500;
        else if (roman[i] == 'C') result += 100;
        else if (roman[i] == 'L') result += 50;
        else if (roman[i] == 'X') result += 10;
        else if (roman[i] == 'V') result += 5;
        else if (roman[i] == 'I') result += 1;

    }


}

int romanCharToValue(char c) {

    c = toupper(c);
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;

    }
}

bool isValidRomanCharacter(char c) {
    c = toupper(c);

    return (c == 'I' || c == 'V' || c == 'X' || c == 'L' || c == 'C' || c == 'D' || c == 'M');
}



int romanToNumber(string roman) {
    int result = 0;
    int length = roman.length();
    for (int i = 0; i < length; i++) {
        int current = romanCharToValue(roman[i]);
        int next = (i + 1 < length) ? romanCharToValue(roman[i + 1]) : 0;
        if (current < next) {
            result -= current;
        }
        else {
            result += current;
        }
    }
    return result;
}


int matchRomanPrefix(string roman, int &pos) {
    if (roman.substr(pos, 2) == "CM") {pos += 2; return 900;}
    if (roman.substr(pos, 2) == "CD") {pos += 2; return 400;}
    if (roman.substr(pos, 2) == "XC") {pos += 2; return 90;}
    if (roman.substr(pos, 2) == "XL") {pos += 2; return 40; }
    if (roman.substr(pos, 2) == "IX") {pos += 2; return 9;}
    if (roman.substr(pos, 2) == "IV") {pos += 2; return 4;}

    if (roman[pos] == 'M') { pos++; return 1000;}
    if (roman[pos] == 'D') { pos++; return 500;}
    if (roman[pos] == 'C') {pos++; return 100;}
    if (roman[pos] == 'L') {pos++; return 50;}
    if (roman[pos] == 'X') {pos++; return 10;}
    if (roman[pos] == 'V') {pos++; return 5;}
    if (roman[pos] == 'I') {pos++; return 1;}
    return 0;
}


int extendedRomanToNumber(string roman) {
    int total = 0;
    int pos = 0;
    int length = roman.length();
    while (pos < length) {
        int value = matchRomanPrefix(roman, pos);
        if (value == 0) break;
        total += value;
    }
    return total;
}



bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isValidRoman(string roman) {
    for (char c : roman) {
        if (!isValidRomanCharacter(c)) {
            return false;
        }
    }
    return true;
}


int plusModeRomanToNumber(string input) {
    int total = 0;
    string currentRoman = "";
    for (char c : input) {
        if (isValidRomanCharacter(c)) {
            currentRoman += toupper(c);
        } else {
            if (!currentRoman.empty()) {
                total += extendedRomanToNumber(currentRoman);
                currentRoman = "";
            }
        }
    }
    if (!currentRoman.empty()) {
        total += extendedRomanToNumber(currentRoman);
    }
    return total;
}


int main(int argc, char* argv[]) {
    bool plusMode = false;
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-plus") {
            plusMode = true;
            break;
        }
    }

    string input;
    while (cin >> input) {
        if (plusMode) {
            cout << plusModeRomanToNumber(input) << endl;
        }
        else {
            if (isdigit(input[0])) {
                string numberPart = "";
                for (char c : input) {
                    if (isdigit(c)) {
                        numberPart += c;
                    } else {
                        break;
                    }
                }

                int num = stoi(numberPart);
                if (num > 0 && num <= 3999) {
                    cout << numberToRoman(num) << endl;
                } else {
                    cout << 0 << endl;
                }
            }

            else {
                string validPrefix = "";
                for (char c : input) {
                    if (isValidRomanCharacter(c)) {
                        validPrefix += toupper(c);
                    } else {
                        break;
                    }
                }

                if (!validPrefix.empty()) {
                    int arabic = extendedRomanToNumber(validPrefix);
                    if (arabic > 0 && arabic <= 3999){
                        cout << arabic << endl;
                    }

                    else{
                        cout << 0 << endl;
                    }
                }
                else{
                    cout << 0 << endl;
                }
            }

        }
    }

    return 0;

}