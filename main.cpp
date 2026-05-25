#include <iostream>
#include <vector>
#include <ranges>
#include <string>
#include <span>
#include <fstream>
#include <sstream>
#include <optional>

class ImageData
{
private:
    char magic_number[2];
    int width;
    int hight;
    short maxval;
    std::string image_string;
    using ColorViewType = decltype(std::declval<std::span<unsigned char>>() | std::views::drop(0) | std::views::stride(3));
    std::optional<ColorViewType> red, green, blue;

    std::string readFile(const std::string &file_path)
    {
        std::ifstream file(file_path); // reads the file
        std::ostringstream string_stream;
        string_stream << file.rdbuf(); // streams it into a string stream
        file.close();
        return string_stream.str(); // turns the stream into a string
    }

    void skipWhitespace(int &string_position)
    { // updates string position to end of whitespace
        while (isspace(image_string[string_position]))
        {
            string_position++;
        }
    }

    int getDecimalFromString(int &string_position)
    { // returns the decimal, or 0 if it fails. keeps string position updated
        int starting_position = string_position;
        std::string string_of_decimal;
        while (!isspace(image_string[string_position]))
        {
            string_position++;
        }
        try
        {
            return std::stoi(image_string.substr(starting_position, string_position));
        }
        catch (...)
        {
            return 0;
        }
    }

public:
    ImageData(const std::string &file_path)
    {
        image_string = readFile(file_path);
        int string_position = 0; // helps to keep track of where I'm at while extracting data

        // get the magic number
        magic_number[0] = image_string[0];
        string_position++;
        magic_number[1] = image_string[1];
        string_position++;
        skipWhitespace(string_position);

        // get width
        width = getDecimalFromString(string_position);
        skipWhitespace(string_position);
        // get hight
        hight = getDecimalFromString(string_position);
        skipWhitespace(string_position);

        // get maxval
        maxval = getDecimalFromString(string_position);
        if (maxval < 0 || maxval >= 65536)
        {
            maxval = 0;
        }

        string_position++; // next char should be whitespace

        // create red, green, and blue views
        std::span<unsigned char> full_file(reinterpret_cast<unsigned char *>(image_string.data()), image_string.size()); // gotta read it differently (unsigned)
        std::span<unsigned char> bytes = full_file.subspan(string_position);
        // red
        red = bytes | std::views::drop(0) | std::views::stride(3);
        // green
        green = bytes | std::views::drop(1) | std::views::stride(3);
        // blue
        blue = bytes | std::views::drop(2) | std::views::stride(3);
    }

    std::string getMagicNumber()
    {
        return magic_number;
    }

    int getWidth()
    {
        return width;
    }

    int getHight()
    {
        return hight;
    }

    std::string getString()
    {
        return image_string;
    }

    // Adjust Red, Green, and Blue by Multiplier
    void adjustRedByMultiplier(float multiplier)
    {
        for (unsigned char &byte : *red)
        {
            if (byte * multiplier > maxval)
            {
                byte = maxval;
            }
            else
            {
                byte *= multiplier;
            }
        }
    }
    void adjustGreenByMultiplier(float multiplier)
    {
        for (unsigned char &byte : *green)
        {
            if (byte * multiplier > maxval)
            {
                byte = maxval;
            }
            else
            {
                byte *= multiplier;
            }
        }
    }
    void adjustBlueByMultiplier(float multiplier)
    {
        for (unsigned char &byte : *blue)
        {
            if (byte * multiplier > maxval)
            {
                byte = maxval;
            }
            else
            {
                byte *= multiplier;
            }
        }
    }
};

int main()
{
    std::cout << "Please type the input file location and press [ENTER]:\n";
    std::string input_file_location;
    std::getline(std::cin, input_file_location);

    std::cout << "Please type the output file location and press [ENTER]:\n";
    std::string output_file_location;
    std::getline(std::cin, output_file_location);

    ImageData image = ImageData(input_file_location);
    std::ofstream output_file(output_file_location);

    std::cout << "Magic Number: " << image.getMagicNumber() << "\n";
    std::cout << "Width: " << image.getWidth() << "\n";
    std::cout << "Hight: " << image.getHight() << "\n";

    float red_multiplier;
    float green_multiplier;
    float blue_multiplier;

    std::cout << "Enter the red multiplier, then green multiplier, then blue multiplier:\n";
    std::cin >> red_multiplier;
    std::cin >> green_multiplier;
    std::cin >> blue_multiplier;

    // make adjustments
    image.adjustRedByMultiplier(red_multiplier);
    image.adjustGreenByMultiplier(green_multiplier);
    image.adjustBlueByMultiplier(blue_multiplier);

    // write to the file
    output_file << image.getString();

    output_file.close();
    return 0;
}
