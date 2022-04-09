#pragma once

#include <chrono>
#include <filesystem>
#include <string>


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
