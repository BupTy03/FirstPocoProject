#include "SimpleRequestHandler.h"
#include "SimpleEchoServer.h"

#include <nlohmann/json.hpp>

#include <Poco/URI.h>
#include <Poco/StringTokenizer.h>


using namespace Poco;
using namespace Poco::Net;


void SimpleRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request,
                                         Poco::Net::HTTPServerResponse& response)
{
    URI uri(request.getURI());
    const auto requestStr = uri.toString();
    if(requestStr.find("/plus") != 0)
    {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        return;
    }

    std::istream& in = request.stream();
    std::vector<char> requestBody(request.getContentLength(), '\0');
    in.read(requestBody.data(), requestBody.size());

    const auto jsonRequest = nlohmann::json::parse(requestBody);
    const int a = jsonRequest["a"].get<int>();
    const int b = jsonRequest["b"].get<int>();

    nlohmann::json jsonResponse;
    jsonResponse["a"] = a;
    jsonResponse["b"] = b;
    jsonResponse["sum"] = a + b;

    response.setStatus(HTTPResponse::HTTP_OK);
    response.setContentType("text/json");

    std::ostream& out = response.send();
    out << jsonResponse.dump(4);
    out.flush();
}


Poco::Net::HTTPRequestHandler* SimpleRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest&) {
    return new SimpleRequestHandler();
}

