#ifndef VOLT_FILE_HPP
#define VOLT_FILE_HPP

#include <string>
#include <vector>

namespace VoltLang
{
    class File
    {
    public:
        static std::string ReadAllText(const std::string& filepath);
        static std::vector<unsigned char> ReadAllBytes(const std::string& filepath);
        static void WriteAllText(const std::string& filepath, const std::string& text);
        static void WriteAllBytes(const std::string& filepath, unsigned char* bytes, size_t size);
        static size_t GetSize(const std::string& filepath);
        static bool Exists(const std::string& filepath);
        static std::string GetName(const std::string &filepath);
        static std::string GetExtension(const std::string &filepath);
    };
}
#endif