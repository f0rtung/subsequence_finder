#pragma once

#include "common.h"

#include <memory>
#include <string>
#include <boost/algorithm/searching/boyer_moore.hpp>

class needle_wrapper_t
{
public:
    explicit needle_wrapper_t( const std::string &needle_file_path );
    bool is_subsequence_of( const sequence_t &sequence ) const;
    sequence_t::size_type size( ) const noexcept;

private:
    void load_needle_from_file( const std::string &needle_file_path );

private:
    using bm_searcher_t = boost::algorithm::boyer_moore<sequence_t::const_iterator>;
    std::unique_ptr<bm_searcher_t> bm_searcher_;
    sequence_t needle_;
};
