
//Included packages
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

// //Function for printing out the top 10 tweeters
// void print_top_ten()
// {
//
// }

const char* get_item(char* input_line, int column_number)
{
    const char* split_by_comma;
    for (split_by_comma = strtok(input_line, ",");
            split_by_comma && *split_by_comma;
            split_by_comma = strtok(NULL, ",\n"))
    {
        if (!--column_number)
            return split_by_comma;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
  struct Tweeter tweeter_array[MAX_CSV_FILE_LEN];
  for (int i = 0; i < MAX_CSV_FILE_LEN; i++) {
    struct Tweeter new_tweeter = {"", 0};
    tweeter_array[i] = new_tweeter;
  }

  //Argument 1 given by user is the file_path to the csv file
  FILE *file_path = fopen(argv[1], "r");

  if (!file_path) {
      exit(1);
  }
}
