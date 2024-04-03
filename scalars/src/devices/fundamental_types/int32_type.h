#ifndef INT32_TYPE_H_
#define INT32_TYPE_H_
#include "devices/fundamental_type.h"
#include <roughpy/core/types.h>
#include <roughpy/core/macros.h>
namespace rpy {
namespace devices {
extern template class RPY_LOCAL FundamentalType<int32_t>;
extern RPY_LOCAL const FundamentalType<int32_t> int32_type;
}
}
#endif // INT32_TYPE_H_