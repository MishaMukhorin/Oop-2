#include <gtest/gtest.h>
#include "../ParseURL.h"

TEST(ParseURLTest, ValidURL) {
    Protocol protocol;
    int port;
    std::string host, document;
    EXPECT_TRUE(ParseURL("http://www.mysite.com/docs/document1.html?page=30&lang=en#title", protocol, port, host, document));
    EXPECT_EQ(protocol, Protocol::HTTP);
    EXPECT_EQ(port, 80);
    EXPECT_EQ(host, "www.mysite.com");
    EXPECT_EQ(document, "docs/document1.html?page=30&lang=en#title");
}

TEST(ParseURLTest, InvalidURL) {
    Protocol protocol;
    int port;
    std::string host, document;
    EXPECT_FALSE(ParseURL("invalid_url", protocol, port, host, document));
}

TEST(ParseURLTest, ValidURLCustomPort) {
    Protocol protocol;
    int port;
    std::string host, document;
    EXPECT_TRUE(ParseURL("http://www.mysite.com:8080/docs/document1.html", protocol, port, host, document));
    EXPECT_EQ(protocol, Protocol::HTTP);
    EXPECT_EQ(port, 8080);
    EXPECT_EQ(host, "www.mysite.com");
    EXPECT_EQ(document, "docs/document1.html");
}

TEST(ParseURLTest, ValidURLUppercaseProtocol) {
    Protocol protocol;
    int port;
    std::string host, document;
    EXPECT_TRUE(ParseURL("HTTPS://www.mysite.com/docs/document1.html", protocol, port, host, document));
    EXPECT_EQ(protocol, Protocol::HTTPS);
    EXPECT_EQ(port, 443);
    EXPECT_EQ(host, "www.mysite.com");
    EXPECT_EQ(document, "docs/document1.html");
}

TEST(ParseURLTest, ValidURLEmptyDocument) {
    Protocol protocol;
    int port;
    std::string host, document;
    EXPECT_TRUE(ParseURL("ftp://www.mysite.com", protocol, port, host, document));
    EXPECT_EQ(protocol, Protocol::FTP);
    EXPECT_EQ(port, 21);
    EXPECT_EQ(host, "www.mysite.com");
    EXPECT_EQ(document, "");
}

TEST(ParseURLTest, ValidURLEmptyPort) {
    Protocol protocol;
    int port;
    std::string host, document;
    EXPECT_TRUE(ParseURL("http://www.mysite.com/", protocol, port, host, document));
    EXPECT_EQ(protocol, Protocol::HTTP);
    EXPECT_EQ(port, 80);
    EXPECT_EQ(host, "www.mysite.com");
    EXPECT_EQ(document, "");
}

TEST(ParseURLTest, InvalidURLInvalidProtocol) {
    Protocol protocol;
    int port;
    std::string host, document;
    EXPECT_FALSE(ParseURL("fttp://www.mysite.com/docs/document1.html", protocol, port, host, document));
}

TEST(ParseURLTest, InvalidURLInvalidPort) {
    Protocol protocol;
    int port;
    std::string host, document;
    EXPECT_FALSE(ParseURL("http://www.mysite.com:0/docs/document1.html", protocol, port, host, document));
}

TEST(ParseURLTest, InvalidURLInvalidPort2) {
    Protocol protocol;
    int port;
    std::string host, document;
    EXPECT_FALSE(ParseURL("http://www.mysite.com:65536/docs/document1.html", protocol, port, host, document));
}

TEST(ParseURLTest, InvalidURLInvalidPort3) {
    Protocol protocol;
    int port;
    std::string host, document;
    EXPECT_FALSE(ParseURL("http://www.mysite.com:-1/docs/document1.html", protocol, port, host, document));
}

TEST(ParseURLTest, ValidURLValidMaxPort) {
    Protocol protocol;
    int port;
    std::string host, document;
    EXPECT_TRUE(ParseURL("http://www.mysite.com:65535/docs/document1.html", protocol, port, host, document));
    EXPECT_EQ(protocol, Protocol::HTTP);
    EXPECT_EQ(port, 65535);
    EXPECT_EQ(host, "www.mysite.com");
    EXPECT_EQ(document, "docs/document1.html");
}
TEST(ParseURLTest, ValidURLValidMinPort) {
    Protocol protocol;
    int port;
    std::string host, document;
    EXPECT_TRUE(ParseURL("http://www.mysite.com:1/docs/document1.html", protocol, port, host, document));
    EXPECT_EQ(protocol, Protocol::HTTP);
    EXPECT_EQ(port, 1);
    EXPECT_EQ(host, "www.mysite.com");
    EXPECT_EQ(document, "docs/document1.html");
}

TEST(ParseURLTest, InvalidURLInvalidHost) {
    Protocol protocol;
    int port;
    std::string host, document;
    EXPECT_FALSE(ParseURL("http:///docs/document1.html", protocol, port, host, document));
}

TEST(ParseURLTest, InvalidURLMissingProtocol) {
    Protocol protocol;
    int port;
    std::string host, document;
    EXPECT_FALSE(ParseURL("www.mysite.com/docs/document1.html", protocol, port, host, document));
}

TEST(ParseURLTest, InvalidURLMissingHost) {
    Protocol protocol;
    int port;
    std::string host, document;
    EXPECT_FALSE(ParseURL("http://", protocol, port, host, document));
}

TEST(ParseURLTest, InvalidURLMissingDocument) {
    Protocol protocol;
    int port;
    std::string host, document;
    EXPECT_FALSE(ParseURL("http://www.mysite.com:", protocol, port, host, document));
}

TEST(ParseURLTest, InvalidURLMissingProtocolAndHost) {
    Protocol protocol;
    int port;
    std::string host, document;
    EXPECT_FALSE(ParseURL("/docs/document1.html", protocol, port, host, document));
}

TEST(ParseURLTest, EmptyURL) {
    Protocol protocol;
    int port;
    std::string host, document;
    EXPECT_FALSE(ParseURL("", protocol, port, host, document));
}

GTEST_API_ int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}