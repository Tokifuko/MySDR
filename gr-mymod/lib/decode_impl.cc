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
#include "decode_impl.h"

 //#define ONES_LEN       20
 //#define BIT_LEN        100

 int iOnesLen_glob, iBitLen_glob;

 int iOnesCounter=0;
 int iZeroCounter=0;
 bool bDataRxFlag=false; 


namespace gr {
  namespace mymod {

    decode::sptr
    decode::make(int iOnesLen, int iBitLen)
    {
      return gnuradio::get_initial_sptr
        (new decode_impl(iOnesLen, iBitLen));
    }

    /*
     * The private constructor
     */
    decode_impl::decode_impl(int iOnesLen, int iBitLen)
      : gr::sync_block("decode",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1,1, sizeof(char)))
    {
      iOnesLen_glob=iOnesLen;
      iBitLen_glob=iBitLen;
      printf( "1=%d 2=%d \n",iOnesLen,iBitLen);
    }

    /*
     * Our virtual destructor.
     */
    decode_impl::~decode_impl()
    {
    }

    int
    decode_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const char *in = (const char *) input_items[0];
        char *out = (char *) output_items[0];

        for(int i = 0; i < noutput_items; i++) 
         {
        /*----------zero--------------------*/
          if ((in[i]==0) & bDataRxFlag)
          {
            iZeroCounter++;
            if (iOnesCounter!=0) // hi-to-low egle
            {
              if (iOnesCounter<iOnesLen_glob) printf("0");
              if (iOnesCounter>=iOnesLen_glob) printf("1");
              iOnesCounter=0;
            }
            if (iZeroCounter>iBitLen_glob)
            {
              bDataRxFlag=false;
              printf("\n");
            } 
          } 
          /*----------ones-------------------*/
          if (in[i]==1)
          {
            iOnesCounter++;
            iZeroCounter=0;
            bDataRxFlag=true;
          } 

          /*----------Signal processing-------------------*/
          out[i] = in[i];
        }

        

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace mymod */
} /* namespace gr */

