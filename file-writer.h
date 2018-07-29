#pragma once

#include <string>
#include <fstream>
#include <mutex>

class file_writer_t
{
public:
    explicit file_writer_t( const std::string &file_path );
    void save( const std::string &content );

private:
    std::mutex write_guard_;
    std::ofstream file_stream_;
};
