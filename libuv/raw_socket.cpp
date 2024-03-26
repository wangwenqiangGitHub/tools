/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 */

#include <unistd.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <errno.h>
#include <uv.h>

#define DEFAULT_IF  "eth0"

uv_loop_t *loop;
int sockfd;
uv_poll_t  *handle;

static void on_close(uv_handle_t* handle)
{
    printf("ON CLOSE\n");
    free(handle);
}
static void on_raw_packet_capture(uv_poll_t *handle, int status, int events)
{
    uint8_t pkt_data[ETH_FRAME_LEN];
    int  len = 0;

    errno = 0;
    len = recvfrom(sockfd, pkt_data, ETH_FRAME_LEN, 0, NULL, NULL);

    if (len < 0) {
        if (errno == EAGAIN || errno == EINTR) {
            /* try again */
            sleep(1);
            return;
        }

        /* error was encountred */
        printf("%s (%d)\n", strerror(errno), errno);
        uv_close((uv_handle_t *)handle, on_close);
        return;
    } else
    if (len == 0) {
        /* wrong state */
        printf("ERROR\n");
        uv_close((uv_handle_t *)handle, on_close);
    }

    printf("receive: %d bytes\n", len);

}
int main(int argc, char *argv[])
{
    int sockfd;
    int flags;
    int sockopt;
    struct ifreq ifopts;    /* set promiscuous mode */
    struct ifreq if_ip; /* get ip addr */
    char ifName[IFNAMSIZ];

    /* Get interface name */
    if (argc > 1)
        strcpy(ifName, argv[1]);
    else
        strcpy(ifName, DEFAULT_IF);

    memset(&if_ip, 0, sizeof(struct ifreq));

    /* Open PF_PACKET socket, listening for EtherType ETH_P_ALL */
    if ((sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1) {
        perror("listener: socket");
        return -1;
    }

    /* Set non-blocking sockets */
    flags = fcntl(sockfd,F_GETFL,0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

    /* Set interface to promiscuous mode - do we need to do this every time? */
    strncpy(ifopts.ifr_name, ifName, IFNAMSIZ-1);
    ioctl(sockfd, SIOCGIFFLAGS, &ifopts);
    ifopts.ifr_flags |= IFF_PROMISC;
    ioctl(sockfd, SIOCSIFFLAGS, &ifopts);

    /* Allow the socket to be reused - incase connection is closed prematurely */
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof sockopt) == -1) {
        perror("setsockopt");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    /* Bind to device */
    if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, ifName, IFNAMSIZ-1) == -1)  {
        perror("SO_BINDTODEVICE");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    /*
    for (;;) {
        uint8_t pkt_data[ETH_FRAME_LEN];
        int  len = 0;

        errno = 0;
        len = recvfrom(sockfd, pkt_data, ETH_FRAME_LEN, 0, NULL, NULL);
        if (len < 0) {
            if (errno == EAGAIN || errno == EINTR) {
                continue;
            }
        }
        printf("receive : %d bytes, errno: %d\n", len, errno);
    }
    */

    handle = (uv_poll_t *)malloc(sizeof(uv_poll_t));
    loop = uv_default_loop();

    if (uv_poll_init(loop, handle, sockfd) != 0) {
        perror("uv_poll_init");
        exit(EXIT_FAILURE);
    }

    if (uv_poll_start(handle, UV_READABLE, on_raw_packet_capture) != 0) {
        perror("uv_poll_start");
        exit(EXIT_FAILURE);
    }


    uv_run(loop, UV_RUN_DEFAULT);

    close(sockfd);
    return EXIT_SUCCESS;
}
