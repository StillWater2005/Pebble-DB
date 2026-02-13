#include "storage.h"
#include <fstream>
#include <cstdint>

Storage::Storage(const std::string &filename)
    : filename(filename) {}

long Storage::append(const std::string &key, const std::string &value)
{
    std::ofstream file(filename, std::ios::binary | std::ios::app);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file for writing: " + filename);
    }

    file.seekp(0, std::ios::end);
    long offset = file.tellp();

    uint32_t key_size = key.size();
    uint32_t value_size = value.size();

    if (!file.write(reinterpret_cast<char *>(&key_size), sizeof(key_size)))
        throw std::runtime_error("Failed to write to file.");

    if (!file.write(reinterpret_cast<char *>(&value_size), sizeof(value_size)))
        throw std::runtime_error("Failed to write to file.");

    if (!file.write(key.data(), key_size))
        throw std::runtime_error("Failed to write to file.");

    if (!file.write(value.data(), value_size))
        throw std::runtime_error("Failed to write to file.");

    file.flush();
    file.close();

    return offset;
}