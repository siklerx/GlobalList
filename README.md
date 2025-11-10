# GlobalList

`GlobalList<T>` is a thread-safe globally accessible list container (singleton) using C++17 `std::shared_mutex`.

### Features
- Thread-safe push operations (`Push`, `Emplace`)
- Safe read operations: `GetSnapshot()` returns a copy; `ForEach(Func)` iterates under shared lock
- Clear all entries `Clear()`, get current count `Size()`
- Singleton access via `Instance()`

### Usage
```cpp
#include "GlobalList.hpp"

// push items
GlobalList<int>::Instance().Push(10);
GlobalList<int>::Instance().Emplace(20);

// iterate
GlobalList<int>::Instance().ForEach([](int x){
    std::cout << x << std::endl;
});

// snapshot
auto snapshot = GlobalList<int>::Instance().GetSnapshot();
std::cout << "Size: " << snapshot.size() << std::endl;
