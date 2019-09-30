#include "api.h"
#include "Logger.h"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "HTTPRequest.hpp"
#include <time.h>


using namespace std;
using namespace hs;

/* Now just hardcode list of urls, later read from file*/
ConfigReader::ConfigReader () {}

ConfigReader::ConfigReader (std::string filename): _fileName(filename)
{
  std::ifstream file_(_fileName);
  std::string line_;

  if (file_.is_open()) {
    while (std::getline(file_, line_)) {

      size_t found = line_.find("Content:"); 
      if (found != string::npos) {
        _content = line_.substr(found+sizeof("Content:"), string::npos);
      } else { 
        size_t found = line_.find("Timeout:"); 
        if (found != string::npos) {
          _timeout = std::stoi(line_.substr(found+sizeof("Timeout:"), string::npos));
        } else {
          _urls.push_back(line_);
        }
      }
    }
    file_.close();
  }
}


Scanner::Scanner (): _content("") {
 }

RetCode Scanner::init(LogType logType) {
   ConfigReader cr("config.txt");
  _urls = cr.readConfig();
  _content = cr.getContent();
  _timeout = cr.getTimeout();

  if (logType == LOG_STD ) {
    _logger = new  ConsoleLogger();
  }
  if (logType == LOG_SLOG ) {
    _logger = new  SyslogLogger();
  }

  return RC_SUCCESS;
}

RetCode Scanner::finalize() { 
  _timeout = 0;
  _logger = 0;
   _urls.clear();
  return RC_SUCCESS;
}

RetCode Scanner::run() { 

  bool a=true;
  while (a) {

    try {
      for (auto it = _urls.begin(); it != _urls.end(); ++it) {
        std::string ts= "00:00:00"; // tbd later
        std::string ht_status;

        http::Request request(*it);
        http::Response response = request.send("GET");

        if (response.status == http::Response::STATUS_OK) {
          std::string resp_body(response.body.begin(), response.body.end()) ;
          if (validateContent(resp_body)) {
            ht_status = "content string MATCHED";
          } else {
            ht_status = "content string NOT MATCHED ";
          }
        } else {
            ht_status = "HTTP_REQ_ERR";
        }
         ts = timeToString();
        _logger->log(*it,  ht_status, ts );
        std::this_thread::sleep_for (std::chrono::seconds(1));
      }
    }
    catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << std::endl;
        continue;
    }
    std::this_thread::sleep_for (std::chrono::seconds(_timeout));
  } // end while 

  return RC_SUCCESS;
}

std::string Scanner::timeToString() {

  std::time_t ct = std::time(0);
  char* cc = ctime(&ct);
  std::string str = cc;
  return str;
}

bool Scanner::validateContent(std::string resp) {
  std::size_t found = resp.find(_content);
  if (found!=std::string::npos) 
    return true;
  else 
    return false;
}
