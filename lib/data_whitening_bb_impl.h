/* -*- c++ -*- */
/*
 * Copyright 2026 GARDENA GmbH.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_WISUN_DATA_WHITENING_BB_IMPL_H
#define INCLUDED_WISUN_DATA_WHITENING_BB_IMPL_H

#include <gnuradio/wisun/data_whitening_bb.h>

namespace gr {
namespace wisun {

class data_whitening_bb_impl : public data_whitening_bb
{
private:
    std::string d_packet_tag;
    uint16_t d_header_bits;
    uint16_t d_header_bits_remaining;
    uint16_t d_payload_bits_remaining;
    uint16_t d_pn9_state;

public:
    data_whitening_bb_impl(const std::string packet_tag, const uint16_t header_bits);
    ~data_whitening_bb_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace wisun
} // namespace gr

#endif /* INCLUDED_WISUN_DATA_WHITENING_BB_IMPL_H */
