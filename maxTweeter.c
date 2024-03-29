#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * TO_DO
 * Find return -1 if name is never found
 * Check return if tweeter array contains less then 10 tweeters
 * Check null csv behavior
 */

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

//Function for printing out the top 10 tweeters
void print_top(struct Tweeter tweeter_array[MAX_CSV_FILE_LEN], int num_to_print)
{
        for (int i = 0; i < num_to_print; i++) {
                printf("%s: %d\n", tweeter_array[i].name, tweeter_array[i].tweet_count);
        }
}

const char* get_item(char* input_line, int column_number)
{
        int count = 0;
        const char* split_by_comma;
        while ((split_by_comma = strsep(&input_line, ",")) != NULL)
        {
                if (count == column_number) {
                        return split_by_comma;
                }
                count++;
        }
        return NULL;
}

// the merge procedure in Merge-Sort
void merge(struct Tweeter tweeter_array[], int l, int m, int r) {
        //left side
        int left_array_len = m - l + 1;
        struct Tweeter L[left_array_len];
        for (int i = 0; i < left_array_len; i++) {

                strcpy(L[i].name, tweeter_array[l + i].name);
                L[i].tweet_count = tweeter_array[l + i].tweet_count;
        }

        //right side
        int right_array_len = r - m;
        struct Tweeter R[right_array_len];
        for (int j = 0; j < right_array_len; j++) {

                strcpy(R[j].name, tweeter_array[m + 1 + j].name);
                R[j].tweet_count = tweeter_array[m + 1 + j].tweet_count;
        }

        int i = 0;
        int j = 0;
        int k = l;

        // merge arrays decreasing order
        while (i < left_array_len && j < right_array_len) {
                //compare the tweet counts

                if (L[i].tweet_count <= R[j].tweet_count) {
                        strcpy(tweeter_array[k].name, R[j].name);
                        tweeter_array[k].tweet_count = R[j].tweet_count;
                        j++;
                } else {
                        strcpy(tweeter_array[k].name, L[i].name);
                        tweeter_array[k].tweet_count = L[i].tweet_count;
                        i++;
                }

                k++;
        }

        // fill in the remaining element
        while (i < left_array_len) {
                tweeter_array[k] = L[i];
                i++;
                k++;
        }

        while (j < right_array_len) {
                tweeter_array[k] = R[j];
                j++;
                k++;
        }
}

// main merge_sort call
void merge_sort(struct Tweeter tweeter_array[], int l, int r) {
        if (l < r) {
                int m = l + (r - l) / 2;
                merge_sort(tweeter_array, l, m);
                merge_sort(tweeter_array, m + 1, r);
                merge(tweeter_array, l, m, r);
        }
}

//function to return column number by comparing column names in header
//IF NAME NOT FOUND RETURN -1 or something
int find(char* columnName, char* row){

	        const char* tokens;
	        int count = 0;
	        while((tokens = strsep(&row, ",")) != NULL ) {
	                if(strcmp(tokens, columnName) == 0) {
	                        return count;
	                }
	                else{
	                        count++;
	                }
	        }
	        return -1;
}

//find tweeter position in list
int tweeterFind(const char* name, int num_tweeters, struct Tweeter tweeter_array[]){
        for (int i = 0; i < num_tweeters; i++) {
                if(strcmp(name, tweeter_array[i].name) == 0) {
                        return i;
                }
        }
        //tweeter not found
        return -1;
}

char *strip_quotes(char *name)
{
    char *token = name;
    if (token != NULL)
    {
        if (token[0] == '"' && token[strlen(token) - 1] == '"')
        {
            ++token;
            token[strlen(token) - 1] = '\0';
        }
        else
        {
            return name;
        }
    }
    return token;
}

int main(int argc, char *argv[]) {
        struct Tweeter tweeter_array[MAX_CSV_FILE_LEN];
        int num_tweeters = 0;
        for (int i = 0; i < MAX_CSV_FILE_LEN; i++) {
                struct Tweeter new_tweeter = {"", 0};
                tweeter_array[i] = new_tweeter;
        }

        //Argument 1 given by user is the file_path to the csv file
        FILE *file = fopen(argv[1], "r");

        if (!file) {
                printf("Invalid Input Format\n");
                exit(1);
        }

        //find_item "name" in header
        int name_column;

        //read in CSV and fill tweeter_array with names and updated counts
        int count=0;
        do {
                char buff[1024];
                fgets(buff, 1024, (FILE*)file);
                count++;

                if (strlen(buff) <= 1) {
                    break;
                }
                if(count == 1) {
                        //find the column number of name in the header
                        name_column = find("\"name\"", buff);
						if(name_column == -1){
              printf("Invalid Input Format\n");
							return 0;
						}
                }
                if(count > 1) {
                        //ignore the header
                        const char* name = get_item(buff, name_column);
                        char *lineWithoutQuotes = malloc(strlen(name));
                        strcpy(lineWithoutQuotes, name);
                        lineWithoutQuotes = strip_quotes(lineWithoutQuotes);
                        int pos = tweeterFind(lineWithoutQuotes, num_tweeters, tweeter_array);
                        if(pos >= 0) {
                                // increment tweet count
                                tweeter_array[pos].tweet_count++;
                        }
                        else{
                                // create new tweeter and increment tweet count
                                strcpy(tweeter_array[num_tweeters].name, lineWithoutQuotes);
                                tweeter_array[num_tweeters].tweet_count++;
                                num_tweeters++;
                        }
                }
        } while((getc(file))!=EOF);

        //sort tweeter_array by tweet count (merge sort maybe)
        merge_sort(tweeter_array, 0, num_tweeters);

        //No tweeters, print nothing
        if (num_tweeters == 0){
          return 0;
        }
        //output top 10 tweeters name and count
        if (num_tweeters < 10){
          print_top(tweeter_array, num_tweeters);
        }
        else{
          print_top(tweeter_array, 10);
        }

        return 0;
}
