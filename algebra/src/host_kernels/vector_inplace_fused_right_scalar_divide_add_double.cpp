
#include "vector_inplace_fused_right_scalar_divide_add.h"

using namespace rpy;
using namespace rpy::algebra;

namespace rpy { namespace algebra {

template class VectorInplaceBinaryWithScalarOperator<rpy::devices::operators::FusedRightScalarDivideAdd, double>;

}

namespace devices {

template class HostKernel<algebra::VectorInplaceBinaryWithScalarOperator<
    rpy::devices::operators::FusedRightScalarDivideAdd, double>>;

}
}
