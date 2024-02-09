#ifndef OOP_2_PARSEURL_H
#define OOP_2_PARSEURL_H
#include <string>

enum class Protocol
{
    HTTP,
    HTTPS,
    FTP
};

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document);



#endif //OOP_2_PARSEURL_H
