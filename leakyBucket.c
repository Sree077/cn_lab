#include <stdio.h>
#include <unistd.h>
#define BUCKET_LIMIT  10
#define OUTPUT_RATE  5
int main(){
    int bucket_level = 0;
    int incoming_data = 0;
    printf("LEAKY BUCKET ALGORITHM SIMULATION:\n");
    while(1){
        incoming_data = rand() % 9 + 1;
        printf("Incoming Data: %d\n", incoming_data);

        if ((incoming_data + bucket_level) <= BUCKET_LIMIT){
            bucket_level += incoming_data;
            printf("Bucket Level: %d\n", bucket_level);
        }
        else{
            printf("Bucket overflow! Dropping Data: %d\n", incoming_data);
        }

        if (bucket_level >= OUTPUT_RATE){
            bucket_level -= OUTPUT_RATE;
            printf("Data Sent: %d\n", OUTPUT_RATE);
            printf("Bucket Level: %d\n", bucket_level);
        }
        else{
            printf("Data Sent: %d\n", bucket_level);
            bucket_level = 0;
            printf("Bucket Level: %d\n", bucket_level);
        }
        printf("----------------\n");
        sleep(1);

    }
    return 0;
}