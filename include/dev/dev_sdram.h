#pragma once

#include "dev_base.h"

namespace nebulaxi {

class dev_axi_sdram final {
    uint64_t m_axi_offset {};

public:
    dev_axi_sdram() = default;
    dev_axi_sdram(uint64_t axi_offset)
        : m_axi_offset { axi_offset }
    {
    }
};

}
