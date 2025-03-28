#include <stdio.h>
#include <time.h>
#include <unistd.h>
int main() {
    int total_frames;
    int window_size;
    int total_transmissions = 0;
    int frame;
    
    srand(time(NULL));

    printf("Enter the Total number of frames: ");
    scanf("%d", &total_frames);
    printf("Enter the Window Size: ");
    scanf("%d", &window_size);

    int current_frame = 1;

    while (current_frame <= total_frames) {
        int successfully_acked = 0;

        for (frame = current_frame;  frame < current_frame + window_size && frame <= total_frames; frame++) 
        {
            printf("Sending Frame %d\n", frame);
            total_transmissions++;
        }

        for (int frame = current_frame; frame < current_frame + window_size && frame <= total_frames; frame++)
        {
            int is_ack_received = rand() % 2;

            if (is_ack_received) {
                printf("Acknowledgment for Frame %d\n", frame);
                successfully_acked++;
            } else {
                printf("Timeout!! Frame Number %d Not Received\n", frame);
                printf("Retransmitting Window...\n");
                sleep(2);
                break;
            }
        }

        printf("\n");
        current_frame += successfully_acked;
    }

    printf("Total number of frames sent and resent: %d\n", total_transmissions);
    return 0;
}