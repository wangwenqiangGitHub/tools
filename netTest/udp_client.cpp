#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <Server IP> <Server Port>" << endl;
        return 1;
    }

    const char *server_ip = argv[1];
    int server_port = atoi(argv[2]);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        perror("socket");
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    cout << "UDP Client started. Send messages to " << server_ip << ":" << server_port << endl;

    fd_set read_fds;
    while (true)
    {
        FD_ZERO(&read_fds);
        FD_SET(sockfd, &read_fds);
        FD_SET(STDIN_FILENO, &read_fds);

        int max_fd = max(sockfd, STDIN_FILENO) + 1;
        if (select(max_fd, &read_fds, NULL, NULL, NULL) < 0)
            break;

            struct sockaddr_in from_addr;
        if (FD_ISSET(sockfd, &read_fds))
        {
            char buffer[1024];
            // struct sockaddr_in from_addr;
            socklen_t from_len = sizeof(from_addr);
            int len = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&from_addr, &from_len);
            if (len <= 0)
                break;
            buffer[len] = '\0';
            char from_ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &from_addr.sin_addr, from_ip, INET_ADDRSTRLEN);
            cout << from_ip << ":" << ntohs(from_addr.sin_port) << " - " << buffer << endl;
        }

        if (FD_ISSET(STDIN_FILENO, &read_fds))
        {
            string input;
            getline(cin, input);
            sendto(sockfd, input.c_str(), input.size(), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
        }
    }

    close(sockfd);
    return 0;
}
