/* -*- c++ -*- */
/* 
 * Copyright 2015 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <gnuradio/io_signature.h>
#include "num_count_impl.h"
int global_counter=0;
namespace gr {
  namespace mymod {

    num_count::sptr
    num_count::make()
    {
      return gnuradio::get_initial_sptr
        (new num_count_impl());
    }

    /*
     * The private constructor
     */
    num_count_impl::num_count_impl()
      : gr::block("num_count",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1,1, sizeof(float)))
    {}

    /*
     * Our virtual destructor.
     */
    num_count_impl::~num_count_impl()
    {
    }

    void
    num_count_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    num_count_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const float *in = (const float*) input_items[0];
        float *out = (float*) output_items[0];

        for(int i = 0; i < noutput_items; i++) {
          out[i] = in[i];
          //printf("in_size=%d\n", ninput_items.size());
         // printf("fin=%d\n", finished());
          //printf("global_counter=%d\n", global_counter++);
        }
        printf("global_counter=%d out_size=%d\n", global_counter++,  noutput_items);

        // Do <+signal processing+>
        // Tell runtime system how many input items we consumed on
        // each input stream.
        consume_each (noutput_items);

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace mymod */
} /* namespace gr */

