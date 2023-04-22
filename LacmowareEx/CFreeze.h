#pragma once

#include <map>
#include <mutex>
#include <chrono>

template <typename T>
class CFreeze
{
private:
    static CFreeze<T> *m_instance;
    
    std::mutex m_mutex;
    std::map<T *, T> m_targets;

    void beginFreeze();
public:
    static CFreeze<T> *get();

    void add(T *ptr, T val);
    void remove(T *ptr);
};

template <typename T>
CFreeze<T> *CFreeze<T>::m_instance;

template<typename T>
inline void CFreeze<T>::beginFreeze()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        if (!m_mutex.try_lock())
        {
            continue;
        }

        for (const auto &[ptr, val] : m_targets)
        {
            if (ptr == nullptr)
            {
                continue;
            }

            *ptr = val;
        }

        m_mutex.unlock();
    }
}

template<typename T>
inline CFreeze<T> *CFreeze<T>::get()
{
    if (m_instance == nullptr)
    {
        m_instance = new CFreeze<T>();
        std::thread(beginFreeze).detach();
    }
    
    return m_instance;
}

template<typename T>
inline void CFreeze<T>::add(T *ptr, T val)
{
    m_targets.insert(std::pair(ptr, val));
}

template<typename T>
inline void CFreeze<T>::remove(T *ptr)
{
    m_mutex.lock();
    m_targets.erase(m_targets.find(ptr));
    m_mutex.unlock();
}
