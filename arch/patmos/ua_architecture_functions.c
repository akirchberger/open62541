/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
* See http://creativecommons.org/publicdomain/zero/1.0/ for more information.
*
*    Copyright YEAR (c) YOUR_NAME, YOUR_COMPANY
*/
#ifdef UA_ARCHITECTURE_PATMOS

#include <open62541/types.h>

void UA_deinitialize_architecture_network(void){
  return;
}




int socket(int domain, int type, int protocol){
    return 0;
}
int setsockopt(int sockfd, int level, int optname,
             const void *optval, socklen_t optlen){
    return 0;
}
int bind(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen){
    return 0;
}

void freeaddrinfo(struct addrinfo *res){

}

void UA_initialize_architecture_network(void){
}

int close(int fd)
{
    return 0;
}

int getsockopt(int sockfd, int level, int optname,
                      void *optval, socklen_t *optlen)
{
    return 0;
}

ssize_t send(int sockfd, const void *buf, size_t len, int flags)
{
    return len;
}

#define BROADCAST_MAC (unsigned char[6]) {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
               const struct sockaddr *dest_addr, socklen_t addrlen)
{
    //printf("sendto(%i bytes)\n", (int)len);

    unsigned int rx_addr = 0x000;
    unsigned int tx_addr = 0x800;
    static unsigned char target_ip[4] = {224, 0, 0, 22};

    #define PORT 4840
    #define SRCPORT 1234

    //printf("send(%i bytes)\n", (int)len);
    udp_send_mac(tx_addr, rx_addr, BROADCAST_MAC, target_ip, SRCPORT, PORT, (unsigned char *)buf, len, 10);
    //arp_table_print();

    return len;
}

ssize_t recv(int sockfd, void *buf, size_t len, int flags)
{
    printf("recv(%i bytes)\n", (int)len);
    return len;
}

ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                 struct sockaddr *src_addr, socklen_t *addrlen)
{
    printf("recvfrom(%i bytes)\n", (int)len);
    return len;
}

int getaddrinfo(const char *node, const char *service,
                      const struct addrinfo *hints,
                      struct addrinfo **result)
{
    printf("getaddrinfo(%s)\n", node);

    struct addrinfo res;

    res.ai_family = 0;//PF_INET;
    res.ai_next = NULL;

    *result = &res;
    return 0;
}

int select(int nfds, fd_set *readfds, fd_set *writefds,
                  fd_set *exceptfds, struct timeval *timeout)
{
    printf("select\n");
    return 0;
}

int inet_pton(int af, const char *src, void *dst)
{
    struct in_addr imr_interface;

    imr_interface.s_addr = 0xE0000000;
    dst = &imr_interface;

    return 1;
}

__uint16_t htons(__uint16_t v) {
  return (v >> 8) | (v << 8);
}

__uint32_t htonl(__uint32_t v) {
  __uint32_t ret=htons(v >> 16) | (htons((__uint16_t) v) << 16);
  return ret;
}

__uint32_t ntohl(__uint32_t v) {
  return htonl(v);
}

#endif /* UA_ARCHITECTURE_PATMOS */
