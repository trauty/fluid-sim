#include "shader-file.h"

std::string getFileContent(const char* path)
{
    std::ifstream in(path, std::ios::in | std::ios::binary);
    if (in)
    {
        std::string content;
        in.seekg(0, std::ios::end);
        content.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&content[0], content.size());
        in.close();
        return content;
    }

    throw errno;
}