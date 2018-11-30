#pragma once
#ifndef _MYAOI_DETOUR_UTIL_H__
#define _MYAOI_DETOUR_UTIL_H__

#include "DetourTileCache/DetourTileCacheBuilder.h"
#include "DetourTileCache/DetourTileCache.h"

namespace aoi {
	class CLinearAllocator : public dtTileCacheAlloc
	{
	public:
		CLinearAllocator(const size_t cap);
		~CLinearAllocator();

		void resize(const size_t cap);
		void reset() override;
		void * alloc(const size_t size) override;
		void free(void *ptr) override;
	private:
		unsigned char* buffer;
		size_t    capacity;
		size_t    top;
		size_t    high;
	};

	class CFastLZCompressor : public dtTileCacheCompressor
	{
	public:
		int maxCompressedSize(const int bufferSize) override;
		dtStatus compress(const unsigned char* buffer, const int bufferSize,
			unsigned char* compressed, const int maxCompressedSize, int* compressedSize) override;
		dtStatus decompress(const unsigned char* compressed, const int compressedSize,
			unsigned char* buffer, const int maxBufferSize, int* bufferSize) override;
	};

	class CMeshProcess : public dtTileCacheMeshProcess
	{
	public:
		CMeshProcess();
		void process(struct dtNavMeshCreateParams* params,
			unsigned char* polyAreas, unsigned short* polyFlags);
	};

};

#endif