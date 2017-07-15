#pragma once

#include <stdint.h>
#include <vector>

typedef void* MemoryAddress;
typedef uint32_t ProcessIdentifier;
typedef void* ProcessHandle;
typedef uint32_t MemoryAccessRights;

typedef uint32_t CompareTypeFlags;

struct MemoryInformation
{
	bool isCommitted, isWriteable, isExecutable, isMirror;
	MemoryAddress allocationBase, allocationEnd;
	size_t allocationSize;
};

typedef std::vector<MemoryInformation> MemoryInformationCollection;


// this represents an entire block of logically mapped memory
struct MemoryMapEntry
{
	size_t size;
	bool isMirror;
	MemoryAddress logicalBase, logicalEnd, physicalBase, physicalEnd;

	MemoryMapEntry(const size_t &physicalBase, const size_t &logicalBase, const size_t &size) :
		logicalBase((MemoryAddress)logicalBase),
		physicalBase((MemoryAddress)physicalBase),
		size(size),
		isMirror(false)
	{
		logicalEnd = (MemoryAddress)((size_t)logicalBase + size);
		physicalEnd = (MemoryAddress)((size_t)physicalBase + size);
	}
	MemoryMapEntry(const MemoryAddress &physicalBase, const MemoryAddress &logicalBase, const size_t &size) :
		logicalBase(logicalBase),
		physicalBase(physicalBase),
		size(size),
		isMirror(false)
	{
		logicalEnd = (MemoryAddress)((size_t)logicalBase + size);
		physicalEnd = (MemoryAddress)((size_t)physicalBase + size);
	}

	MemoryMapEntry mirror(const size_t &logicalBase) const { return this->mirror((MemoryAddress)logicalBase);  }
	MemoryMapEntry mirror(const MemoryAddress &logicalBase) const
	{
		MemoryMapEntry ret(*this);
		ret.isMirror = true;
		ret.logicalBase = logicalBase;
		return ret;
	}
};