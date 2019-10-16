#define SET_IMPL WORD

#if SET_IMPL == WORD
    #include "word.h"
#elif SET_IMPL == BITARR
    #include "bitarr.h"
#elif SET_IMPL == ARR
    #include "arr.h"
#elif SET_IMPL == LIST
    #include "list.h"
#endif

int main() {
    
    return 0;
}