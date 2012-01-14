#include "MapLoader.h"

MapLoader::MapLoader(std::string const &map)
{
    _file = NULL;
    _sizeLine = 0;
    _valid.assign("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    parseFile(map);
}

MapLoader::~MapLoader()
{

}

MapLoader::tabInt      &MapLoader::getMap()
{
    return (_map);
}

MapLoader::tabInt const&MapLoader::getMap() const
{
    return (_map);
}

bool    MapLoader::openFile(std::string const &file)
{
    _file = new std::ifstream(file.c_str());
    if ((*_file))
        return (true);
    return (false);
}

bool    MapLoader::isLineValid(std::string const &line)
{
    if (_sizeLine == 0)
        _sizeLine = line.size();
    if (_sizeLine != line.size() || line.size() == 0)
        throw Exception("Invalid line in Map file");

    for (unsigned int i = 0; i < line.size(); i++)
        if (_valid.find(line[i]) == std::string::npos)
            return (false);
    return (true);
}

void    MapLoader::parseFile(std::string const &file)
{
    if (openFile(file) == false)
        throw Exception("Cannot open map file");

    std::string line;
    while ( std::getline((*_file), line) )
    {
        if (_file->bad())
            throw Exception("Can't read Map file");
        if (isLineValid(line) == true)
            putLineInMap(line);
    }
}



void    MapLoader::putLineInMap(std::string const &line)
{
    std::vector<Int32>  newLine;

    for (unsigned int i = 0; i < line.size(); i++)
        newLine.push_back(static_cast<int>(_valid.find(line[i])));
    _map.push_back(newLine);
}

void    MapLoader::printMap()
{
    tabInt::iterator                it;
    std::vector<Int32>::iterator    i;

    for (it = _map.begin(); it != _map.end(); ++it)
    {
        for (i = (*it).begin(); i != (*it).end(); ++i)
            std::cout << (*i);
        std::cout << std::endl;
    }
}
