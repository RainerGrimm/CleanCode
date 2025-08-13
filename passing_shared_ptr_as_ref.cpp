// Fahrudin Halilovic

#include <iostream>
#include <memory>
#include <cassert>

void update(std::shared_ptr<int>& ptr, int val)
{
    ptr = std::make_shared<int>(val);
    // ptr.reset(new int { val });
}

int main()
{
    auto ptr = std::make_shared<int>(10);
    auto ptrCopy = ptr;

    assert(*ptr == 10);
    update(ptr, 20);
    assert(*ptr == 20);
    assert(*ptrCopy == 10);

    auto& ptrRef = ptr;
    update(ptr, 30);
    assert(*ptr == 30);
    assert(*ptrRef == 30);

    update(ptrRef, 40);
    assert(*ptr == 40);
    assert(*ptrRef == 40);

    return 0;
}