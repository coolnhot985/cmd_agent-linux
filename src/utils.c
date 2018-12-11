#include "utils.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <string.h>

#define HWADDR_LEN 6

void mac_eth0(unsigned char miner_mac[MAC_LEN])
{
    struct ifreq sock;
    int i   = 0;
    int fd  = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    strcpy(sock.ifr_name, "eth0");

    if (0 == ioctl(fd, SIOCGIFHWADDR, &sock)) {
        for (i = 0; i < HWADDR_LEN; i++) {
            sprintf(&miner_mac[i*2], "%02X",
                    ((unsigned char*)sock.ifr_addr.sa_data)[i]);
        }
    }
}



