/* -*- c++ -*- */
/*
 * Copyright 2026 GARDENA GmbH.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_WISUN_CORRELATE_SYNC_WORD_BB_IMPL_H
#define INCLUDED_WISUN_CORRELATE_SYNC_WORD_BB_IMPL_H

#include <gnuradio/wisun/correlate_sync_word_bb.h>

namespace gr {
namespace wisun {

class correlate_sync_word_bb_impl : public correlate_sync_word_bb
{
private:
    // Nothing to declare in this block.

public:
    correlate_sync_word_bb_impl(uint16_t sfd);
    ~correlate_sync_word_bb_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace wisun
} // namespace gr

#endif /* INCLUDED_WISUN_CORRELATE_SYNC_WORD_BB_IMPL_H */
