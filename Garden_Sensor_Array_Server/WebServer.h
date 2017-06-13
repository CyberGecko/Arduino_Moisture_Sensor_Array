#ifndef WebServer_h
#define WebServer_h

#include "Arduino.h"

class WebServer{
  public:  
    WebServer();
    void handleClient();

  private:
    String inputString;
    void handleRequest(String request);
    void writeResponse(String response);
    String getResponseStatusLine(int responseCode);
    String getContent(String sensor, int value);
    String getHeader(int contentLength);
};
#endif
