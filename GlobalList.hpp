// GlobalList.hpp by siklerx @ Github
#pragma once
#include <vector>
#include <shared_mutex>
#include <cstddef>

template<typename T>
class GlobalList {
public:
    // Add an element (thread-safe)
    void Push(const T& item) {
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        m_data.push_back(item);
    }

    void Push(T&& item) {
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        m_data.push_back(std::move(item));
    }

    // Emplace directly
    template<typename... Args>
    void Emplace(Args&&... args) {
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        m_data.emplace_back(std::forward<Args>(args)...);
    }

    // Read-only access: returns a copy of the current list (safe for iteration)
    [[nodiscard]] std::vector<T> GetSnapshot() const {
        std::shared_lock<std::shared_mutex> lock(m_mutex);
        return m_data; // Copy is intentional for safety
    }

    // Alternative: pass a functor to operate on the list without copying (C++17)
    template<typename Func>
    void ForEach(Func&& f) const {
        std::shared_lock<std::shared_mutex> lock(m_mutex);
        for (const auto& item : m_data) {
            f(item);
        }
    }

    // Clear all entries
    void Clear() {
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        m_data.clear();
    }

    // Get current size
    [[nodiscard]] size_t Size() const {
        std::shared_lock<std::shared_mutex> lock(m_mutex);
        return m_data.size();
    }

    // Singleton access
    static GlobalList& Instance() noexcept {
        static GlobalList instance;
        return instance;
    }

    GlobalList(const GlobalList&) = delete;
    GlobalList& operator=(const GlobalList&) = delete;
    GlobalList(GlobalList&&) = delete;
    GlobalList& operator=(GlobalList&&) = delete;

private:
    mutable std::shared_mutex m_mutex;
    std::vector<T> m_data;

    GlobalList() = default;
    ~GlobalList() = default;
};
