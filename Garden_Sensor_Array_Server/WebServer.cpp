#include "Arduino.h"
#include "ctype.h"
#include "WebServer.h"
#include "Helper.h"

String inputString = "";

WebServer::WebServer()
{
  inputString.reserve(200);
}

void WebServer::handleClient()
{
  while(Serial.available() > 0) {
    inputString += Serial.readString();
  }
  if (inputString.length() > 0){
    handleRequest(inputString);
    inputString = "";
  }
}

void WebServer::handleRequest(String request)
{
  String page = "[";

  request.trim();
  request.toLowerCase();
  
  Helper::activateSensorArray();
  
//  if (request == "all" )
//  {
    for (int sensorId = 1; sensorId <= Helper::sensorCount; sensorId++)
    {
      page += getContent("Sensor "+ String(sensorId, DEC), Helper::getSensorValue(sensorId));
      if(sensorId != Helper::sensorCount)
      {
        page += ",";
      }
    }
//  }else if (request.startsWith("sensor"))
//  {
//    String sensorIdString = request;
//    sensorIdString.replace("sensor","");
    
//    page += getContent("Sensor "+ sensorIdString, 100);
//  }
  
  page += "]";
  String header = getHeader(page.length());

  Helper::deactivateSensorArray();
  
  writeResponse(header + page);
}

void WebServer::writeResponse(String response)
{
  //this method will write out the response to the client
  //the write will be done in chunks
  //it just seems to need these small chunks with the time delay in order for it to work.
  int chunkSize = 30;
  int remainingBytes = 0;
  int totalBytes = response.length();
  
  for (int i = 0; i < totalBytes; i += chunkSize)
  {
    if (i + chunkSize <= totalBytes)
    {
      Serial.print(response.substring(i, i + chunkSize));
    }
    else
    {
      remainingBytes = totalBytes - i;
      Serial.print(response.substring(i, i + remainingBytes));
    }
    Serial.flush();
    delay(100);
  }
}

String WebServer::getResponseStatusLine(int responseCode)
{
  String statusLine = "HTTP/1.0 ";
  statusLine.concat(responseCode);
  statusLine += " ";
  switch (responseCode){
    case 100:  statusLine += " Continue"; break;
    case 101:  statusLine += "Switching Protocols"; break;
    case 200:  statusLine += "OK"; break;
    case 201:  statusLine += "Created"; break;
    case 202:  statusLine += "Accepted"; break;
    case 203:  statusLine += "Non-Authoritative Information"; break;
    case 204:  statusLine += "NO Content"; break;
    case 205:  statusLine += "Reset Content"; break;
    case 206:  statusLine += "Partial Content"; break;
    case 300:  statusLine += "Multiple Choices"; break;
    case 301:  statusLine += "Moved Permanently"; break;
    case 302:  statusLine += "Found"; break;
    case 303:  statusLine += "See Other"; break;
    case 304:  statusLine += "Not Modified"; break;
    case 305:  statusLine += "Use Proxy"; break;
    case 307:  statusLine += "Temporary Redirect"; break;
    case 400:  statusLine += "Bad Request"; break;
    case 401:  statusLine += "Unauthorized"; break;
    case 402:  statusLine += "Payment Required"; break;
    case 403:  statusLine += "Forbidden"; break;
    case 404:  statusLine += "Not Found"; break;
    case 405:  statusLine += "Method Not Allowed"; break;
    case 406:  statusLine += "Not Acceptable"; break;
    case 407:  statusLine += "Proxy Authentication Required"; break;
    case 408:  statusLine += "Request Time-out"; break;
    case 409:  statusLine += "Conflict"; break;
    case 410:  statusLine += "Gone"; break;
    case 411:  statusLine += "Length Required"; break;
    case 412:  statusLine += "Precondition Failed"; break;
    case 413:  statusLine += "Request Entity Too Large"; break;
    case 414:  statusLine += "Request-URL Too Large"; break;
    case 415:  statusLine += "Unsupported Media Type"; break;
    case 416:  statusLine += "Requested Range NOt Satifiable"; break;
    case 417:  statusLine += "Expectation Failed"; break;
    case 500:  statusLine += "Internal Server Error"; break;
    case 501:  statusLine += "Not Implemented"; break;
    case 502:  statusLine += "Bad Gateway"; break;
    case 503:  statusLine += "Service Unavailable"; break;
    case 504:  statusLine += "Gateway Time-out"; break;
    case 505:  statusLine += "HTTP Version Not Supported"; break;
  }
  statusLine += "\n\r";    
  return statusLine;
}

String WebServer::getHeader(int contentLength)
{
  String header = getResponseStatusLine(200);
  header += "Server: Garden_Sensor_Array\r\n";
  header += "Content-Type: application/json\r\n";
  header += "Content-Length: ";
  header.concat(contentLength);
  header += "\r\n\r\n";

  return header;
}

String WebServer::getContent(String sensor, int value)
{
  return "{\"Name\":\"" + sensor + "\", \"Value\":" + value + "}";
}

