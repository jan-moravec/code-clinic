#include <cpr/cpr.h>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <string>

namespace
{
const std::string URL = "http://ip-api.com/json/?fields=status,message,country,regionName,city,zip,lat,lon,query";
}


int main()
{
    fmt::print("Sending request to {}\n", URL);

    // Use CPR library for simple HTTP Get request
    // https://github.com/libcpr/cpr
    cpr::Response response = cpr::Get(cpr::Url{ URL });

    if (response.status_code == 0)
    {
        fmt::print(stderr, "Request failed with following error: {}\n", response.error.message);
    }
    else if (response.status_code >= 400)
    {
        fmt::print(stderr, "Error [{}] making request\n", response.status_code);
    }
    else
    {
        // Use nlohmann json library for simple JSON parsing
        // https://github.com/nlohmann/json
        nlohmann::json body = nlohmann::json::parse(response.text);
        fmt::print("Request took {} seconds, raw response body: {}\n", response.elapsed, body.dump(4));

        double longitude = body["lon"];
        double latitude = body["lat"];

        fmt::print("You have been located!\n");
        fmt::print("IP Address: {}\n", body["query"]);
        fmt::print("Country: {}\n", body["country"]);
        fmt::print("City: {}\n", body["city"]);
        fmt::print("Longitude: {}\n", longitude);
        fmt::print("Latitude: {}\n", latitude);

        fmt::print("Follow this link to your location in Google Maps: https://www.google.com/maps?q={},{}\n", latitude, longitude);
    }
}
