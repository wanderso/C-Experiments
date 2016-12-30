typedef struct
{
    uint8_t * const buffer;
    int head;
    int tail;
    const int maxLen;
}circBuf_t;
