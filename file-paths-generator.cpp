#include "file-paths-generator.h"

#include <boost/algorithm/string.hpp>

file_paths_generator_t::file_paths_generator_t( const std::string &root_folder,
                                                const std::string &simple_file_name_pattern )
    : curr_file_it_{ root_folder }
    , file_name_regex_{ boost::replace_all_copy( simple_file_name_pattern, "*", ".*" ) }
{ }

bool file_paths_generator_t::is_appropriate_path( const boost::filesystem::path &path ) const
{
    std::smatch what;
    return boost::filesystem::is_regular_file( path ) &&
           std::regex_match( path.filename( ).string( ), what, file_name_regex_ );
}

std::string file_paths_generator_t::next_file_path( )
{
    std::lock_guard<std::mutex> _{ curr_file_it_guard_ };

    while ( curr_file_it_ != end_it_ ) {
        const boost::filesystem::path curr_file_path{ curr_file_it_->path( ) };
        if ( is_appropriate_path( curr_file_path ) ) {
            const std::string path_str{ curr_file_path.string( ) };
            ++curr_file_it_;
            return path_str;
        }
        ++curr_file_it_;
    }

    throw stop_iteration_exception{ };
}
