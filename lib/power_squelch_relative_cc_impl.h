/* -*- c++ -*- */
/*
 * Copyright 2026 GARDENA GmbH.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_WISUN_POWER_SQUELCH_RELATIVE_CC_IMPL_H
#define INCLUDED_WISUN_POWER_SQUELCH_RELATIVE_CC_IMPL_H

#include <gnuradio/wisun/power_squelch_relative_cc.h>

namespace gr {
namespace wisun {

class power_squelch_relative_cc_impl : public power_squelch_relative_cc
{
private:
    // Nothing to declare in this block.

public:
    power_squelch_relative_cc_impl(const double relative_threshold, const double alpha);
    ~power_squelch_relative_cc_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace wisun
} // namespace gr

#endif /* INCLUDED_WISUN_POWER_SQUELCH_RELATIVE_CC_IMPL_H */
