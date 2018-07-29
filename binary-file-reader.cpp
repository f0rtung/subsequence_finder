#include "binary-file-reader.h"

binary_file_reader_t::binary_file_reader_t( const std::string &file_path )
{
    const auto open_mod = std::ifstream::in |
                          std::ifstream::binary |
                          std::ifstream::ate;
    bf_stream_.open( file_path, open_mod );
    if ( !bf_stream_ ) {
        throw std::runtime_error{ "Can not open file \"" + file_path + "\"" };
    }
    bf_size_ = bf_stream_.tellg( );
    bf_stream_.seekg( 0 );
}

void binary_file_reader_t::read( char *buf, std::size_t size )
{
    bf_stream_.read( buf, size );
}

std::size_t binary_file_reader_t::size( ) const noexcept
{
    return bf_size_;
}

bool binary_file_reader_t::is_good( ) const
{
    return bf_stream_.good( );
}

std::size_t binary_file_reader_t::read_bytes_count( ) const
{
    return bf_stream_.gcount( );
}
