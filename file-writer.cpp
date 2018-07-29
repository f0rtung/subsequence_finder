#include "file-writer.h"

file_writer_t::file_writer_t( const std::string &file_path )
    : file_stream_{ file_path, std::ofstream::trunc }
{ }

void file_writer_t::save( const std::string &content )
{
    std::lock_guard<std::mutex> _{ write_guard_ };
    file_stream_ << content << std::endl;
}
