#ifndef TRY_CATCH_H_
#define TRY_CATCH_H_

/*
 * MIT License
 *
 * Copyright (c) 2024 Oleksii Bulba <oleksii.bulba@gmail.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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

