#define MAX_CSV_LINE_CHARS 1024
#define MAX_CSV_FILE_LEN 20000
#define MAX_CHARS_IN_NAME 50
#define MAX_CHARS_IN_TWEET 280


//Make an array of tweeters and sort by tweet_count

struct Tweeter {
    char name[MAX_CHARS_IN_NAME];
    int tweet_count;
};

struct Tweeter tweeter_array[MAX_CSV_FILE_LEN];
