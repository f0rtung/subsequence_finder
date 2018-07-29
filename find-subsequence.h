#pragma once

#include "file-writer.h"
#include "needle-wrapper.h"
#include "file-paths-generator.h"

#include <string>

bool contains_subsequence( const needle_wrapper_t &needle,
                           const std::string &file_path );

void find_subsequence( const needle_wrapper_t &needle,
                       file_paths_generator_t &fp_gen,
                       file_writer_t &result_file );
