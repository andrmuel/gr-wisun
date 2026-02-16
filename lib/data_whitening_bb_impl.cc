/* -*- c++ -*- */
/*
 * Copyright 2026 GARDENA GmbH.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "data_whitening_bb_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace wisun {

static const uint16_t pn9_seed = 0x1ff;

using input_type = uint8_t;
using output_type = uint8_t;

data_whitening_bb::sptr data_whitening_bb::make(const std::string packet_tag,
                                                const uint16_t header_bits)
{
    return gnuradio::make_block_sptr<data_whitening_bb_impl>(packet_tag, header_bits);
}


/*
 * The private constructor
 */
data_whitening_bb_impl::data_whitening_bb_impl(const std::string packet_tag,
                                               const uint16_t header_bits)
    : gr::sync_block("data_whitening_bb",
                     gr::io_signature::make(1, 1, sizeof(input_type)),
                     gr::io_signature::make(1, 1, sizeof(output_type))),
      d_packet_tag(packet_tag),
      d_header_bits(header_bits),
      d_header_bits_remaining(0),
      d_payload_bits_remaining(0),
      d_pn9_state(0)
{
}

/*
 * Our virtual destructor.
 */
data_whitening_bb_impl::~data_whitening_bb_impl() {}

int data_whitening_bb_impl::work(int noutput_items,
                                 gr_vector_const_void_star& input_items,
                                 gr_vector_void_star& output_items)
{
    auto in = static_cast<const input_type*>(input_items[0]);
    auto out = static_cast<output_type*>(output_items[0]);
    std::vector<tag_t> tags;
    uint16_t pn9_next_bit;

    /* TODO check if data whitening is enabled for each packet */

    // do signal processing
    for (int i = 0; i < noutput_items; i++) {
        if (d_header_bits_remaining) { /* ignore packet header (no data whitening) */
            out[i] = in[i];
            d_header_bits_remaining--;
        } else if (d_payload_bits_remaining) { /* apply data whitening to payload */
            /* update PN9 state */
            pn9_next_bit = ((d_pn9_state >> 8) ^ (d_pn9_state >> 3)) & 1;
            d_pn9_state = ((d_pn9_state << 1) | pn9_next_bit) & 0x1ff;
            /* apply whitening to next bit */
            out[i] = in[i] ^ pn9_next_bit;
            d_payload_bits_remaining--;
        } else {
            /* check for next packet tag */
            get_tags_in_range(tags,
                              0,
                              nitems_read(0) + i,
                              nitems_read(0) + i + 1,
                              pmt::string_to_symbol(d_packet_tag));
            if (tags.size() > 0) {
                /* next packet start found - set up de-whitening */
                uint16_t packet_length = pmt::to_long(tags[0].value);
                d_header_bits_remaining = d_header_bits;
                d_payload_bits_remaining = 8 * packet_length - d_header_bits;
                d_pn9_state = pn9_seed;
            }
            /* copy unmodified data */
            out[i] = in[i];
            if (d_header_bits_remaining) {
                /* first bit already copied */
                d_header_bits_remaining--;
            }
        }
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace wisun */
} /* namespace gr */
