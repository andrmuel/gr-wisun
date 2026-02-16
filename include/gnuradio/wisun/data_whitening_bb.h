/* -*- c++ -*- */
/*
 * Copyright 2026 GARDENA GmbH.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_WISUN_DATA_WHITENING_BB_H
#define INCLUDED_WISUN_DATA_WHITENING_BB_H

#include <gnuradio/sync_block.h>
#include <gnuradio/wisun/api.h>

namespace gr {
namespace wisun {

/*!
 * \brief Block used to apply data (de-)whitening to the bitstream.
 * \ingroup wisun
 *
 * This block applies (XORs) the data whitening pattern to the bit stream. As the
 * operation is symmetrical, the same block can be used for whitening (sender) and
 * de-whitening (receiver).
 *
 * Note: the PN9 used in Wi-SUN does not use the common polynomial x⁹ + x⁵ + 1, but rather
 * the polynomial x⁹ + x⁴ + 1 (feedback taken from 9th and 4th stage of shift register).
 */
class WISUN_API data_whitening_bb : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<data_whitening_bb> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of wisun::data_whitening_bb.
     * \param packet_tag Name tag indicating the start of a new packet
     * \param header_bits number of PHY header bits in the packet (ignored for data
     * whitening)
     *
     * To avoid accidental use of raw pointers, wisun::data_whitening_bb's
     * constructor is in a private implementation
     * class. wisun::data_whitening_bb::make is the public interface for
     * creating new instances.
     */
    static sptr make(const std::string packet_tag, const uint16_t header_bits);
};

} // namespace wisun
} // namespace gr

#endif /* INCLUDED_WISUN_DATA_WHITENING_BB_H */
