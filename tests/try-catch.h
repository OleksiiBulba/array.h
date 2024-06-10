#ifndef TRY_CATCH_H_
#define TRY_CATCH_H_

#include <setjmp.h>

jmp_buf *g__ActiveBuf;

#define try                                 \
    jmp_buf __LocalJmpBuff;                 \
    jmp_buf *__OldActiveBuf = g__ActiveBuf; \
    bool __WasThrown = false;               \
    g__ActiveBuf = &__LocalJmpBuff;         \
    if (setjmp(__LocalJmpBuff)) {           \
        __WasThrown=true;                   \
    } else

#define catch(x)                            \
    g__ActiveBuf = __OldActiveBuf;          \
    if (__WasThrown)

#define success else

#define throw(x) longjmp(*g__ActiveBuf, 1)

#endif // TRY_CATCH_H_

