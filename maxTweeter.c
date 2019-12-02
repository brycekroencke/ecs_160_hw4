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

//Function for printing out the top 10 tweeters
void print_top_ten(struct Tweeter tweeter_array[MAX_CSV_FILE_LEN])
{
        for (int i = 0; i < 10; i++) {
                printf("%s %d\n", tweeter_array[i].name, tweeter_array[i].tweet_count);
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
int find(char* columnName, char* row){
        char* tokens =strtok(row, ",");
        int count = 0;
        while(tokens != NULL ) {
                if(strcmp(tokens, columnName) == 0) {
                        return count;
                }
                else{
                        count++;
                        tokens = strtok(NULL, ",");
                }
        }
        return count;
}

int main(int argc, char *argv[]) {
        struct Tweeter tweeter_array[MAX_CSV_FILE_LEN];
        for (int i = 0; i < MAX_CSV_FILE_LEN; i++) {
                struct Tweeter new_tweeter = {"", 0};
                tweeter_array[i] = new_tweeter;
        }

        //Argument 1 given by user is the file_path to the csv file

        // !!!!! CHANGE BACK TO ARGV[1] !!!!!!
        FILE *file = fopen("cl-tweets-short-clean.csv", "r"); //fopen(argv[1], "r");

        if (!file) {
                exit(1);
        }

        //find_item "name" in header
        int name_column;

        //read in CSV and fill tweeter_array with names and updated counts
        char name_array[MAX_CSV_FILE_LEN][MAX_CHARS_IN_NAME];
        int count=0;
        do {
                char buff[1024];
                fgets(buff, 1024, (FILE*)file);
                count++;
                if(count == 1) {
                        //find the column number of name in the header
                        name_column = find("name", buff);
                }
                if(count > 1) {
                        //ignore the header
                        const char* name = get_item(buff, name_column);
                        strcpy(name_array[count-1], name);
                }
        } while((getc(file))!=EOF);


        for (int i = 0; i < MAX_CSV_FILE_LEN; i++) {
                printf("%s\n", name_array[i]);
        }

        //sort tweeter_array by tweet count (merge sort maybe)
        merge_sort(tweeter_array, 0, MAX_CSV_FILE_LEN);

        //output top 10 tweeters name and count
        print_top_ten(tweeter_array);
}
