#ifndef NSLOOKUP_H
#define NSLOOKUP_H
#include "easylog.h"
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

class nslookup
{
public:
    nslookup();
    ~nslookup();
    void NameServer(const char* hostname,std::string &v4,std::string &v6);

};
#endif // NSLOOKUP_H
