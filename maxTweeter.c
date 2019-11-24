
//Included packages
#include <stdio.h>
#include <stdlib.h>


//Given Definitions
#define MAX_CSV_LINE_CHARS 1024
#define MAX_CSV_FILE_LEN 20000

//Definitions based on Twitters limitations
#define MAX_CHARS_IN_NAME 50
#define MAX_CHARS_IN_TWEET 280

//Struct used to keep track of each tweeter and their tweet count
struct Tweeter {
  char name[MAX_CHARS_IN_NAME];
  int tweet_count;
};

int main(int argc, char *argv[]) {
  struct Tweeter tweeter_array[MAX_CSV_FILE_LEN];
  for (int i = 0; i < MAX_CSV_FILE_LEN; i++) {
    struct Tweeter new_tweeter = {"", 0};
    tweeter_array[i] = new_tweeter;
  }

  FILE *file_path = fopen(argv[1], "r");

  if (!file_path) {
      exit(1);
  }
}
