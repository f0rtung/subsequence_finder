#pragma once

#include <mutex>
#include <regex>
#include <string>
#include <boost/filesystem.hpp>

class stop_iteration_exception : public std::exception
{
public:
    const char* what( ) const noexcept
    {
        return "Have no any files";
    }
};

class file_paths_generator_t
{
public:
    file_paths_generator_t( const std::string &root_folder,
                            const std::string &simple_file_name_pattern );
    std::string next_file_path( );

private:
    bool is_appropriate_path( const boost::filesystem::path &file_name ) const;

private:
    std::mutex curr_file_it_guard_;
    boost::filesystem::recursive_directory_iterator curr_file_it_;
    const boost::filesystem::recursive_directory_iterator end_it_;
    const std::regex file_name_regex_;
};
