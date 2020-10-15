/*
 * Copyright (C) 2014-2016  Yaochuang Ding - <ych_ding@163.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions, and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution, and in the same
 *    place and form as other copyright, license and disclaimer information.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <cstdlib>
#include <cassert>
#include <vector>

#if !defined(BUILD_LIB)
#include<bitset>
using std::bitset;
#endif

using std::vector;

/*! \brief add one to an integer signed and unsigned */
#define ADD_ONE(n) (-(~n)) // 2's complement code
/*! \brief fetch bit[i] of an integer, i's range assured by user. */
#define BIT(n,i) ((n & (1 << i)) >> i)

/*! \brief an array of number, all number occur twice except one, find that number. */
int unpairNumber(const vector<int> &nums);

/*! \brief an array of number, all number occur twice except two, find them. */
void unpairNumbers(const vector<int> &nums, int &x, int &y);

/*! \brief how to only keep right most bit */
inline unsigned int bitSeted(unsigned int n)
{
    assert(!(n & (n - 1))); //user should assure only bit set.
    int bits = sizeof(n) * 8, i;
    for (i = 0; i < bits && !(n & (1 << i)); ++i);
    return i;
}

inline unsigned int firstSettedBit(int n)
{
    int bits = sizeof(n) * 8, i;
    for (i = 0; i < bits && !(n & (1 << i)); ++i);
    return i;
}

/*! \brief test an integer, is it 4's power */
inline bool isPowerOf4(unsigned int n)
{
    if (n > 0 && !(n & (n - 1)))
    {
        for (unsigned int i = 0; i < sizeof(n) * 8; i += 2)
        {
            if ((n >> i) & 0x1) return true;
        }
    }
    return false;
}

/*! \brief return min by bit operation.
 * http://graphics.stanford.edu/~seander/bithacks.html#IntegerMinOrMax
 * -1 = ~0; b ^ a ^ b = a; a ^ a = 0; a ^ 0 = a;
 */
inline bool minByBit(int a, int b)
{
    // -1 = 0xFFFF -0 = 0x0000
    return b ^ ((a ^ b) & -(a < b));
}

#if !defined(BUILD_LIB)
#endif
