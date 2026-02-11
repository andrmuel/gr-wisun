/* -*- c++ -*- */
/*
 * Copyright 2026 GARDENA GmbH.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_WISUN_PACKET_DATA_GATE_BB_IMPL_H
#define INCLUDED_WISUN_PACKET_DATA_GATE_BB_IMPL_H

#include <gnuradio/wisun/packet_data_gate_bb.h>

namespace gr {
namespace wisun {

class packet_data_gate_bb_impl : public packet_data_gate_bb
{
private:
    // Nothing to declare in this block.

public:
    packet_data_gate_bb_impl(const std::string length_tag);
    ~packet_data_gate_bb_impl();

    // Where all the action really happens
    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace wisun
} // namespace gr

#endif /* INCLUDED_WISUN_PACKET_DATA_GATE_BB_IMPL_H */
