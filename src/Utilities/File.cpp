#include <File.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <sys/stat.h>

namespace REKT
{
    const char DirectorySeparatorChar = '\\';
    const char AltDirectorySeparatorChar = '/';
    const char VolumeSeparatorChar = ':';

    std::string File::ReadAllText(const std::string& filepath)
    {
        std::ifstream file(filepath);
        std::string str;
        std::string file_contents;

        while (std::getline(file, str))
        {
            file_contents += str;
            file_contents.push_back('\n');
        }

        if(file.is_open())
            file.close();
        return file_contents; 
    }

    std::vector<unsigned char> File::ReadAllBytes(const std::string& filepath)
    {
        std::vector<unsigned char> bytes;
        std::ifstream file(filepath, std::ios_base::in | std::ios_base::binary);
        unsigned char ch = file.get();

        while (file.good())
        {
            bytes.push_back(ch);
            ch = file.get();
        }

        file.close();
        return bytes;
    }

    void File::WriteAllText(const std::string& filepath, const std::string& text)
    {
        std::ofstream outfile;
        std::string file(filepath);
        outfile.open(file);
        outfile << text; 
        outfile.close();
    }

    void File::WriteAllBytes(const std::string& filepath, unsigned char* bytes, size_t size)
    {
        std::ofstream file(filepath);

        if(file)
        {
            file.write(reinterpret_cast<const char*>(bytes), size);
        }

        if(file.is_open())
            file.close();
    }

    size_t File::GetSize(const std::string& filepath)
    {
        struct stat stat_buf;
        int rc = stat(filepath.c_str(), &stat_buf);
        return rc == 0 ? stat_buf.st_size : -1;
    }

    bool File::Exists(const std::string& filepath)
    {
        struct stat buffer;   
        return (stat(filepath.c_str(), &buffer) == 0); 
    }

    std::string File::GetName(const std::string& filepath)
    {
        if (filepath.size() > 0) 
        {
            size_t length = filepath.size();

            for (size_t i = length; --i > 0;) 
            {
                char ch = filepath[i];

                if (ch == DirectorySeparatorChar || ch == AltDirectorySeparatorChar || ch == VolumeSeparatorChar)
                {
                    return filepath.substr(i + 1, length - i - 1);
                }
            }
        }
        return filepath;
    }

    std::string File::GetExtension(const std::string& filepath) 
    {
        if (filepath.size() == 0)
            return "";

        size_t length = filepath.size();
        
        for (int i = length; --i > 0;) 
        {
            char ch = filepath[i];
        
            if (ch == '.')
            {
                if (i != length - 1)
                    return filepath.substr(i, length - i);
                else
                    return "";
            }
        
            if (ch == DirectorySeparatorChar || ch == AltDirectorySeparatorChar || ch == VolumeSeparatorChar)
                break;
        }
        
        return "";
    }
}