#include "find-subsequence.h"

#include <thread>
#include <iostream>
#include <boost/program_options.hpp>

boost::program_options::variables_map parse_command_line( int argc, const char* const *argv )
{
    namespace po = boost::program_options;
    po::variables_map vm;
    po::options_description desc{ "Options" };

    try {
        desc.add_options( )
        ( "help,h",
          "Help message" )
        ( "rootpath,p", po::value<std::string>( )->default_value( "./" ),
          "Folder with files for searching" )
        ( "filemask,m", po::value<std::string>( )->default_value( "*" ),
          "File name mask" )
        ( "subseqfile,i", po::value<std::string>( )->required( ),
          "Path to file with subsequence" )
        ( "resultfile,o", po::value<std::string>( )->default_value( "./result.txt" ),
          "Path to file with result" );
        po::store( po::parse_command_line( argc, argv, desc ), vm );
        po::notify(vm);
    } catch ( const po::required_option &ex ) {
        if ( vm.count( "help" ) ) {
            std::cout << desc << "\n";
        } else {
            throw ex;
        }
    }
    return vm;
}

int main( int argc, char** argv )
{
    try {
        const auto params = parse_command_line( argc, argv );

        if ( params.count( "help" ) ) {
            return 0;
        }

        const needle_wrapper_t needle{ params["subseqfile"].as<std::string>( ) };
        file_writer_t file_result{ params["resultfile"].as<std::string>( ) };
        file_paths_generator_t fp_gen{ params["rootpath"].as<std::string>( ),
                                       params["filemask"].as<std::string>( ) };

        std::size_t threads_count{ 4 };
        std::vector<std::thread> threads;
        for ( std::size_t idx = 0; idx < threads_count; ++idx ) {
            threads.push_back( std::thread( [ &needle, &file_result, &fp_gen ] {
                                    find_subsequence( needle, fp_gen, file_result );
                               } )
            );
        }

        for ( auto &thread : threads ) {
            thread.join( );
        }

    } catch ( const std::exception &ex ) {
        std::cout << ex.what( ) << std::endl;
        return 1;
    }
    return 0;
}
