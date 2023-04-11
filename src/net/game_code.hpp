#ifndef GAME_CODE_HPP
#define GAME_CODE_HPP

#include <string>
#include <boost/algorithm/string.hpp>

using namespace std;

static const char *CHARS = "QWXRTYLPESDFGHUJKZOCVBINMA";
static const int CHAR_MAP[26] = { 25, 21, 19, 10, 8, 11, 12, 13, 22, 15, 16, 6, 24, 23, 18, 7, 0, 3, 9, 4, 14, 20, 1, 2, 5, 17 };

class GameCode {
public:
    static string int_to_string(int gameCode) {
        if (gameCode < -1) {
            char arr[6];
            int num = gameCode & 1023;
            int num2 = (int) ((unsigned int) gameCode >> 10 & 1048575U);
            arr[0] = CHARS[num % 26];
            arr[1] = CHARS[num / 26];
            arr[2] = CHARS[num2 % 26];
            arr[3] = CHARS[num2 / 26 % 26];
            arr[4] = CHARS[num2 / 676 % 26];
            arr[5] = CHARS[num2 / 17576 % 26];
            return arr;
        }
        return (const char*)&gameCode;
    }

    static unsigned int string_to_int(string& gameCode) {
        boost::to_upper(gameCode);
        for (const auto &item: gameCode) {
            if (!isalpha(item)) {
                return 0;
            }
        }

        if (gameCode.length() == 4) {
            return *(int*)gameCode.c_str();
        }

        int first = CHAR_MAP[(int) gameCode[0] - 65];
        int second = CHAR_MAP[(int) gameCode[1] - 65];
        int third = CHAR_MAP[(int) gameCode[2] - 65];
        int fourth = CHAR_MAP[(int) gameCode[3] - 65];
        int fifth = CHAR_MAP[(int) gameCode[4] - 65];
        int sixth = CHAR_MAP[(int) gameCode[5] - 65];

        int firstTwo = (first + 26 * second) & 0x3FF;
        int lastFour = (third + 26 * (fourth + 26 * (fifth + 26 * sixth)));

        return firstTwo | ((lastFour << 10) & 0x3FFFFC00) | 0x80000000;
    }
};

#endif //GAME_CODE_HPP
