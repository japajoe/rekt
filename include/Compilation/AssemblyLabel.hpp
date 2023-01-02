#ifndef ASSEMBLYLABEL_HPP
#define ASSEMBLYLABEL_HPP

#include <string>
#include <map>

namespace VoltLang
{
    class AssemblyLabel
    {
    public:
        std::map<std::string,uint64_t> labels;

        bool Add(const std::string& label, uint64_t location)
        {
            if(labels.count(label))
                return false;

            labels[label] = location;

            return true;
        }
    };
}
#endif