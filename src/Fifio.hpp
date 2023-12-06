#include <JuceHeader.h>
#include <format>
#include <string>
#include <functional>
#include <vector>
#include <ranges>
#include <numeric>

using namespace juce;

template<typename T>
class Fifo {
public:
    Fifo(int n) : fifo(n), buffer(n) {}

    auto write(const T *src, size_t n) noexcept -> int {
        auto h = fifo.write(n);
        auto w = 0;
        if (h.blockSize1 > 0) {
            copy(buffer.data() + h.startIndex1, src, h.blockSize1);
            w += h.blockSize1;
        }

        if (h.blockSize2 > 0) {
            copy(buffer.data() + h.startIndex2, src, h.blockSize2);
            w += h.blockSize2;
        }

        return w;
    }

    auto read(T *dst, size_t n) noexcept -> int {
        auto h = fifo.read(n);
        auto r = 0;

        if (h.blockSize1 > 0) {
            copy(dst, buffer.data() + h.startIndex1, h.blockSize1);
            r += h.blockSize1;
        }

        if (h.blockSize2 > 0) {
            copy(dst, buffer.data() + h.startIndex2, h.blockSize2);
            r += h.blockSize2;
        }

        return r;
    }

private:
    template<typename T>
    constexpr inline auto copy(T *dst, const T *src, size_t n) noexcept -> void {
        memcpy(dst, src, n * sizeof(T));
    }

    AbstractFifo fifo;
    std::vector<T> buffer;
};