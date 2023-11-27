#pragma once

#include "Timer.hpp"
#include <memory>
#include <vector>

/*
    TODO: 
        optimize your bullshit plz, i will poke my eyes if i see this vector traversal once more

    what's there to optimize you ask?
     -> space complexity, why keep items that are out of time already? preparing a zombie attack?
     -> time complexity, i mean, you can do better with a heap like tree .. 
            that whole stuff shall be amortized O(1) for put and get..
*/

template <typename T>
struct Timeline 
{
    void put(std::shared_ptr<T> item, float tStart, float tEnd);
    std::vector<std::shared_ptr<T>> get();

private:
    struct _Item {
        std::shared_ptr<T> data;
        float t_beg;
        float t_end;
    };

    Timer::Chronometre m_timer;
    std::vector<_Item> m_container;

    float _get_curr_time() {
        return m_timer.elapsed<Timer::millisecond>() / 1000.0f;
    }
};

// ---- Implementation ----
template<typename T> inline 
    void Timeline<T>::put(std::shared_ptr<T> item, float tStart, float tEnd)
{
    m_container.push_back({ item, tStart, tEnd });
}

template<typename T> inline 
    std::vector<std::shared_ptr<T>> Timeline<T>::get()
{
    float t = _get_curr_time();

    std::vector<std::shared_ptr<T>> results;
    for (const _Item& item : m_container) {
        if (item.t_beg <= t && t <= item.t_end) {
            results.push_back(item.data);
        }
    }

    return results;
}
