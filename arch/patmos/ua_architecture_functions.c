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

int UA_sleep_ms(unsigned int miliSeconds)
{

}

int gethostname_ecos(char* name, size_t len){
    return 0;
}

int UA_getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
    return 0;
}

int accept(UA_SOCKET sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    return 0;
}

int listen(UA_SOCKET sockfd, int backlog){
    return 0;
}

unsigned int UA_socket_set_blocking(UA_SOCKET sockfd){
    return 0;
}

unsigned int UA_socket_set_nonblocking(UA_SOCKET sockfd){
    return 0;
}

int connect(int sockfd, const struct sockaddr *addr,
                   socklen_t addrlen){
   return 0;
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

int UA_shutdown(UA_SOCKET sockfd, int how){
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
#define OPCUA_PUBSUB_PORT 4840
#define SRCPORT 1234

ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
               const struct sockaddr *dest_addr, socklen_t addrlen)
{
    //printf("sendto(%i bytes)\n", (int)len);

    unsigned int rx_addr = 0x000;
    unsigned int tx_addr = 0x800;
    static unsigned char target_ip[4] = {224, 0, 0, 22};

    //printf("send(%i bytes)\n", (int)len);
    udp_send_mac(tx_addr, rx_addr, BROADCAST_MAC, target_ip, SRCPORT, OPCUA_PUBSUB_PORT, (unsigned char *)buf, len, 10);
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
    size_t msg_length = -1;
    //enum eth_protocol packet_type;

    unsigned int rx_addr = 0x000;
    unsigned int tx_addr = 0x800;

    {
        unsigned ret = eth_mac_receive_nb(rx_addr);
        if(ret == 1)
        {
            unsigned char packet_type = mac_packet_type(rx_addr);

            //printf("packet_type %i %i\n", packet_type, ret);
            switch (packet_type) {
                //case 6: //ARP
                    //arp_process_received(rx_addr, tx_addr);
                    //return -1;
                case 3: //UDP
                        //printf("DST_PORT %i\n", udp_get_destination_port(rx_addr));
                    if( udp_get_destination_port(rx_addr)  == OPCUA_PUBSUB_PORT)
                    {
                        msg_length = udp_get_data_length(rx_addr);
                        //printf("Message Length %i\n", msg_length);
                        if(len >= msg_length)
                        {
                            LEDS |= (1U << UDP_RECV_LED_BIT);
                            udp_get_data(rx_addr, buf, msg_length);
                            LEDS &= ~( (1U << UDP_RECV_LED_BIT) );
                            LEDS |= (1U << DECODE_LED_BIT);
                        }
                        else {
                            return -1; 
                        }
                    }
                    else
                        return -1; 
                    break;
                default:
                    return -1;
            }
        }
        else
        {
        }
    }

    return msg_length;
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

__uint16_t ntohs(__uint16_t v) {
  return htons(v);
}

//#define MEMORY_DEBUG

#define MEMORY_BLOCKS 32
#define MEMORY_BLOCK_SIZE 256
unsigned char memory[MEMORY_BLOCKS][MEMORY_BLOCK_SIZE];
bool memory_used[MEMORY_BLOCKS]= {0};

#ifdef MEMORY_DEBUG
# define MEMORY_DEBUG_PRINT(x) printf x
#else
# define MEMORY_DEBUG_PRINT(x)
#endif

void print_memory_usage()
{
    for(int i=0;i<MEMORY_BLOCKS;i++)
    {
        MEMORY_DEBUG_PRINT(("%i", memory_used[i] ));
    }
    MEMORY_DEBUG_PRINT(("\n"));
}

void *malloc_patmos(size_t size)
{
    int i;
    MEMORY_DEBUG_PRINT(("malloc(%i)\n", size));

    if(size > MEMORY_BLOCK_SIZE)
    {
        MEMORY_DEBUG_PRINT(("malloc() memory limit exceeded!\n"));
        return NULL;
    }

    _Pragma("loopbound min 1 max 32") // MEMORY_BLOCKS
    for(i=0;i<MEMORY_BLOCKS;i++)
    {
        if(memory_used[i]==0) 
        {
            MEMORY_DEBUG_PRINT(("malloc() block number %i! %p\n", i, &memory[i][0]));
            memory_used[i] = 1;

            //print_memory_usage();

            return (void *)&memory[i][0];
        }
    }
    MEMORY_DEBUG_PRINT(("malloc() no free memory block!\n"));
    return NULL;
}

void *calloc_patmos(size_t nitems, size_t size)
{
    int i;
    MEMORY_DEBUG_PRINT(("calloc(%i, %i)\n", nitems, size));

    if(size*nitems > MEMORY_BLOCK_SIZE)
    {
        MEMORY_DEBUG_PRINT(("calloc() no free memory block!\n"));
        return NULL;
    }

    _Pragma("loopbound min 1 max 32") // MEMORY_BLOCKS
    for(i=0;i<MEMORY_BLOCKS;i++)
    {
        if(memory_used[i]==0) 
        {
            MEMORY_DEBUG_PRINT(("calloc() block number %i! %p\n", i, &memory[i][0]));
            memory_used[i] = 1;

            //print_memory_usage();

            return (void *)&memory[i][0];
        }
    }
    MEMORY_DEBUG_PRINT(("calloc() no free memory block!\n"));
    return NULL;
}

void *realloc_patmos(void *ptr, size_t size)
{
    MEMORY_DEBUG_PRINT(("realloc(%p, %i)\n", ptr, size));

    if(size > MEMORY_BLOCK_SIZE)
    {
        MEMORY_DEBUG_PRINT(("realloc() memory limit exceeded!\n"));
        return NULL;
    }
}

void free_patmos(void *p)
{
    int i;
    MEMORY_DEBUG_PRINT(("free(%p)\n", p));

    if(p == NULL) return;

    _Pragma("loopbound min 1 max 32") // MEMORY_BLOCKS
    for(i=0;i<MEMORY_BLOCKS;i++)
    {
        if( (void*)&memory[i][0] == p) 
        {
            MEMORY_DEBUG_PRINT(("free() block number %i!\n", i));
            memory_used[i] = 0;

            //print_memory_usage();

            return;
        }
    }
    MEMORY_DEBUG_PRINT(("free() no matching block found!\n"));
}

void *memset_patmos(void *str, int c, size_t n)
{
    MEMORY_DEBUG_PRINT(("memset(%p, %i, %i)\n", str, c, n));

    unsigned char *str_buffer = str;

    _Pragma("loopbound min 1 max 32") // MEMORY_BLOCK_SIZE
    for(int i=0;i<n;i++)
    {
        str_buffer[i] = c;
    }
    return str;
}

#endif /* UA_ARCHITECTURE_PATMOS */
