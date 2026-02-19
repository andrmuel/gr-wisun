/* -*- c++ -*- */
/*
 * Copyright 2026 GARDENA GmbH.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_WISUN_POWER_SQUELCH_RELATIVE_CC_H
#define INCLUDED_WISUN_POWER_SQUELCH_RELATIVE_CC_H

#include <gnuradio/sync_block.h>
#include <gnuradio/wisun/api.h>

namespace gr {
namespace wisun {

/*!
 * \brief <+description of block+>
 * \ingroup wisun
 *
 */
class WISUN_API power_squelch_relative_cc : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<power_squelch_relative_cc> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of wisun::power_squelch_relative_cc.
     *
     * To avoid accidental use of raw pointers, wisun::power_squelch_relative_cc's
     * constructor is in a private implementation
     * class. wisun::power_squelch_relative_cc::make is the public interface for
     * creating new instances.
     */
    static sptr make(const double relative_threshold, const double alpha);
};

} // namespace wisun
} // namespace gr

#endif /* INCLUDED_WISUN_POWER_SQUELCH_RELATIVE_CC_H */
