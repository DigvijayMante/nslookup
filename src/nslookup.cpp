#include"nslookup.h"
#include "easylog.h"
INITIALIZE_EASYLOGGINGPP
#define EASY_LOG(LEVEL) CLOG(LEVEL, "EASY_LOG")

nslookup::nslookup()
{
    //##??## Initilization of easylogger
    el::Configurations conf;
    conf.setToDefault();
    conf.set(el::Level::Global, el::ConfigurationType::Format, "[%datetime{%H:%m:%s}] [%loc]  [%level] : %msg");
    conf.set(el::Level::Global, el::ConfigurationType::ToFile, "true");
    conf.set(el::Level::Global, el::ConfigurationType::ToStandardOutput, "false");
    conf.set(el::Level::Global, el::ConfigurationType::Filename, "./LogFiles/%datetime{%d%b%Y}_nslookup.log");
    el::Loggers::reconfigureLogger("EASY_LOG", conf);
}

nslookup::~nslookup()
{

}

void nslookup::NameServer(const char* hostname,std::string &v4,std::string &v6)
{
     EASY_LOG(INFO)<<"*******In Name Server*******";
     struct addrinfo req, *res = nullptr;
     int errcode = 0 ,icounter = 0;
     char addrstr[100] = {0};
     void *ptr = nullptr;

     memset(&req, 0, sizeof(req));
     req.ai_family   = AF_UNSPEC; // IPv4 or IPv6
     req.ai_socktype = SOCK_STREAM;
     req.ai_flags    = AI_CANONNAME;

     errcode = getaddrinfo(hostname, NULL, &req, &res);
     if(errcode != 0)
     {
         std::cout<< "Invalid DNS: "<<errcode;
         EASY_LOG(ERROR)<<"Invalid DNS:"<<errcode;
         return;
     }
     if(res->ai_canonname == NULL)
     {
         std::cout<<"Server can't find"<<hostname<<": NXDOMAIN";
         EASY_LOG(ERROR)<< "Server can't find "<<hostname<< ": NXDOMAIN";
         freeaddrinfo(res);
         return;
     }

     EASY_LOG(INFO)<<"Name      : "<<res->ai_canonname;
     v4.clear();
     v6.clear();
     while(res)
     {
         inet_ntop(res->ai_family, res->ai_addr->sa_data, addrstr, 100);

         switch (res->ai_family)
         {
             case AF_INET:
                 ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
             break;
             case AF_INET6:
                 ptr = &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr;
             break;
         }
         inet_ntop(res->ai_family, ptr,addrstr,100);
         if(icounter == 0)
            v4.assign(addrstr);
         else if(icounter == 1)
             v6.assign(addrstr);

         EASY_LOG(INFO)<< "IPv4 Address: "<<v4;
         EASY_LOG(INFO)<< "IPv6 Address: "<<v6;
         res = res->ai_next;
         icounter++;
     }

     freeaddrinfo(res);
}

