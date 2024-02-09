#include "stdafx.h"
#include "HTMLEncode.h"

void EncodeHTML(std::string& str)
{
    const std::vector<std::string> HTMLElememts = {"&quot;", "&apos;", "&lt;", "&gt;", "&amp;"};
    std::string result;
    for (int i = 0; i < str.length(); ++i)
    {
        switch (str[i]){
            case '\"':
                result.append("&quot;");
                break;
            case '\'':
                result.append("&apos;");
                break;
            case '<':
                result.append("&lt;");
                break;
            case '>':
                result.append("&gt;");
                break;
            case '&':
                result.append("&amp;");
                break;
            default:
                std::string s = std::string(1, str[i]);
                result.append(s);
                break;
        }
    }
    str = result;
}