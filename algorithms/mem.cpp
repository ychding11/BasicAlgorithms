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
 
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <intrin.h>
#include <glog/logging.h>

#include "profiler.h"

using std::cin;
using std::cout;

//#define PERFORMANCE_METER

std::unordered_map<std::string, core::ProfilerEntry> core::CPUProfiler::ProfilerData;

#define ENTER_FUNCTION 
#define EXIT_FUNCTION 

#define Debug_Internal_State

#if defined(Debug_Internal_State)
//static std::fstream g_DebugStream("PagesOfOneSize_debug.txt", std::fstream::out);
std::string WriteLog(const char* format, ...)
{
	char buffer[4096] = { 0 };
	va_list args;
	va_start(args, format);
	vsprintf_s(buffer, 4096, format, args);
	std::cout << buffer;
	return std::string(buffer);
}
void FlushLog(void)
{
}
#endif

std::string prettySize(uint64_t s)
{
	const uint64_t G = 1024 * 1024 * 1024;
	const uint64_t M = 1024 * 1024;
	const uint64_t K = 1024;
	char buf[1024];
	sprintf_s(buf, "%lluG%lluM%lluK",s / G,(s % G) / M,((s % G) % M) / K );
	return std::string(buf);
}

//< 64K  512K  2M  8M
struct SimpleMemAllocator
{
	struct MemSlice
	{
		void* addr;
		uint64_t size;
		uint64_t slot;

	};
	struct AllocateBlock
	{
		void* addr;
		uint64_t size;
		uint64_t slicesize;
		uint64_t slot;
	};
	std::vector<std::list<MemSlice>> mSlicePool;

	static uint64_t sMinSliceSize;

	AllocateBlock allocate(size_t size)
	{
		void *addr = nullptr;
		uint64_t integer = size / sMinSliceSize;
		uint64_t fraction = size % sMinSliceSize;
		if (fraction > 0) integer += 1;
		unsigned long bitIndex = 0;
		uint64_t slotIndex = (integer & (integer-1)) ? _BitScanReverse64(&bitIndex, (integer << 1) ): _BitScanReverse64(&bitIndex, integer);
		slotIndex = slotIndex > 0 ? bitIndex : 0;
		uint64_t sliceSize =  sMinSliceSize * (0x1 << slotIndex);

		WriteLog("allocate (%s, %s, %llu) \t",prettySize(size).c_str(), prettySize(sliceSize).c_str(), slotIndex);
		
		if (slotIndex >= mSlicePool.size())
		{
			for (int i = mSlicePool.size(); i <= slotIndex; ++i)
			{
				mSlicePool.emplace_back(std::list<MemSlice>{});
			}
			auto& list = mSlicePool[slotIndex];
			addr = malloc(sliceSize);
			list.emplace_back(MemSlice{ malloc(sliceSize), sliceSize, slotIndex });
		    WriteLog("new entry(0x%p)\n", addr);
		}
		else
		{
			auto& list = mSlicePool[slotIndex];
			if (list.empty())
			{
				addr = malloc(sliceSize);
				list.emplace_back(MemSlice{malloc(sliceSize), sliceSize, slotIndex});
				WriteLog("new slice(0x%p)\n", addr);
			}
			else
			{
				auto head = list.front();
				list.pop_front();
				addr = head.addr;
				WriteLog("reuse(0x%p)\n", addr);
			}
		}
		return AllocateBlock{addr, size, sliceSize, slotIndex};
	}

	void retire(const AllocateBlock &info)
	{
		mSlicePool[info.slot].emplace_back(MemSlice{info.addr, info.slicesize, info.slot});
	}

	static SimpleMemAllocator* getMemAllocator();

	SimpleMemAllocator()
		: mSlicePool(16)
	{
		for (uint64_t slot = 0; slot < 10; ++slot)
		{
			uint64_t sliceSize =  sMinSliceSize * (0x1 << slot);
			auto& list = mSlicePool[slot];
			list.emplace_back(MemSlice{ malloc(sliceSize), sliceSize, slot});
		}
	}

	uint64_t TotalSizeInPool(void) const
	{
		uint64_t ret = 0;
		for (uint64_t slot = 0; slot < mSlicePool.size(); ++slot)
		{
			uint64_t sliceSize =  sMinSliceSize * (0x1 << slot);
			uint64_t sliceNum = mSlicePool[slot].size();
			ret += sliceNum * sliceSize;
		}
		return ret;
	}

};

uint64_t SimpleMemAllocator::sMinSliceSize = 64 * 1024;
SimpleMemAllocator* SimpleMemAllocator::getMemAllocator()
{
	static SimpleMemAllocator *allocator = new SimpleMemAllocator();
	return allocator;
}


#include "thirdparty/gtest/gtest.h"

TEST(Basic, allocate)
{
  core::CPUProfiler::begin();
  SimpleMemAllocator::AllocateBlock block;
  uint64_t size = 64 * 1024;
  block = SimpleMemAllocator::getMemAllocator()->allocate(size);
  EXPECT_EQ(64 * 1024 * 1, block.slicesize);
  EXPECT_EQ(0, block.slot);

  size = 61 * 1024;
  block = SimpleMemAllocator::getMemAllocator()->allocate(size);
  EXPECT_EQ(64 * 1024 * 1, block.slicesize);
  EXPECT_EQ(0, block.slot);

  size = 66 * 1024;
  block = SimpleMemAllocator::getMemAllocator()->allocate(size);
  EXPECT_EQ(64 * 1024 * 2, block.slicesize);
  EXPECT_EQ(1, block.slot);

  size = 36 * 1024 * 1024;
  block = SimpleMemAllocator::getMemAllocator()->allocate(size);
  EXPECT_EQ(64 * 1024 * (0x1<<10), block.slicesize);
  EXPECT_EQ(10, block.slot);

  auto str = core::CPUProfiler::end();
  WriteLog("%s\n",str.c_str());
  char c;
  std::cin >> c;
}
