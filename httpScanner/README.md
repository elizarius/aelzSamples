How to run:
----------
git clone https://github.com/elnormous/HTTPRequest.git
git clone https://github.com/elizarius/aelzSamples.git
cd aelzSamples
git checkout develop 
cd httpScanner
make clean
make
./http_scan 


Design questions 
----------------
Assuming we wanted to simultaneously monitor the connectivity (and latencies) from multiple
geographically distributed locations and collect all the data to a single report that always
reflects the current status across all locations. Describe how the design would be different.

How would you transfer the data? 
- Cliens starts on remote location
- Syslog logger should be used instead of Console logger  (see Logger.h)
- Syslog logger initiated in main function when scanner instance created
- Syslog logger prints messages  to rsyslog 
- Rsyslog configured to transfer logs to remote server via rsyslog  protocol (RFC 3164)
- Remote rsyslog server accumulates logs from multiple  sources 
- Time zone should be taken into considearation when analyse log files 

Security considerations?
 - Use rsyslog with tls: 
   https://www.golinuxcloud.com/secure-remote-logging-rsyslog-tls-certificate/
     
 - Extra option could be use IPSec (Ikev2 / Strongswan ) as secure transmission (actually heavy solution)


TBD
---
1. Implement config file class: list of urls 
2. Read timeout value from config file 
3. Read content string from config file 
4. Move implementation from headers to cpp files
5. Exception handling instead of traditional status codes  OK
6. All functions with  RC_NOT_IMPLEMENTED
7. api_test runner 
8. CLI in main (geT_longopt)


