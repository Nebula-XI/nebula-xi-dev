#pragma once

#include "dev_base.h"

namespace nebulaxi {

class unit_dev_axi_spi final {
    uint64_t m_axi_offset {};
    uint32_t m_chip_select {};
    double m_frequency {};

public:
    unit_dev_axi_spi() = default;
    unit_dev_axi_spi(uint64_t axi_offset)
        : m_axi_offset { axi_offset }
    {
    }
};

}
