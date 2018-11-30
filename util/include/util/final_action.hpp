#pragma once

#include <utility>

namespace util {

template <class F>
class final_action
{
public:
    explicit final_action(F f) noexcept
      : f_(std::move(f)), invoke_(true) {}

    final_action(final_action&& other) noexcept
     : f_(std::move(other.f_)),
       invoke_(other.invoke_)
    {
        other.invoke_ = false;
    }

    final_action(const final_action&) = delete;
    final_action& operator=(const final_action&) = delete;

    ~final_action() noexcept
    {
        if (invoke_) f_();
    }

private:
    F f_;
    bool invoke_;
};

template <class F>
inline final_action<F> finally(const F& f) noexcept
{
    return final_action<F>(f);
}

template <class F>
inline final_action<F> finally(F&& f) noexcept
{
    return final_action<F>(std::forward<F>(f));
}

} // util
