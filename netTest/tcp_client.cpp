#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <IP> <Port>" << endl;
        return 1;
    }

    const char* ip = argv[1];
    int port = atoi(argv[2]);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        close(sockfd);
        return 1;
    }

    cout << "Connected to server " << ip << ":" << port << endl;

    fd_set read_fds;
    while (true) {
        FD_ZERO(&read_fds);
        FD_SET(sockfd, &read_fds);
        FD_SET(STDIN_FILENO, &read_fds);

        int max_fd = max(sockfd, STDIN_FILENO) + 1;
        if (select(max_fd, &read_fds, NULL, NULL, NULL) < 0) break;

        if (FD_ISSET(sockfd, &read_fds)) {
            char buffer[1024];
            int len = recv(sockfd, buffer, sizeof(buffer)-1, 0);
            if (len <= 0) {
                cout << "Connection closed" << endl;
                break;
            }
            buffer[len] = '\0';
            cout << "Server: " << buffer << endl;
        }

        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            string input;
            getline(cin, input);
            send(sockfd, input.c_str(), input.size(), 0);
        }
    }

    close(sockfd);
    return 0;
}
