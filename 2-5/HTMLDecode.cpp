#include "stdafx.h"
#include "HTMLDecode.h"
#include <string_view>
#include <array>


struct Entity
{
    std::string_view encoded;
    char decoded;
};

using namespace std::literals;

constexpr std::array<Entity, 5> ENTITIES  = {Entity
                                             {"quot;"sv, '"'},
                                             {"apos;"sv, '\''},
                                             {"amp;"sv, '&'},
                                             {"lt;"sv, '<'},
                                             {"gt;"sv, '>'}};


constexpr auto MAX_ENTITY_LENGTH = []{
    size_t maxLenEntity = 0;
    for(auto k: ENTITIES)
        if (k.encoded.length() > maxLenEntity)
            maxLenEntity = k.encoded.length();
    return maxLenEntity;
}();

std::string DecodeHTML(const std::string& html)
{
    // fixed const array

    std::string result;
    for (size_t i = 0; i < html.size(); i++)
    {
        if (html[i] == '&')
        { // обойтись без копирования в entity
            std::string entity;
            size_t j = i;
            //hard function
            while (j < i + MAX_ENTITY_LENGTH && html[j] != ';' && html[j + 1] != '&') // fixed магическое число
            {
                j++;
                entity += html[j];
            }
            for(auto& k: ENTITIES)
            {
                if (entity == k.encoded)
                {
                    result += k.decoded;
                    i = j;
                    break;
                }
            }
            if (i != j)
                result += "&";
        }
        else
            result += html[i];
    }
    return result;
}