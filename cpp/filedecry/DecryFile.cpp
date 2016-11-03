//
// Created by zhaolei on 16-10-20.
//
#include <iostream>
#include "DecryFile.h"

DecryFile::DecryFile(const std::string &filename, const std::string &newfilename, char *key, std::size_t size ,size_t buffersize) {
    decry_key.clear();
    for (int i = 0; i < size; ++i) {
        decry_key.push_back(key[i]);
    }
    decry_filename = filename;
    new_filename = newfilename;
    read_index = 0;
    max_buffer_size = buffersize;
}

bool DecryFile::DoProcess()
{
    read_index = 0;
    read_stream.open(decry_filename, std::ios_base::in | std::ios_base::binary);
    write_stream.open(new_filename, std::ios_base::out | std::ios_base::binary);
    int buffer_size = 1024 * 1024;
    char *buffer = new char[max_buffer_size];
    while(read_stream)
    {
        read_stream.read(buffer,max_buffer_size);
        int readed = read_stream.gcount();
        if (readed > 0)
        {
            decrybuffer(buffer,readed);
            write_stream.write(buffer,readed);
        }
    }

    delete buffer;
    read_stream.close();
    write_stream.close();
    std::cout << "write " + new_filename << " ok" << std::endl;
    return true;
}

void DecryFile::decrybuffer(char *buffer, std::size_t size) {
    for (int i = 0; i < size; ++i, read_index++) {
        // the key muse be in the decry_key array
        int index = read_index % decry_key.size();
        buffer[i] = buffer[i] ^ decry_key[index];
    }
}

