/** \file FFTOperator.h
    \brief Device independent implementation of the FFT operator.

    The file FFTOperator.h is a device independent implementation of an operator perfoming a Cartesian FFT.
    To simplify the actual instantiation we refer to 
    - the class(/file) hoFFTOperator(/.h) for a cpu instantiated operator using the hoNDArray class
    - the class(/file) cuFFTOperator(/.h) for a gpu instantiated operator using the cuNDArray class
*/

#pragma once

#include "linearOperator.h"

namespace Gadgetron{

  template <class ARRAY_TYPE, class FFT> class FFTOperator : public linearOperator<ARRAY_TYPE>
  {
  public:
    
    FFTOperator() : linearOperator<ARRAY_TYPE>() {}
    virtual ~FFTOperator() {}
    
    virtual void mult_M( ARRAY_TYPE *in, ARRAY_TYPE *out, bool accumulate = false )
    {
      if( in == 0x0 || out == 0x0 ){
	BOOST_THROW_EXCEPTION(runtime_error("Error: FFTOperator::mult_M(): illegal array pointer provided"));
      }
      
      if( accumulate ){
	ARRAY_TYPE tmp(in);
	FFT::instance().fft(tmp);
    	*out += tmp;
      }
      else{
	*out = *in;
	FFT::instance().fft(out);
      }
    }
    
    virtual void mult_MH( ARRAY_TYPE *in, ARRAY_TYPE *out, bool accumulate = false )
    {
      if( in == 0x0 || out == 0x0 ){
	BOOST_THROW_EXCEPTION(runtime_error("Error: FFTOperator::mult_M(): illegal array pointer provided"));
      }
      
      if( accumulate ){
	ARRAY_TYPE tmp(in);
	FFT::instance().ifft(tmp);
    	*out += tmp;
      }
      else{
	*out = *in;
	FFT::instance().ifft(out);
      }
    }
    
    virtual void mult_MH_M( ARRAY_TYPE *in, ARRAY_TYPE *out, bool accumulate = false )
    {
      if( accumulate )
    	*out += *in;
      else 
	*out = *in;           
    }
    
    virtual boost::shared_ptr< linearOperator< ARRAY_TYPE > > clone()
    {
      return linearOperator<ARRAY_TYPE>::clone(this);
    }
  };
}
