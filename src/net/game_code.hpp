#ifndef GAME_CODE_HPP
#define GAME_CODE_HPP

#include <string>
#include <boost/algorithm/string.hpp>

using namespace std;

static const char *CHARS = "QWXRTYLPESDFGHUJKZOCVBINMA";
static const int CHAR_MAP[26] = { 25, 21, 19, 10, 8, 11, 12, 13, 22, 15, 16, 6, 24, 23, 18, 7, 0, 3, 9, 4, 14, 20, 1, 2, 5, 17 };

class GameCode {
public:
    static string int_to_string(int gameCode);

    static unsigned int string_to_int(string& gameCode);
};

#endif //GAME_CODE_HPP
