#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>

int main() {
    FILE *fp;
    int sd, newsd, port, clilen;
    char rcv[100], fileread[100];
    struct sockaddr_in servaddr, cliaddr;

    printf("Enter the port: ");
    scanf("%d", &port);

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if (bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        close(sd);
        exit(1);
    }

    listen(sd, 5);
    clilen = sizeof(cliaddr);
    newsd = accept(sd, (struct sockaddr *)&cliaddr, &clilen);

    if (newsd < 0) {
        perror("Accept failed");
        close(sd);
        exit(1);
    }

    int n = recv(newsd, rcv, sizeof(rcv) - 1, 0);
    if (n <= 0) {
        perror("Receiving filename failed");
        close(newsd);
        close(sd);
        exit(1);
    }

    rcv[n] = '\0';
    fp = fopen(rcv, "r");

    if (!fp) {
        send(newsd, "error", strlen("error"), 0);
    } else {
        while (fgets(fileread, sizeof(fileread), fp)) {
            send(newsd, fileread, strlen(fileread), 0);
            usleep(50000);  // Slight delay to avoid data clumping
        }
        send(newsd, "completed", strlen("completed"), 0);
        fclose(fp);
    }

    close(newsd);
    close(sd);
    return 0;
}