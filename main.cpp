#include <iostream>
#include <vector>
#include <ranges>
#include <print>

class ImageData {
    private:
        char magic_number[3];
        int width;
        int hight;
        short maxval;
        std::vector<unsigned char> bytes;
        std::ranges::stride_view<std::ranges::drop_view<std::ranges::ref_view<std::vector<unsigned char>>>> red, green, blue;
};

int main()
{
    std::println("hey there");
    return 0;
}
