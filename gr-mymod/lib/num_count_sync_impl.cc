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
#include "num_count_sync_impl.h"
int global_counter_sync=0;

namespace gr {
  namespace mymod {

    num_count_sync::sptr
    num_count_sync::make()
    {
      return gnuradio::get_initial_sptr
        (new num_count_sync_impl());
    }

    /*
     * The private constructor
     */
    num_count_sync_impl::num_count_sync_impl()
      : gr::sync_block("num_count_sync",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1,1, sizeof(float)))
    {}

    /*
     * Our virtual destructor.
     */
    num_count_sync_impl::~num_count_sync_impl()
    {
    }

    int
    num_count_sync_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const float *in = (const float*) input_items[0];
        float *out = (float*) output_items[0];
        
        for(int i = 0; i < noutput_items; i++) {
          out[i] = in[i];
          //printf("in_size=%d\n", ninput_items.size());
         // printf("fin=%d\n", finished());
          
        }
          printf("global_counter2=%d   noutput_items=%d \n", global_counter_sync++,noutput_items);
        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace mymod */
} /* namespace gr */

