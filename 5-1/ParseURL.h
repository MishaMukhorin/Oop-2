#ifndef OOP_2_PARSEURL_H
#define OOP_2_PARSEURL_H
#include <string>
#include <regex>


const int MAX_PORT = 65535;

enum class Protocol
{
    HTTP,
    HTTPS,
    FTP
};

int DefinePort(const std::string& port_str, Protocol protocol, int& port);
bool DefineProtocol(const std::string& protocol_str, Protocol& protocol);
bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document);



#endif //OOP_2_PARSEURL_H
