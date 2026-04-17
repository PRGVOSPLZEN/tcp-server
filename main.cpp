#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <chrono>
#include <ctime>

std::string getCurrentTime() {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind selhal");
        return 1;
    }

    listen(server_fd, 5);
    std::cout << "Server bezi a zapisuje do 'log.txt'..." << std::endl;

    while (true) {
        int addrlen = sizeof(address);
        int new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        
        if (new_socket < 0) {
            perror("Accept selhal");
            continue;
        }

        char buffer[1024] = {0};
        ssize_t bytesRead = read(new_socket, buffer, 1024);

        if (bytesRead > 0) {
            
            std::ofstream outfile;
            outfile.open("log.txt", std::ios_base::app);

            std::stringstream ss;

            ss << buffer;

            std::string type;
            std::string id;
            std::string value;

            std::getline(ss, type, ':');
            std::getline(ss, id, ':');
            std::getline(ss, value, ':');
            
            if (outfile.is_open()) {
                outfile << "[" << getCurrentTime() << "] " << "TYPE: " << type << " | ID: " << id << " | VALUE: " << value << std::endl;
                outfile.close();
                std::cout << "Data ulozena." << std::endl;
            }
            send(new_socket, "Data prijata", 12, 0);
        }

        close(new_socket);
    }

    close(server_fd);
    return 0;
}