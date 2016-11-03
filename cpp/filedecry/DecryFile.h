//
// Created by zhaolei on 16-10-20.
//

#ifndef FILEDECRY_DECRYFILE_H
#define FILEDECRY_DECRYFILE_H

#include <vector>
#include <fstream>
#include <string>

class DecryFile {
public:
    ///
    /// \param filename
    /// \param newfilename
    /// \param key
    /// \param size
    /// \param buffersize
    /// \return
    DecryFile(const std::string &filename, const std::string &newfilename, char *key, std::size_t size,
              std::size_t buffersize = 1024 * 512);

protected:

    std::vector<char> decry_key;
    std::string decry_filename;
    std::string new_filename;
    std::fstream read_stream;
    std::fstream write_stream;
public:
    bool DoProcess();
private:
    void decrybuffer(char *buffer, std::size_t size);
    int read_index;
    int max_buffer_size;
};


#endif //FILEDECRY_DECRYFILE_H
