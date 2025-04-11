#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    FILE *fp;
    int csd, cport;
    char name[100], rcvg[100], fname[100];
    struct sockaddr_in servaddr;

    printf("Enter the port: ");
    scanf("%d", &cport);

    csd = socket(AF_INET, SOCK_STREAM, 0);
    if (csd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(cport);

    if (connect(csd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    printf("Enter the existing file name: ");
    scanf("%s", name);
    printf("Enter the new file name: ");
    scanf("%s", fname);

    fp = fopen(fname, "w");
    if (!fp) {
        perror("File creation failed");
        close(csd);
        exit(1);
    }

    send(csd, name, sizeof(name), 0);

    while (1) {
        int s = recv(csd, rcvg, sizeof(rcvg) - 1, 0);
        if (s <= 0) break;

        rcvg[s] = '\0';

        if (strcmp(rcvg, "error") == 0) {
            printf("File is not available on server\n");
            break;
        }

        if (strcmp(rcvg, "completed") == 0) {
            printf("File transfer completed\n");
            break;
        }

        fprintf(fp, "%s", rcvg);
    }

    fclose(fp);
    close(csd);
    return 0;
}