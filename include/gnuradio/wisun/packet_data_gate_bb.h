/* -*- c++ -*- */
/*
 * Copyright 2026 GARDENA GmbH.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_WISUN_PACKET_DATA_GATE_BB_H
#define INCLUDED_WISUN_PACKET_DATA_GATE_BB_H

#include <gnuradio/block.h>
#include <gnuradio/wisun/api.h>

namespace gr {
namespace wisun {

/*!
 * \brief <+description of block+>
 * \ingroup wisun
 *
 */
class WISUN_API packet_data_gate_bb : virtual public gr::block
{
public:
    typedef std::shared_ptr<packet_data_gate_bb> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of wisun::packet_data_gate_bb.
     *
     * To avoid accidental use of raw pointers, wisun::packet_data_gate_bb's
     * constructor is in a private implementation
     * class. wisun::packet_data_gate_bb::make is the public interface for
     * creating new instances.
     */
    static sptr make(const std::string length_tag);
};

} // namespace wisun
} // namespace gr

#endif /* INCLUDED_WISUN_PACKET_DATA_GATE_BB_H */
