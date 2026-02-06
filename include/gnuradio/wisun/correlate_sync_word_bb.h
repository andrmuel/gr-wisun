/* -*- c++ -*- */
/*
 * Copyright 2026 GARDENA GmbH.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_WISUN_CORRELATE_SYNC_WORD_BB_H
#define INCLUDED_WISUN_CORRELATE_SYNC_WORD_BB_H

#include <gnuradio/sync_block.h>
#include <gnuradio/wisun/api.h>

namespace gr {
namespace wisun {

/*!
 * \brief <+description of block+>
 * \ingroup wisun
 *
 */
class WISUN_API correlate_sync_word_bb : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<correlate_sync_word_bb> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of wisun::correlate_sync_word_bb.
     *
     * To avoid accidental use of raw pointers, wisun::correlate_sync_word_bb's
     * constructor is in a private implementation
     * class. wisun::correlate_sync_word_bb::make is the public interface for
     * creating new instances.
     */
    static sptr make(uint16_t sfd);
};

} // namespace wisun
} // namespace gr

#endif /* INCLUDED_WISUN_CORRELATE_SYNC_WORD_BB_H */
