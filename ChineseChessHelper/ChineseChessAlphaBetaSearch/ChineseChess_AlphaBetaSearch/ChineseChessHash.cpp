#include <string>
#include <stdio.h>
#include <string.h>
#include "ChineseChessHash.h"

ChineseChessHash::ChineseChessHash()
{
    clear();
}

void ChineseChessHash::clear()
{
    htcnt = 0;

    eg = 0;
    memset(head, -1, sizeof(head));
    nxt.clear();
    depth.clear();
    str.clear();
    val.clear();
}

void ChineseChessHash::insert(int d, std::string board, int v)
{
    unsigned int h;

    h = ELFHash(board);
    nxt.push_back(head[h]);
    val.push_back(v);
    str.push_back(board);
    depth.push_back(d);
    head[h] = eg++;
}

bool ChineseChessHash::find(int d, std::string board, int &v)
{
    int e;
    unsigned int h;

    h = ELFHash(board);
    e = head[h];
    while (e != -1) {
        if (depth[e] == d && str[e] == board) {
            v = val[e];
            break;
        }
        e = nxt[e];
    }

//    if (e != -1) {
//        htcnt++;
//        printf("hitcnt: %d\n", htcnt);
//    }
    return e != -1;
}

unsigned int ChineseChessHash::ELFHash(std::string s)
{
    unsigned int g, h = 0;
    const char *str = s.c_str();

    while (*str)
    {
        h = (h << 4) + *str++;
        g = h & 0xf0000000L;
        if (g) h ^= g >> 24;
        h &= ~g;
    }

    return h % CHINESECHESS_HASH_PRIME;
}
