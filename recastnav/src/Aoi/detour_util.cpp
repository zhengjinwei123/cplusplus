#include "Aoi/detour_util.h"
#include "Aoi/filter.h"
#include "Contrib/Fastlz/fastlz.h"
#include "Detour/DetourNavMeshBuilder.h"
#include <algorithm>




namespace aoi {

	CLinearAllocator::CLinearAllocator(const size_t cap)
		: buffer(0)
		, capacity(0)
		, top(0)
		, high(0)
	{
		resize(cap);
	}

	CLinearAllocator::~CLinearAllocator()
	{
		dtFree(buffer);
	}

	void CLinearAllocator::resize(const size_t cap)
	{
		if (buffer) dtFree(buffer);
		buffer = (unsigned char*)dtAlloc(cap, DT_ALLOC_PERM);
		capacity = cap;
	}

	void CLinearAllocator::reset()
	{
		high = std::max(high, top);
		top = 0;
	}

	void* CLinearAllocator::alloc(const size_t size)
	{
		if (!buffer)
			return 0;
		if (top + size > capacity)
			return 0;
		unsigned char* mem = &buffer[top];
		top += size;
		return mem;
	}

	void CLinearAllocator::free(void* /*ptr*/)
	{
		// Empty
	}


	int CFastLZCompressor::maxCompressedSize(const int bufferSize)
	{
		return (int)(bufferSize* 1.05f);
	}

	dtStatus CFastLZCompressor::compress(const unsigned char* buffer, const int bufferSize,
		unsigned char* compressed, const int /*maxCompressedSize*/, int* compressedSize)
	{
		*compressedSize = fastlz_compress((const void *const)buffer, bufferSize, compressed);
		return DT_SUCCESS;
	}

	dtStatus CFastLZCompressor::decompress(const unsigned char* compressed, const int compressedSize,
		unsigned char* buffer, const int maxBufferSize, int* bufferSize)
	{
		*bufferSize = fastlz_decompress(compressed, compressedSize, buffer, maxBufferSize);
		return *bufferSize < 0 ? DT_FAILURE : DT_SUCCESS;
	}

	CMeshProcess::CMeshProcess() {
	}

	void CMeshProcess::process(struct dtNavMeshCreateParams* params,
		unsigned char* polyAreas, unsigned short* polyFlags)
	{
		// Update poly flags from areas.
		for (int i = 0; i < params->polyCount; ++i)
		{
			if (polyAreas[i] == DT_TILECACHE_WALKABLE_AREA)
				polyAreas[i] = POLYAREA_GROUND;

			if (polyAreas[i] == POLYAREA_GROUND ||
				polyAreas[i] == POLYAREA_GRASS ||
				polyAreas[i] == POLYAREA_ROAD)
			{
				polyFlags[i] = POLYFLAGS_WALK;
			}
			else if (polyAreas[i] == POLYAREA_WATER)
			{
				polyFlags[i] = POLYFLAGS_SWIM;
			}
			else if (polyAreas[i] == POLYAREA_DOOR)
			{
				polyFlags[i] = POLYFLAGS_WALK | POLYFLAGS_DOOR;
			}
		}

		// TODO: Pass in off-mesh connections.
	}

}