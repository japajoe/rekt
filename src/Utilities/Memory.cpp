#include <Memory.hpp>
#include <IO/File.hpp>
#include <cstring>

#if defined(_WIN32)
#include <windows.h>
#endif

#if defined(__linux__) || defined(__FreeBSD__)
#include <link.h>
#endif

namespace VoltLang
{
    struct VoltModuleInfo
    {
        const char *name;
        uintptr_t address;
    };

    static int volt_dl_callback(struct dl_phdr_info *info, size_t size, void *data)
    {
        if(info->dlpi_name[0] != '\0')
        {
            VoltModuleInfo *moduleInfo = reinterpret_cast<VoltModuleInfo *>(data);

            std::string path = std::string(info->dlpi_name);
            std::string filename = File::GetName(path);

            if(filename == moduleInfo->name)
            {
                moduleInfo->address = info->dlpi_addr;
            }
        }
        return 0;
    }

    #if defined(_WIN32)
    static void volt_get_module_handle(const char* name, uintptr_t* address)
    {
        *address = GetModuleHandle(name);
    }
    #endif

    #if defined(__linux__) || defined(__FreeBSD__)
    static void volt_get_module_handle(const char* name, uintptr_t* address)
    {
        VoltModuleInfo moduleInfo = {name, 0};
        dl_iterate_phdr(volt_dl_callback, &moduleInfo);
        *address = moduleInfo.address;
    }
    #endif

    //If you are on Mac, blame Apple for being so non accommodating towards anyone who hasn't paid for the privilege to build for their platform.
    //Alternatively, implement needed code here yourself and do a pull request :)
    #if defined(__APPLE__)
    static void volt_get_module_handle(const char* name, uintptr_t* address)
    {
        *address = 0;
    }
    #endif    

    std::vector<unsigned char> Memory::GetBytes(const std::string& value)
    {
        std::vector<unsigned char> bytes(value.begin(), value.end());
        return bytes;
    }

    std::vector<unsigned char> Memory::GetBytes(double value)
    {
        std::vector<unsigned char> bytes;
        bytes.resize(sizeof(double));
        memcpy(&bytes[0], &value, sizeof(double));
        return bytes;
    }

    std::vector<unsigned char> Memory::GetBytes(int64_t value)
    {
        std::vector<unsigned char> bytes;
        bytes.resize(sizeof(int64_t));
        memcpy(&bytes[0], &value, sizeof(int64_t));
        return bytes;
    }

    std::vector<unsigned char> Memory::GetBytes(uint64_t value)
    {
        std::vector<unsigned char> bytes;
        bytes.resize(sizeof(uint64_t));
        memcpy(&bytes[0], &value, sizeof(uint64_t));
        return bytes;
    }

    uint64_t Memory::GetSizeInWords(uint64_t sizeInBytes)
    {
        return (sizeInBytes + SIZE_OF_WORD - 1) / SIZE_OF_WORD;
    }

    void Memory::GetModuleAddress(const std::string& name, uintptr_t *address)
    {
        volt_get_module_handle(name.c_str(), address);
    }
}