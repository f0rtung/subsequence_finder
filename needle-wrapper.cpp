#include "needle-wrapper.h"
#include "binary-file-reader.h"

needle_wrapper_t::needle_wrapper_t( const std::string &needle_file_path )
{
    load_needle_from_file( needle_file_path );
    bm_searcher_.reset( new bm_searcher_t{ needle_.cbegin( ), needle_.cend( ) } );
}

bool needle_wrapper_t::is_subsequence_of( const sequence_t &sequence ) const
{
    const auto serch_result{ (*bm_searcher_)( sequence.cbegin( ), sequence.cend( ) ) };
    return sequence.cend( ) != serch_result.first;
}

sequence_t::size_type needle_wrapper_t::size( ) const noexcept
{
    return needle_.size( );
}

void needle_wrapper_t::load_needle_from_file( const std::string &file_path )
{
    binary_file_reader_t needle_file{ file_path };

    if ( 0 == needle_file.size( ) ) {
        throw std::runtime_error{ "Empty file \"" + file_path + "\"" };
    }

    needle_.resize( needle_file.size( ) );
    needle_file.read( needle_.data( ), needle_file.size( ) );
}
