#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>
#include <string>
#include <cstring>

class UdpSocket {
    private:
        int sock_fd;
    public:
        UdpSocket() {
            if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
                throw std::runtime_error("Socket creation failed");
            }
        }

        ~UdpSocket() {
            if (sock_fd >= 0) {
                close(sock_fd);
            }
        }

        void Bind(int port) {
            struct sockaddr_in addr;
            memset(&addr, 0, sizeof(addr));

            addr.sin_family = AF_INET;
            addr.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
            addr.sin_port = htons(port);       // Host-to-Network Short

            if (bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
                throw std::runtime_error("Bind failed. Port might be in use.");
            }
        }

        void SendTo(const std::string& ip, int port, const void* data, size_t len) {
            struct sockaddr_in dest_addr;
            memset(&dest_addr, 0, sizeof(dest_addr));
            
            dest_addr.sin_family = AF_INET;
            dest_addr.sin_port = htons(port);
            inet_pton(AF_INET, ip.c_str(), &dest_addr.sin_addr); // Convert String IP to Binary

            sendto(sock_fd, data, len, 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));
        }

        // 5. Recv: For Gateway waiting for data
        // Returns number of bytes received
        int Recv(void* buffer, size_t len) {
            struct sockaddr_in src_addr;
            socklen_t addr_len = sizeof(src_addr);
            
            // This blocks (waits) until data arrives
            return recvfrom(sock_fd, buffer, len, 0, (struct sockaddr*)&src_addr, &addr_len);
        }

};




#endif