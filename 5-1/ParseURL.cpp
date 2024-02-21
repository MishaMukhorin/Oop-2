#include "ParseURL.h"



//имена переменных  lower camel case
//bool DefPort
// rename parsePort
int DefinePort(const std::string& port_str, Protocol protocol, int& port)
{
    if (port_str.empty())
    {
        switch (protocol)
        {
            case Protocol::HTTP:
                port = 80;
                break;
            case Protocol::HTTPS:
                port = 443;
                break;
            case Protocol::FTP:
                port = 21;
                break;
        }
    }
    else
    {
        port = std::stoi(port_str);
    }
    if (port < 1 or port > MAX_PORT) return false;
    return true;
}

bool DefineProtocol(const std::string& protocol_str, Protocol& protocol)
{
    //
    if (protocol_str == "http")
    {
        protocol = Protocol::HTTP;
    }
    else if (protocol_str == "https")
    {
        protocol = Protocol::HTTPS;
    }
    else if (protocol_str == "ftp")
    {
        protocol = Protocol::FTP;
    }
    else
    {
        return false;
    }
    return true;
}

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
    std::regex url_regex(R"(^(\w+):\/\/([^:\/\s]+)(?::(\d+))?(?:\/(.*)?)?$)");

    std::smatch url_match;
    if (!std::regex_match(url, url_match, url_regex)) return false;

    std::string protocol_str = url_match[1];
    // пожалуй перенести в define protocol
    // использовать правильно tolower (лямбда принимающая unsigned char)
    std::transform(protocol_str.begin(), protocol_str.end(), protocol_str.begin(), ::tolower);

    if (!DefineProtocol(protocol_str, protocol)) return false;

    if (!DefinePort(url_match[3], protocol, port)) return false;

    host = url_match[2];
    document = url_match[4];

    return true;
}