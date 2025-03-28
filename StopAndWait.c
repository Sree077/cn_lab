#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(){
    int total_frames;
    int ack_status;
    int total_transmissions = 0;
    int current_frame = 1;

    srand(time(NULL));

    printf("Enter Total Frames: ");
    scanf("%d", &total_frames);

    while ( current_frame <= total_frames ){
        printf("\nSending Frame: %d\n", current_frame);
        total_transmissions++;

        ack_status = rand() % 4;

        if (ack_status != 3){
            printf("ACK Received for Frame: %d\n", current_frame);
            current_frame++;
        }
        else{
            printf("Timout for frame: %d\n", current_frame);
            sleep(2);
            printf("Retransmitting Frame: %d\n", current_frame);

        }
    }
    printf("Total Transmissions: %d\n", total_transmissions);
    return 0;
}