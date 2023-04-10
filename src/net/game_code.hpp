#ifndef GAME_CODE_HPP
#define GAME_CODE_HPP

#include <string>

using namespace std;

static const char* CHARS = "QWXRTYLPESDFGHUJKZOCVBINMA";

class GameCode {
public:
    static string int_to_string(int gameCode) {
        char arr[6];
        int num = gameCode & 1023;
        int num2 = (int)((uint)gameCode >> 10 & 1048575U);
        arr[0] = CHARS[num % 26];
        arr[1] = CHARS[num / 26];
        arr[2] = CHARS[num2 % 26];
        arr[3] = CHARS[num2 / 26 % 26];
        arr[4] = CHARS[num2 / 676 % 26];
        arr[5] = CHARS[num2 / 17576 % 26];
        for (const auto &item: arr) {
            if (item < 'A' || item > 'z') {
                return "";
            }
        }
        return string(arr);
    }

    static int string_to_int(string gameCode) {

    }
};

#endif //GAME_CODE_HPP
