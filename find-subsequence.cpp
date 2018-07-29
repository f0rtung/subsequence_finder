#include "common.h"
#include "find-subsequence.h"
#include "binary-file-reader.h"

bool contains_subsequence( const needle_wrapper_t &needle,
                           const std::string &file_path )
{
    binary_file_reader_t file{ file_path };
    const auto needle_size{ needle.size( ) };

    if ( file.size( ) < needle_size ) {
        return false;
    }

    sequence_t chunk( needle_size * 2 );
    auto chunk_begin{ chunk.data( ) };
    auto chunk_mid{ chunk_begin + needle_size };

    file.read( chunk_begin, needle_size );

    while ( file.is_good( ) ) {

        file.read( chunk_mid, needle_size );

        if ( file.read_bytes_count( ) < needle_size ) {
            auto end_point{ chunk.end( ) };
            std::advance( end_point,  file.read_bytes_count( ) - needle_size );
            chunk.erase( end_point, chunk.end( ) );
            return needle.is_subsequence_of( chunk );
        }

        if ( needle.is_subsequence_of( chunk ) ) {
            return true;
        }

        std::copy_n( chunk_mid, needle_size, chunk_begin );
    }
    return false;
}

void find_subsequence( const needle_wrapper_t &needle,
                       file_paths_generator_t &fp_gen,
                       file_writer_t &result_file )
{
    while ( true ) {
        try {
            const std::string file_path{ fp_gen.next_file_path( ) };
            if ( contains_subsequence( needle, file_path ) ) {
                result_file.save( file_path );
            }
        } catch ( const stop_iteration_exception & ) {
            return;
        } catch ( const std::exception & ) {

        }
    }
}
