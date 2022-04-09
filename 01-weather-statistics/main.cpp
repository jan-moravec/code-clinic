#include "WeatherStatistics.h"
#include <iostream>


int main(int numberOfParameters, char **parameters)
{
    try
    {
        Configuration configuration = ParseArguments(numberOfParameters, parameters);
        std::vector<std::filesystem::path> filePaths = GetFilePaths(configuration);
        std::vector<Data> data = FindData(configuration, filePaths);
        SortData(data);
        PrintData(data);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "Usage: ./weather-statistics.exe 'path/to/data' '2014_01_03 23:12:39' '2014_01_20 02:59:23'" << std::endl;
    }
}
