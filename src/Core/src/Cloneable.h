#pragma once

namespace core {
    template<typename T>
    class Cloneable {
    public:
        virtual T *clone() = 0;
    };
}