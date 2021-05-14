#pragma once

#include "dev_base.h"

namespace nebulaxi {

using i2c_address = uint16_t;
using i2c_data = std::vector<uint8_t>;
using i2c_segment = uint32_t;

enum class i2c_addressing { _7bit,
    _10bit };

struct dev_i2c_interface : dev_interface<dev_i2c_interface> {
    virtual ~dev_i2c_interface() noexcept = default;
};

struct dev_axi_i2c_interface
    : dev_axi_interface<dev_axi_i2c_interface, dev_i2c_interface> {
    virtual void configure(i2c_address, double, i2c_addressing) noexcept = 0;
    virtual void set_address(i2c_address) noexcept = 0;
    virtual i2c_address get_address() const noexcept = 0;
    virtual void set_addressing(i2c_addressing) noexcept = 0;
    virtual i2c_addressing get_addressing() const noexcept = 0;
    virtual void set_frequency(double) noexcept = 0;
    virtual double get_frequency() const noexcept = 0;
    virtual ~dev_axi_i2c_interface() noexcept = default;
};

namespace detail {
    template <typename dev_parent_type>
    class dev_i2c_base : public dev_base<dev_axi_i2c_interface, dev_i2c_interface, dev_parent_type> {
    public:
        dev_i2c_base() = default;
        dev_i2c_base(typename dev_base<dev_axi_i2c_interface, dev_i2c_interface, dev_parent_type>::axi_interface io,
            typename dev_base<dev_axi_i2c_interface, dev_i2c_interface, dev_parent_type>::parent_functor fn, i2c_address address, double frequency = double(400000), i2c_addressing addressing = i2c_addressing::_7bit)
            : dev_base<dev_axi_i2c_interface, dev_i2c_interface, dev_parent_type> { io, fn }
            , m_address { address }
            , m_frequency { frequency }
            , m_addressing { addressing }
        {
        }
        dev_i2c_base(typename dev_base<dev_axi_i2c_interface, dev_i2c_interface, dev_parent_type>::axi_interface io,
            i2c_address address, double frequency = double(400000), i2c_addressing addressing = i2c_addressing::_7bit)
            : dev_base<dev_axi_i2c_interface, dev_i2c_interface, dev_parent_type> { io }
            , m_address { address }
            , m_frequency { frequency }
            , m_addressing { addressing }
        {
        }

    protected:
        i2c_address m_address {};
        double m_frequency {};
        i2c_addressing m_addressing {};
    };

} // namespace detail

class dev_axi_i2c final : public detail::dev_axi_base<dev_axi_i2c_interface>, public detail::dev_base_creator<dev_axi_i2c> {
public:
    dev_axi_i2c() = default;
    dev_axi_i2c(uint64_t axi_offset)
        : dev_axi_base { axi_offset }
    {
    }
    void configure(i2c_address address, double frequency, i2c_addressing addressing) noexcept final { }
    uint64_t get_axi_offset() const noexcept final { return m_axi_offset; }
    void set_address(i2c_address address) noexcept final { }
    i2c_address get_address() const noexcept final { return {}; }
    void set_addressing(i2c_addressing addressing) noexcept final { }
    i2c_addressing get_addressing() const noexcept final { return {}; }
    void set_frequency(double frequency) noexcept final { }
    double get_frequency() const noexcept final { return {}; }
    std::size_t write(const i2c_data& data) final { return {}; }
    i2c_data read() final { return {}; }
};

class dev_i2c_mux : public detail::dev_i2c_base<dev_i2c_mux>, public detail::dev_base_creator<dev_i2c_mux> {
    i2c_segment m_segment {};

public:
    dev_i2c_mux() = default;
    dev_i2c_mux(axi_interface io, i2c_segment segment, i2c_address address, double frequency = double(400000),
        i2c_addressing addressing = i2c_addressing::_7bit)
        : dev_i2c_base { io, address, frequency, addressing }
        , m_segment { segment }
    {
    }
    dev_i2c_mux(axi_interface io, parent_functor fn, i2c_segment segment, i2c_address address, double frequency = double(400000),
        i2c_addressing addressing = i2c_addressing::_7bit)
        : dev_i2c_base { io, fn, address, frequency, addressing }
        , m_segment { segment }
    {
    }
    std::size_t write(const i2c_data& data) final
    {
        assert(m_io.use_count() != 0 && m_io.get() != nullptr);
        call_parent();
        m_io->configure(m_address, m_frequency, m_addressing);
        return m_io->write(data);
    }
    i2c_data read() final
    {
        assert(m_io.use_count() != 0 && m_io.get() != nullptr);
        call_parent();
        m_io->configure(m_address, m_frequency, m_addressing);
        return m_io->read();
    }
    void operator()() { segment(); }
    virtual void segment() { call_parent(); }
};

class dev_i2c : public detail::dev_i2c_base<dev_i2c_mux>, public detail::dev_base_creator<dev_i2c> {
public:
    dev_i2c() = default;
    dev_i2c(axi_interface io, i2c_address address, double frequency = double(400000),
        i2c_addressing addressing = i2c_addressing::_7bit)
        : dev_i2c_base { io, address, frequency, addressing }
    {
    }
    dev_i2c(axi_interface io, parent_functor fn, i2c_address address, double frequency = double(400000),
        i2c_addressing addressing = i2c_addressing::_7bit)
        : dev_i2c_base { io, fn, address, frequency, addressing }
    {
    }
    std::size_t write(const i2c_data& data) final
    {
        assert(m_io.use_count() != 0 && m_io.get() != nullptr);
        call_parent();
        m_io->configure(m_address, m_frequency, m_addressing);
        return m_io->write(data);
    }
    i2c_data read() final
    {
        assert(m_io.use_count() != 0 && m_io.get() != nullptr);
        call_parent();
        m_io->configure(m_address, m_frequency, m_addressing);
        return m_io->read();
    }
};

}
