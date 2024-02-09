#include <iostream>
#include <string>
#include "ParseURL.h"

int main()
{
    std::string url;
    while (std::getline(std::cin, url))
    {
        Protocol protocol;
        int port;
        std::string host, document;
        if (ParseURL(url, protocol, port, host, document))
        {
            std::cout << url << std::endl;
            std::cout << "HOST: " << host << std::endl;
            std::cout << "PORT: " << port << std::endl;
            std::cout << "DOC: " << document << std::endl;
        } else
        {
            std::cout << "Invalid URL: " << url << std::endl;
        }
    }
    return 0;
}
