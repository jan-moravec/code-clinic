#include <algorithm>
#include <chrono>
#include <ctime>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>

struct Configuration
{
    std::filesystem::path pathToData;
    std::chrono::system_clock::time_point beginDateTime;
    std::chrono::system_clock::time_point endDateTime;
};

struct Data
{
    std::chrono::system_clock::time_point dateTime{};
    double airTemperature{};
    double barometricPressure{};
    double dewPoint{};
    double relativeHumidity{};
    double windDirection{};
    double windGust{};
    double windSpeed{};
};

Configuration ParseArguments(int numberOfParameters, char **parameters);
std::chrono::system_clock::time_point ParseDateTime(std::string_view dateTime);
std::string DateTimeToString(std::chrono::system_clock::time_point dateTime);
std::vector<std::filesystem::path> GetFilePaths(const Configuration &configuration);
std::vector<Data> FindData(const Configuration &configuration, const std::vector<std::filesystem::path> &filePaths);
void SortData(std::vector<Data> &data);
void PrintData(std::vector<Data> &data);

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

Configuration ParseArguments(int numberOfParameters, char **parameters)
{
    if (numberOfParameters != 4)
    {
        throw std::invalid_argument("Wrong number of arguments!");
    }

    const std::filesystem::path path = parameters[1];
    if (!std::filesystem::exists(path))
    {
        throw std::invalid_argument("Invalid path " + path.string() + "!");
    }

    std::cout << path.string() << std::endl;

    std::chrono::system_clock::time_point begin = ParseDateTime(parameters[2]);
    std::chrono::system_clock::time_point end = ParseDateTime(parameters[3]);

    std::cout << "Begin date and time: " << DateTimeToString(begin) << std::endl;
    std::cout << "End date and time: " << DateTimeToString(end) << std::endl;

    return Configuration{ path, begin, end };
}

std::chrono::system_clock::time_point ParseDateTime(std::string_view dateTime)
{
    std::chrono::system_clock::time_point dateTimePoint;
    std::stringstream ss{ std::string(dateTime) };

    // For example 2012_01_01 13:57:21
    if (!(ss >> std::chrono::parse("%Y_%m_%d %H:%M:%S", dateTimePoint)))
    {
        throw std::invalid_argument("Invalid date and time format " + ss.str() + "!");
    }

    return dateTimePoint;
}

std::string DateTimeToString(std::chrono::system_clock::time_point dateTime)
{
    std::time_t t = std::chrono::system_clock::to_time_t(dateTime);
    tm timeinfo{};
    localtime_s(&timeinfo, &t);

    std::stringstream ss;
    ss << std::put_time(&timeinfo, "%c");

    return ss.str();
}

std::vector<std::filesystem::path> GetFilePaths(const Configuration &configuration)
{
    std::vector<std::filesystem::path> filePaths;

    for (const auto &entry : std::filesystem::directory_iterator(configuration.pathToData))
    {
        if (entry.is_regular_file())
        {
            filePaths.push_back(entry.path());
        }
    }

    if (filePaths.empty())
    {
        throw std::invalid_argument("No files found in " + configuration.pathToData.string() + "!");
    }

    return filePaths;
}

std::vector<Data> FindData(const Configuration &configuration, const std::vector<std::filesystem::path> &filePaths)
{
    std::vector<Data> data;

    for (const auto &filePath : filePaths)
    {
        std::cout << "Searching in file " << filePath << std::endl;

        std::string date, time;
        Data dato;
        std::ifstream file;
        file.open(filePath);

        std::string header;
        std::getline(file, header);// Do not check headers

        while (file >> date >> time >> dato.airTemperature >> dato.barometricPressure >> dato.dewPoint
               >> dato.relativeHumidity >> dato.windDirection >> dato.windGust >> dato.windSpeed)
        {
            dato.dateTime = ParseDateTime(date.append(" ").append(time));
            if (dato.dateTime >= configuration.beginDateTime && dato.dateTime <= configuration.endDateTime)
            {
                data.push_back(dato);
            }
        }
    }

    if (data.empty())
    {
        throw std::invalid_argument("No data found!");
    }

    return data;
}

void SortData(std::vector<Data> &data)
{
    std::sort(data.begin(), data.end(), [](const Data &a, const Data &b) {
        return (a.dateTime < b.dateTime);
    });
}

void PrintData(std::vector<Data> &data)
{
    for (const auto &dato : data)
    {
        std::cout << DateTimeToString(dato.dateTime) << ": " << dato.barometricPressure << std::endl;
    }
}
