#pragma once

#include "dev_base.h"

namespace nebulaxi {

class dev_axi_gpio final {
    uint64_t m_axi_offset {};

public:
    dev_axi_gpio() = default;
    dev_axi_gpio(uint64_t axi_offset)
        : m_axi_offset { axi_offset }
    {
    }
};

}
