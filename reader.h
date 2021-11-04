#ifndef READER
#define READER

typedef struct Reader Reader;

struct Reader
{
    char *input;
    int index;
    int length;
};

// Returns the passed in string with
// all whitespace and line breaks removed.
char *StripWhitespace(char *s);

// Returns a new Reader.
Reader NewReader(char *input);

int CloseReader(Reader *reader);
char NextChar(Reader *reader);
char ScanChar(Reader *reader);

#endif