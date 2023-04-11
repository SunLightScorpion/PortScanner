#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <atomic>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <ip-address>\n";
        return 1;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cerr << "Failed to create socket\n";
        return 1;
    }

    struct timeval timeout{};
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
        cerr << "Failed to set socket timeout\n";
        return 1;
    }

    struct sockaddr_in addr{};
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    for (int port = 1; port <= 65535; ++port) {
        addr.sin_port = htons(port);
        if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) >= 0) {
            cout << "Port " << port << " is open\n";
        }
    }

    close(sock);

    return 0;
}
