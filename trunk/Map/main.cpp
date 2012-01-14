#include "MapLoader.h"

int main()
{
    std::cout << "lol" << std::endl;
    try {
    MapLoader *tg = new MapLoader("../map_example.map");
    tg->printMap();
    }
    catch (Exception e) {
        std::cout << e.what() << std::endl;
    }

    return (0);
}
