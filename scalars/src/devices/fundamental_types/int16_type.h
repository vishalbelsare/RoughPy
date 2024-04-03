#ifndef INT16_TYPE_H_
#define INT16_TYPE_H_
#include "devices/fundamental_type.h"
#include <roughpy/core/types.h>
#include <roughpy/core/macros.h>
namespace rpy {
namespace devices {
extern template class RPY_LOCAL FundamentalType<int16_t>;
extern RPY_LOCAL const FundamentalType<int16_t> int16_type;
}
}
#endif // INT16_TYPE_H_