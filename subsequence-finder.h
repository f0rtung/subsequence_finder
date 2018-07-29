#pragma once

class needle_wrapper_t;
class file_paths_generator_t;
class file_writer_t;

class subsequence_finder_t
{
public:
    subsequence_finder_t( const needle_wrapper_t &needle_wr,
                          file_paths_generator_t &fp_gen,
                          file_writer_t &result_file );

private:

};
