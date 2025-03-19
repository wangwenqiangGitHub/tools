#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " [IP] <Port>" << endl;
        return 1;
    }

    const char* ip = "0.0.0.0";
    int port;

    if (argc == 3) {
        ip = argv[1];
        port = atoi(argv[2]);
    } else if (argc == 2) {
        port = atoi(argv[1]);
    } else {
        cerr << "Invalid arguments" << endl;
        return 1;
    }

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        return 1;
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr.sin_addr);

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 5) == -1) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    cout << "TCP Server listening on " << ip << ":" << port << endl;

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    close(server_fd);

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
    cout << "Connected with " << client_ip << ":" << ntohs(client_addr.sin_port) << endl;

    fd_set read_fds;
    while (true) {
        FD_ZERO(&read_fds);
        FD_SET(client_fd, &read_fds);
        FD_SET(STDIN_FILENO, &read_fds);

        int max_fd = max(client_fd, STDIN_FILENO) + 1;
        if (select(max_fd, &read_fds, NULL, NULL, NULL) < 0) break;

        if (FD_ISSET(client_fd, &read_fds)) {
            char buffer[1024];
            int len = recv(client_fd, buffer, sizeof(buffer)-1, 0);
            if (len <= 0) {
                cout << "Connection closed" << endl;
                break;
            }
            buffer[len] = '\0';
            cout << "Client: " << buffer << endl;
        }

        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            string input;
            getline(cin, input);
            send(client_fd, input.c_str(), input.size(), 0);
        }
    }

    close(client_fd);
    return 0;
}
