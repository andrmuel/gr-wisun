#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2026 GARDENA GmbH.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

"""Tests for data_whitening_bb block."""

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import pmt
try:
    from gnuradio.wisun import data_whitening_bb
except ImportError:
    import os
    import sys
    dirname, filename = os.path.split(os.path.abspath(__file__))
    sys.path.append(os.path.join(dirname, "bindings"))
    from gnuradio.wisun import data_whitening_bb

# first 24 bits of PN9 sequence data given in 802.15.4-2020 section 16.2.3
PN9_EXAMPLE_DATA = [0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1]


def make_tag(key, value, offset, srcid=None):
    """Create a tag."""
    tag = gr.tag_t()
    tag.key = pmt.string_to_symbol(key)
    tag.value = pmt.to_pmt(value)
    tag.offset = offset
    if srcid is not None:
        tag.srcid = pmt.to_pmt(srcid)
    return tag


class qa_data_whitening_bb(gr_unittest.TestCase):
    """GNU Radio test case class."""

    def setUp(self):
        """Set up top block."""
        self.tb = gr.top_block()

    def tearDown(self):
        """Teardown."""
        self.tb = None

    def test_instance(self):
        """Test to ensure block can be instantiated."""
        data_whitening_bb("wisun-packet", 32)

    def test_001_data_without_tag_not_modified(self):
        """Test to ensure data outside a packet is not touched."""
        src_data = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
        # set up fg
        src = blocks.vector_source_b(src_data)
        blk = data_whitening_bb("wisun-packet", 32)
        dst = blocks.vector_sink_b()
        self.tb.connect(src, blk)
        self.tb.connect(blk, dst)

        # run flow graph
        self.tb.run()

        # ensure data is unmodified
        result_data = dst.data()
        self.assertEqual(src_data, result_data)

    def test_002_zero_payload_results_in_pn9_sequence(self):
        """Test with zero bits as payload - should result in PN9 sequence."""
        initial_data = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
        packet_header = [
            1, 0, 0, 1, 0, 0, 0, 0,  # SFD
            0, 1, 0, 0, 1, 1, 1, 0,  # SFD
            0, 0, 0, 0, 0, 0, 0, 0,  # PHR
            0, 0, 0, 0, 0, 0, 0, 0,  # PHR (packet length - 7 bytes: 4 byte header + 3 byte payload)
        ]
        packet_payload = [
            0, 0, 0, 0, 0, 0, 0, 0,  # payload byte 1
            0, 0, 0, 0, 0, 0, 0, 0,  # payload byte 2
            0, 0, 0, 0, 0, 0, 0, 0,  # payload byte 3
        ]
        packet_data = packet_header + packet_payload
        src_data = initial_data + packet_data
        # set up fg
        src = blocks.vector_source_b(src_data,
                                     tags=(
                                         make_tag("wisun-packet", 7, 10),
                                     ))
        blk = data_whitening_bb("wisun-packet", 32)
        dst = blocks.vector_sink_b()
        self.tb.connect(src, blk)
        self.tb.connect(blk, dst)

        # run flow graph
        self.tb.run()

        # ensure data is unmodified
        result_data = dst.data()
        self.assertEqual(result_data[0:10], initial_data)
        self.assertEqual(result_data[10:42], packet_header)
        self.assertEqual(result_data[42:], PN9_EXAMPLE_DATA)

    def test_003_ones_payload_results_in_inverted_pn9_sequence(self):
        """Test with only '1' bits as payload - should result in inverted PN9 sequence."""
        initial_data = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
        packet_header = [
            1, 0, 0, 1, 0, 0, 0, 0,  # SFD
            0, 1, 0, 0, 1, 1, 1, 0,  # SFD
            0, 0, 0, 0, 0, 0, 0, 0,  # PHR
            0, 0, 0, 0, 0, 0, 0, 0,  # PHR (packet length - 7 bytes: 4 byte header + 3 byte payload)
        ]
        packet_payload = [
            1, 1, 1, 1, 1, 1, 1, 1,  # payload byte 1
            1, 1, 1, 1, 1, 1, 1, 1,  # payload byte 2
            1, 1, 1, 1, 1, 1, 1, 1,  # payload byte 3
        ]
        packet_data = packet_header + packet_payload
        src_data = initial_data + packet_data
        # set up fg
        src = blocks.vector_source_b(src_data,
                                     tags=(
                                         make_tag("wisun-packet", 7, 10),
                                     ))
        blk = data_whitening_bb("wisun-packet", 32)
        dst = blocks.vector_sink_b()
        self.tb.connect(src, blk)
        self.tb.connect(blk, dst)

        # run flow graph
        self.tb.run()

        # ensure data is unmodified
        result_data = dst.data()
        inverted_pn9_example_data = [0 if bit == 1 else 1 for bit in PN9_EXAMPLE_DATA]
        self.assertEqual(result_data[0:10], initial_data)
        self.assertEqual(result_data[10:42], packet_header)
        self.assertEqual(result_data[42:], inverted_pn9_example_data)


if __name__ == '__main__':
    gr_unittest.run(qa_data_whitening_bb)
