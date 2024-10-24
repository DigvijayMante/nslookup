#include <iostream>
#include"nslookup.h"


int main(int argc, char *argv[])
{
    std::string v4,v6;
    nslookup obj;

    if (argc != 2)
    {
        int iChoice = 0;
        std::string strDomainName ;

        do
        {
            std::cout<<"\nPlease provide domain name to know IP address:   ";
            std::cin>>strDomainName;

            obj.NameServer(strDomainName.c_str(),v4,v6);
            std::cout<<"\nName         : "<<strDomainName;
            std::cout<<"\nIPv4 Address : "<<v4;
            std::cout<<"\nIpv6 Address : "<<v6;

            std::cout<<"\n\npress 0 to exit.. \nPress 1 to continue...\n";
            std::cin>>iChoice;
        }while(iChoice == 1);

        return -1;
    }

    obj.NameServer(argv[1],v4,v6);
    std::cout<<"\nIPv4 Address :"<<v4;
    std::cout<<"\nIpv6 Address : "<<v6;

    return 0;
}

