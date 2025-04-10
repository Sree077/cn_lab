#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){
    int total_frame;
    int ack_status;
    int current_frame = 1;
    int total_transmissions = 0;

    srand(time(NULL));

    printf("Enter total frames: ");
    scanf("%d", &total_frame);

    

    while (current_frame <= total_frame){
        printf("Sending Frame: %d\n", current_frame);
        total_transmissions += 1;

        ack_status = rand() % 4;

        if (ack_status != 3){
            printf("Acknowledgement Received for frame: %d\n", current_frame);
            current_frame += 1;
        }
        else{
            sleep(2);
            printf("Timout for frame: %d\n", current_frame);
            printf("Retransmitting frame: %d\n", current_frame);
        }
        sleep(2);
    }
    printf("Total transmisssions: %d\n", total_transmissions);
    return 0;

}