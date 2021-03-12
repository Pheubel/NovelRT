//
// Created by matth on 12/03/2021.
//

#ifndef NOVELRT_LLGRAPHICSRESOURCEVIEWCONTAINER_H
#define NOVELRT_LLGRAPHICSRESOURCEVIEWCONTAINER_H

#include <memory>
#include <utility>

namespace NovelRT::Experimental::Graphics
{
    class LLGraphicsResource;

    template<typename T> class LLGraphicsResourceViewContainer
    {
    private:
        std::shared_ptr<LLGraphicsResource> _ptr;

    public:
        LLGraphicsResourceViewContainer(std::shared_ptr<LLGraphicsResource> ptr) noexcept : _ptr(std::move(ptr))
        {
        }

        [[nodiscard]] constexpr T* operator ->()
        {
            return reinterpret_cast<T*>(_ptr.get());
        }
    };
} // namespace NovelRT::Experimental::Graphics

#endif // NOVELRT_LLGRAPHICSRESOURCEVIEWCONTAINER_H
