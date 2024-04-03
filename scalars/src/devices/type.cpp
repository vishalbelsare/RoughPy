//
// Created by sam on 3/30/24.
//

#include "devices/type.h"

#include <roughpy/platform/alloc.h>

#include "devices/device_handle.h"

#include "fundamental_types/int8_type.h"
#include "fundamental_types/int16_type.h"
#include "fundamental_types/int32_type.h"
#include "fundamental_types/int64_type.h"

#include "fundamental_types/uint8_type.h"
#include "fundamental_types/uint16_type.h"
#include "fundamental_types/uint32_type.h"
#include "fundamental_types/uint64_type.h"

#include "fundamental_types/half_type.h"
#include "fundamental_types/float_type.h"
#include "fundamental_types/double_type.h"

#include "fundamental_types/b_float_16_type.h"

using namespace rpy;
using namespace rpy::devices;

Type::Type(string_view id, string_view name, TypeInfo info, TypeTraits traits)
    : m_id(std::move(id)),
      m_name(std::move(name)),
      m_info(info),
      m_traits(traits)
{}

Type::~Type() = default;

Buffer Type::allocate(Device device, dimn_t count) const
{
    return device->alloc(m_info, count);
}

void* Type::allocate_single() const
{
    return aligned_alloc(m_info.alignment, m_info.bytes);
}

void Type::free_single(void* ptr) const { aligned_free(ptr); }

bool Type::supports_device(const Device& device) const noexcept { return true; }


const Type* devices::get_type(TypeInfo info)
{
    switch (info.code) {
        case TypeCode::Int:
            switch (info.bytes) {
                case 1: return &int8_type;
                case 2: return &int16_type;
                case 4: return &int32_type;
                case 8: return &int64_type;
                default: break;
            }
        case TypeCode::UInt:
            switch (info.bytes) {
                case 1: return &int8_type;
                case 2: return &int16_type;
                case 4: return &int32_type;
                case 8: return &int64_type;
                default: break;
            }
        case TypeCode::Float:
            switch (info.bytes) {
                case 2: return &half_type;
                case 4: return &float_type;
                case 8: return &double_type;
                default: break;
            }
        case TypeCode::BFloat:
            RPY_CHECK(info.bytes == 2);
            return &bfloat16_type;
        default: break;
    }

    RPY_THROW(
            std::runtime_error,
            "Only fundamental types can be read from TypeInfo"
    );
}
