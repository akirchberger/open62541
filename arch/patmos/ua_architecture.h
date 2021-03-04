/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
* See http://creativecommons.org/publicdomain/zero/1.0/ for more information.
*
*    Copyright YEAR (c) YOUR_NAME, YOUR_COMPANY
*/
#ifdef UA_ARCHITECTURE_PATMOS

#ifndef PLUGINS_ARCH_PATMOS_UA_ARCHITECTURE_H_
#define PLUGINS_ARCH_PATMOS_UA_ARCHITECTURE_H_


//#define UA_EXPORT
#define UA_INLINE inline

#include <open62541/architecture_base.h>

#include <stdbool.h>
#include <stdint.h>

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
//#include <open62541/types.h>

#include <machine/spm.h>

#define PATMOS_IO_LED      0xf0090000
#define LEDS *((volatile _SPM unsigned int *) (PATMOS_IO_LED))

#define PUBLISH_LED_BIT	    0
#define ENCODE_LED_BIT	    1
#define UDP_SEND_LED_BIT	2

#define SUBSCRIBE_LED_BIT	0
#define UDP_RECV_LED_BIT	1
#define DECODE_LED_BIT	    2

#define	IPPROTO_IP		0
#define	IP_ADD_MEMBERSHIP	5
#define	IP_DROP_MEMBERSHIP	6

#define	AF_INET		2
#define	PF_INET		AF_INET

#define IN_ADDR 1234

#define SOCK_DGRAM	2

#define	INADDR_ANY		(u_long)0x00000000


#define UA_IPV6 0
#define UA_SOCKET int
#define UA_INVALID_SOCKET -1
#define IPPROTO_TCP 0
#define TCP_NODELAY 0
#define AF_UNSPEC 0

#define SOL_SOCKET 0
#define SO_REUSEADDR 0

#define SO_SNDBUF	0x1001		/* send buffer size */
#define SO_RCVBUF	0x1002		/* receive buffer size */
#define SO_SNDLOWAT	0x1003		/* send low-water mark */
#define SO_RCVLOWAT	0x1004		/* receive low-water mark */
#define SO_SNDTIMEO	0x1005		/* send timeout */
#define SO_RCVTIMEO	0x1006		/* receive timeout */
#define	SO_ERROR	0x1007		/* get error status and clear */
#define	SO_TYPE		0x1008		/* get socket type */

#define UA_ERRNO errno
#define UA_INTERRUPTED EINTR
#define UA_AGAIN EAGAIN
#define UA_EAGAIN EAGAIN
#define UA_WOULDBLOCK EWOULDBLOCK
#define UA_ERR_CONNECTION_PROGRESS EINPROGRESS

#define OPTVAL_TYPE int

 #define SOCK_STREAM 1

#define	IP_MULTICAST_IF		2 /* in_addr; set/get IP multicast interface */
#define	IP_MULTICAST_TTL	3 /* u_char; set/get IP multicast timetolive */
#define	IP_MULTICAST_LOOP	4 /* u_char; set/get IP multicast loopback */
#define	IP_ADD_MEMBERSHIP	5 /* ip_mreq; add an IP group membership */
#define	IP_DROP_MEMBERSHIP	6 /* ip_mreq; drop an IP group membership */

#define	AI_PASSIVE		 1

#define ERRNO_MSG(errno, msg)	msg
#define SAME_AS(x)		(const char *)&errno_message[x]

int udp_send_mac(unsigned int tx_addr, unsigned int rx_addr, unsigned char destination_mac[], unsigned char destination_ip[], unsigned short source_port, unsigned short destination_port, unsigned char data[], unsigned short data_length, long long timeout);
unsigned eth_mac_receive_nb(unsigned int rx_addr);

unsigned char udp_get_data(unsigned int pkt_addr, unsigned char data[], unsigned int data_length);
unsigned short int udp_get_data_length(unsigned int pkt_addr);
unsigned short int udp_get_destination_port(unsigned int pkt_addr);

#define UA_free free_patmos
#define UA_malloc malloc_patmos
#define UA_calloc calloc_patmos
#define UA_realloc realloc_patmos
#define UA_memset memset_patmos

#define UA_snprintf snprintf

#define UA_LOG_SOCKET_ERRNO_WRAP(LOG)
#define UA_LOG_SOCKET_ERRNO_GAI_WRAP(LOG)

#if UA_MULTITHREADING >= 100
#error Multithreading unsupported
#else
#define UA_LOCK_TYPE(mutexName)
#define UA_LOCK_TYPE_POINTER(mutexName)
#define UA_LOCK_INIT(mutexName)
#define UA_LOCK_DESTROY(mutexName)
#define UA_LOCK(mutexName)
#define UA_UNLOCK(mutexName)
#define UA_LOCK_ASSERT(mutexName, num)
#endif
/*
* Define and include all that's needed for your architecture
*/
void UA_initialize_architecture_network(void);

/*
* Define OPTVAL_TYPE for non windows systems. In doubt, use int //TODO: Is this really necessary
*/

/*
* Define the following network options
*/

#define UA_LITTLE_ENDIAN 0

//typedef unsigned long ssize_t;
typedef _ssize_t ssize_t;
typedef unsigned long socklen_t;

typedef unsigned short	sa_family_t;

struct sockaddr {
    unsigned short    sa_family;    // address family, AF_xxx
    char              sa_data[14];  // 14 bytes of protocol address
};


struct in_addr {
    unsigned long s_addr;  // load with inet_aton()
};

struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};

struct addrinfo {
    int       ai_flags;
    int       ai_family;
    int       ai_socktype;
    int       ai_protocol;
    socklen_t ai_addrlen;
    struct    sockaddr* ai_addr;
    char*     ai_canonname;      // canonical name
    struct    addrinfo* ai_next; // this struct can form a linked list
};
/*
typedef struct
{
     long fds_bits[1024 / 64];
} fd_set;*/

struct timeval {
	long	tv_sec;		// seconds
	long	tv_usec;	// and microseconds
};

#define UA_fd_set(fd, fds) FD_SET((unsigned int)fd, fds)
#define UA_fd_isset(fd, fds) FD_ISSET((unsigned int)fd, fds)

#define UA_access(x,y) 0

struct ip_mreq {
	struct in_addr	imr_multiaddr;	/* IP multicast address of group */
	struct in_addr	imr_interface;	/* local IP address of interface */
};



// sys/socket.h

typedef __int64_t int64_t;

/*
 *  Desired design of maximum size and alignment.
 */
#define _SS_MAXSIZE 128
    /* Implementation-defined maximum size. */
#define _SS_ALIGNSIZE (sizeof(int64_t))
    /* Implementation-defined desired alignment. */

/*
 *  Definitions used for sockaddr_storage structure paddings design.
 */
#define _SS_PAD1SIZE (_SS_ALIGNSIZE - sizeof(sa_family_t))
#define _SS_PAD2SIZE (_SS_MAXSIZE - (sizeof(sa_family_t)+ \
                      _SS_PAD1SIZE + _SS_ALIGNSIZE))
struct sockaddr_storage {
    sa_family_t  ss_family;  /* Address family. */
/*
 *  Following fields are implementation-defined.
 */
    char _ss_pad1[_SS_PAD1SIZE];
        /* 6-byte pad; this is to make implementation-defined
           pad up to alignment field that follows explicit in
           the data structure. */
    int64_t _ss_align;  /* Field to force desired structure
                           storage alignment. */
    char _ss_pad2[_SS_PAD2SIZE];
        /* 112-byte pad to achieve desired size,
           _SS_MAXSIZE value minus size of ss_family
           __ss_pad1, __ss_align fields is 112. */
};


int close(int fd);

int getsockopt(int sockfd, int level, int optname,
                      void *optval, socklen_t *optlen);

ssize_t send(int sockfd, const void *buf, size_t len, int flags);

#define BROADCAST_MAC (unsigned char[6]) {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
               const struct sockaddr *dest_addr, socklen_t addrlen);

ssize_t recv(int sockfd, void *buf, size_t len, int flags);
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                 struct sockaddr *src_addr, socklen_t *addrlen);
int getaddrinfo(const char *node, const char *service,
                      const struct addrinfo *hints,
                      struct addrinfo **result);

void freeaddrinfo(struct addrinfo *res);
int socket(int domain, int type, int protocol);
int setsockopt(int sockfd, int level, int optname,
             const void *optval, socklen_t optlen);
int bind(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int connect(int sockfd, const struct sockaddr *addr,
                   socklen_t addrlen);
int listen(int sockfd, int backlog);
int shutdown(int sockfd, int how);
int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

int select(int nfds, fd_set *readfds, fd_set *writefds,
                  fd_set *exceptfds, struct timeval *timeout);
int inet_pton(int af, const char *src, void *dst);

__uint16_t htons(__uint16_t v);
__uint32_t htonl(__uint32_t v);
__uint32_t ntohl(__uint32_t v);
__uint16_t ntohs(__uint16_t v);

//#define UA_getnameinfo getnameinfo
#define UA_send send
#define UA_recv recv
#define UA_sendto sendto
#define UA_recvfrom recvfrom
#define UA_htonl htonl
#define UA_ntohl ntohl
#define UA_close close
#define UA_select select
#define UA_shutdown shutdown
#define UA_socket socket
#define UA_bind bind
#define UA_listen listen
#define UA_accept accept
#define UA_connect connect
#define UA_getaddrinfo getaddrinfo
#define UA_getsockopt getsockopt
#define UA_setsockopt setsockopt
#define UA_freeaddrinfo freeaddrinfo
#define UA_gethostname gethostname_ecos
#define UA_getsockname getsockname
#define UA_gethostname gethostname_ecos
#define UA_inet_pton(af,src,dst) inet_pton(af, src, (char*) dst)


#define UA_fd_set(fd, fds) FD_SET((unsigned int)fd, fds)
#define UA_fd_isset(fd, fds) FD_ISSET((unsigned int)fd, fds)

int gethostname_ecos(char* name, size_t len);


/*
* Define the ua_getnameinfo if your architecture supports it
*/

/*
* Use #define for the functions defined in ua_architecture_functions.h
* or implement them in a ua_architecture_functions.c file and
* put it in your new_arch folder and add it in the CMakeLists.txt file
* using ua_add_architecture_file(${CMAKE_CURRENT_SOURCE_DIR}/ua_architecture_functions.c)
*/

/*
* Define UA_LOG_SOCKET_ERRNO_WRAP(LOG) which prints the string error given a char* errno_str variable
* Do the same for UA_LOG_SOCKET_ERRNO_GAI_WRAP(LOG) for errors related to getaddrinfo
*/

#include <open62541/architecture_functions.h>

#endif /* PLUGINS_ARCH_PATMOS_UA_ARCHITECTURE_H_ */

#endif /* UA_ARCHITECTURE_PATMOS */
