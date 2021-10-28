/*

MIT License

Copyright (c) 2021 Nebula-XI

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#pragma once

#include <cassert>
#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

namespace nebulaxi {

template <typename dev_interface_type>
struct dev_interface {
    using dev_shared = typename std::shared_ptr<dev_interface_type>;
    virtual std::size_t write(const std::vector<uint8_t>&) = 0;
    virtual std::vector<uint8_t> read() = 0;
    virtual ~dev_interface() noexcept = default;
};

template <typename dev_axi_interface_type, typename dev_interface_type>
struct dev_axi_interface : dev_interface_type {
    using axi_shared = typename std::shared_ptr<dev_axi_interface_type>;
    virtual uint64_t get_axi_offset() const noexcept = 0;
    virtual ~dev_axi_interface() noexcept = default;
};

template <typename dev_type, typename... args_type>
auto make_dev(args_type&&... args)
{
    return std::make_shared<dev_type>(std::forward<args_type>(args)...);
}

namespace detail {
    template <typename dev_axi_interface_type>
    class dev_axi_base : public dev_axi_interface_type {
    public:
        using dev_interface = typename dev_axi_interface_type::axi_shared;
        dev_axi_base() = default;
        dev_axi_base(uint64_t axi_offset)
            : m_axi_offset { axi_offset }
        {
        }

    protected:
        uint64_t m_axi_offset {};
    };
    template <typename dev_axi_interface_type, typename dev_interface_type, typename dev_parent_type>
    class dev_base : public dev_interface_type {
    public:
        using dev_interface = typename dev_axi_interface_type::dev_shared;
        using axi_interface = typename dev_axi_interface_type::axi_shared;
        using parent_functor = std::shared_ptr<dev_parent_type>;
        dev_base() = default;
        template <typename axi_interface_type = axi_interface, typename parent_functor_type = parent_functor>
        dev_base(axi_interface_type&& io, parent_functor_type&& parent_functor)
            : m_io { std::forward<axi_interface_type>(io) }
            , m_parent_functor { std::forward<parent_functor_type>(parent_functor) }
        {
        }
        template <typename axi_interface_type = axi_interface>
        dev_base(axi_interface_type&& io)
            : m_io { std::forward<axi_interface_type>(io) }
        {
        }

    protected:
        axi_interface m_io {};
        void call_parent()
        {
            if (m_parent_functor) {
                auto parent_functor = *m_parent_functor;
                parent_functor();
            }
        }

    private:
        parent_functor m_parent_functor {};
    };
    template <typename dev_creator_type>
    class dev_base_creator {
    public:
        template <typename... args_type>
        static auto create(args_type&&... args) { return make_dev<dev_creator_type>(std::forward<args_type>(args)...); }
    };

}

}
