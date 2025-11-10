# 🧩 GlobalList — A Thread-Safe Global Container for Modern C++

![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)
![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)
![Thread-Safe](https://img.shields.io/badge/thread-safe-orange.svg)

`GlobalList<T>` is a lightweight, thread-safe, singleton-based container for managing global shared data across threads or modules — built with **modern C++17+**.

---

## 🚀 Features

- 🧵 **Fully thread-safe** using `std::shared_mutex`  
- 📦 **Global singleton** access per template type  
- ⚡ **Zero external dependencies** — standard C++ only  
- 🔄 **Copy-safe reads** with `GetSnapshot()`  
- 🧭 **In-place construction** using `Emplace()`  
- 🧰 **Functional iteration** with `ForEach(Func&&)`  
- 🧹 **RAII-style cleanup** (`Clear()` automatically releases memory)

---

### Usage
```cpp
#include <iostream>
#include "GlobalList.hpp"

struct Player {
    std::string name;
    int score;
};

int main() {
    // Add data (thread-safe)
    GlobalList<Player>::Instance().Emplace("Alice", 100);
    GlobalList<Player>::Instance().Push({"Bob", 75});

    // Iterate safely
    GlobalList<Player>::Instance().ForEach([](const Player& p) {
        std::cout << p.name << " -> " << p.score << std::endl;
    });

    // Snapshot access (copy)
    auto players = GlobalList<Player>::Instance().GetSnapshot();
    std::cout << "Total players: " << players.size() << std::endl;

    // Clear all
    GlobalList<Player>::Instance().Clear();
}
