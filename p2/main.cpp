#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 1602

int main() {
    int server_fd, new_socket;
    sockaddr_in address{};
    int addr_len = sizeof(address);
    char buffer[1024] = { 0 };

    // Создание дескриптора сокета
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Привязка сокета к порту
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Ожидание подключения
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (true) {
        // Принятие подключения
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addr_len)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Чтение данных из сокета
        ssize_t val_read = read(new_socket, buffer, sizeof(buffer) - 1);
        if (val_read < 0) {
            perror("read failed");
            close(new_socket);
            continue;
        }

        buffer[val_read] = '\0';  // Завершение строки нулевым символом

        int sum = std::stoi(buffer);
        if (strlen(buffer) > 2 && sum % 32 == 0) {
            std::cout << "\nData have been received" << std::endl;
        } else {
            std::cout << "Error!" << std::endl;
        }

        std::cout << buffer << std::endl;

        // Закрытие подключенного сокета
        close(new_socket);
    }

    // Закрытие сервера
    close(server_fd);
    return 0;
}
