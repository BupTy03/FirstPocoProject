#include "SimpleRequestHandler.h"
#include "SimpleEchoServer.h"

#include <Poco/URI.h>
#include <Poco/StringTokenizer.h>


using namespace Poco;
using namespace Poco::Net;


void SimpleRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request,
                                         Poco::Net::HTTPServerResponse& response)
{
    response.setStatus(HTTPResponse::HTTP_OK);
    response.setContentType("text/html");
    std::ostream& out = response.send();

    URI uri(request.getURI());
    if (uri.toString().find("/setText") == 0)
    {
        StringTokenizer str(uri.getQuery(), "=");
        if (str.count() == 2 && str[0] == "text")
        {
            SimpleEchoServer::instance().setText(str[1]);
            out << "ok";
            out.flush();
            return;
        }
    }

    out << "error";
    out.flush();
}


Poco::Net::HTTPRequestHandler* SimpleRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest&) {
    return new SimpleRequestHandler();
}

