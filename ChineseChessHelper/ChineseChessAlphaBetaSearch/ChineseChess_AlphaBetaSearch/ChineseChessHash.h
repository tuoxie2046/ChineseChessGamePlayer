#ifndef CHINESECHESSHASH_H
#define CHINESECHESSHASH_H

#include <vector>
#include <string>
#define CHINESECHESS_HASH_PRIME 1020379

class ChineseChessHash
{
public:
    ChineseChessHash();
    void clear();
    void insert(int depth, std::string board, int v);
    bool find(int depth, std::string board, int &v);
private:
    unsigned int ELFHash(std::string s);
private:
    int eg, htcnt;
    int head[CHINESECHESS_HASH_PRIME];
    std::vector<int> nxt;
    std::vector<int> depth;
    std::vector<int> val;
    std::vector<std::string> str;
};

#endif // CHINESECHESSHASH_H
