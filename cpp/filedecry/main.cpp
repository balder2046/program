#include <iostream>
#include "DecryFile.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc < 3) return 1;
    std::vector<char> keys;
    int defaultkey = 1981;

    char *buf = (char *) &defaultkey;
    size_t size;
    for (int i = 0; i < 4; ++i) {
        keys.push_back(buf[i]);
    }
    std::string filename = argv[1];
    std::string newfilename = argv[2];
    DecryFile fileprocess(filename,newfilename,&keys[0],keys.size());
    fileprocess.DoProcess();
    return 0;
}