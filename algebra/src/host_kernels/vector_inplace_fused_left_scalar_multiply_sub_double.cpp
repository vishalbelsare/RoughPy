
#include "vector_inplace_fused_left_scalar_multiply_sub.h"

using namespace rpy;
using namespace rpy::algebra;

namespace rpy { namespace algebra {

//template class VectorInplaceBinaryWithScalarOperator<rpy::devices::operators::FusedLeftScalarMultiplySub, double>;

}

namespace devices {

template class HostKernel<algebra::VectorInplaceBinaryWithScalarOperator<
    rpy::devices::operators::FusedLeftScalarMultiplySub, double>>;

}
}
