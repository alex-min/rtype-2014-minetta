#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Exception.h"
#include "SystemDefines.h"

class MapLoader
{


public:
    MapLoader(std::string const &map);
    ~MapLoader();

    typedef std::vector<std::vector<Int32> > tabInt;
    void        printMap();
    void        parseFile(std::string const &file);
    tabInt      &getMap();
    tabInt const&getMap() const;

private:
    bool        openFile(std::string const &file);
    bool        isLineValid(std::string const &line);
    void        putLineInMap(std::string const &line);


    unsigned int    _sizeLine;
    std::string     _valid;
    tabInt          _map;
    std::ifstream   *_file;

};

#endif // MAPLOADER_H
