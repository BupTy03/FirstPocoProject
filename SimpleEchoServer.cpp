#include "SimpleEchoServer.h"
#include "SimpleRequestHandler.h"

#include <Poco/Net/HTTPServer.h>
#include <cassert>


SimpleEchoServer* SimpleEchoServer::pInstance_ = nullptr;


SimpleEchoServer::SimpleEchoServer()
    : textViewed_(false)
    , text_("Hello!")
    , textMutex_()
{
    assert(pInstance_ == nullptr);
    pInstance_ = this;
}

void SimpleEchoServer::setText(const std::string& newText)
{
    std::lock_guard<std::mutex> lock(textMutex_);
    textViewed_ = false;
    text_ = newText;
}

void SimpleEchoServer::viewText(std::ostream& os)
{
    std::lock_guard<std::mutex> lock(textMutex_);
    if(textViewed_)
        return;

    os << text_ << std::endl;
    textViewed_ = true;
}


int SimpleEchoServer::main(const std::vector<std::string> &)
{
    using namespace Poco::Net;

    HTTPServer s(new SimpleRequestHandlerFactory, ServerSocket(8000), new HTTPServerParams);
    s.start();

    while(true)
        viewText(std::cout);

    s.stop();
    return Application::EXIT_OK;
}

SimpleEchoServer& SimpleEchoServer::instance()
{
    assert(pInstance_ != nullptr);
    return *pInstance_;
}

