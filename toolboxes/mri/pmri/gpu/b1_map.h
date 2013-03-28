#pragma once

#include "gpupmri_export.h"
#include "cuNDArray.h"
#include "vector_td.h"
#include "complext.h"

#include <boost/smart_ptr.hpp>

namespace Gadgetron{

  //
  // Estimate b1 map
  //
  template<class REAL, unsigned int D> EXPORTGPUPMRI boost::shared_ptr< cuNDArray<complext<REAL> > >
  estimate_b1_map( cuNDArray<complext<REAL> > *data, int target_coils = -1);
}
