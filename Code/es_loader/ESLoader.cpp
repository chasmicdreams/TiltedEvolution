#include "ESLoader.h"

#include <filesystem>
namespace fs = std::filesystem;

ESLoader::ESLoader(String aDirectory) 
    : m_directory(std::move(aDirectory))
{
}

bool ESLoader::BuildFileList()
{
    if (!FindFiles())
        return false;

    if (!SortPlugins())
        return false;

    return true;
}

bool ESLoader::FindFiles()
{
    if (m_directory.empty())
    {
        spdlog::error("Directory string is empty.");
        return false;
    }

    for (const auto& entry : fs::directory_iterator(m_directory))
    {
        String filename = entry.path().filename().string().c_str();

        const char* fileExtension = strrchr(filename.c_str(), '.');
        if (!fileExtension)
        {
            spdlog::warn("File extension for file {} not found.", filename);
            continue;
        }

        if (strlen(fileExtension) != 4)
        {
            spdlog::warn("File found with less or more than 3 characters in the extension ({}).", filename);
            continue;
        }

        if (tolower(fileExtension[1]) != 'e' || tolower(fileExtension[2]) != 's')
        {
            spdlog::warn("File found without 'es' in extension ({}).", filename);
            continue;
        }

        const char extensionEnd = tolower(fileExtension[3]);
        switch (extensionEnd)
        {
        case 'm':
            m_esmFilenames.push_back(filename);
            break;
        case 'p':
            m_espFilenames.push_back(filename);
            break;
        case 'l':
            m_eslFilenames.push_back(filename);
            break;
        default:
            spdlog::warn("File extension ends in an unknown letter ({})", filename);
            break;
        }
    }

    return true;
}

bool ESLoader::SortPlugins()
{
    DEBUG_BREAK;

    // TODO: sort plugins
    return true;
}

