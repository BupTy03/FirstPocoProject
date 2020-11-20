#pragma once
#include <Poco/Util/ServerApplication.h>

#include <iostream>
#include <string>
#include <mutex>
#include <vector>


class SimpleEchoServer : public Poco::Util::ServerApplication
{
public:
    SimpleEchoServer();
    static SimpleEchoServer& instance();

    void viewText(std::ostream& os);
    void setText(const std::string& newText);

protected:
    int main(const std::vector<std::string>&) override;

private:
    bool textViewed_;
    std::string text_;
    mutable std::mutex textMutex_;
    static SimpleEchoServer* pInstance_;
};