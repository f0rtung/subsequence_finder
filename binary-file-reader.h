#pragma once

#include <string>
#include <fstream>

class binary_file_reader_t
{
public:
    explicit binary_file_reader_t( const std::string &file_path );

public:
    void read( char *buf, std::size_t size );
    std::size_t size( ) const noexcept;
    bool is_good( ) const;
    std::size_t read_bytes_count( ) const;

private:
    std::ifstream bf_stream_;
    std::size_t bf_size_;
};
