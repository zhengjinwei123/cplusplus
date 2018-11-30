#pragma once
#ifndef _MYAOI_DETOUR_H__
#define _MYAOI_DETOUR_H__

#include <cstdint>
#include <unordered_map>
#include <mutex>

class dtNavMesh;
class dtNavMeshQuery;
class dtQueryFilter;
class dtTileCache;

namespace aoi {
	class CLinearAllocator;
	class CFastLZCompressor;
	class CMeshProcess;

	class CDetour {
	public:
		CDetour(bool bStaticMesh = true, uint16_t maxNode = 4096);
		virtual ~CDetour();
		int Load(const char* path);

		bool TryMove(uint64_t startPolyRef,
			float startPos[3],
			float endPos[3],
			float halfExtents[3],
			const dtQueryFilter& filter,
			uint64_t& realEndPolyRef,
			float readEndPos[3],
			bool& bHit);

		bool GetPoly(
			float pos[3],
			float halfExtents[3],
			const dtQueryFilter& filter,
			uint64_t& nearestRef,
			float nearestPt[3]
		);

		bool Raycast(
			uint64_t startPolyRef,
			float startPos[3],
			float endPos[3],
			const dtQueryFilter &filter,
			bool& bHit,
			float hitPos[3]);

		bool RandomPosition(
			float halfExtents[3],
			const dtQueryFilter* filter,
			float(*frand)(),
			uint64_t& randomRef,
			float randomPt[3]
		);

		inline void SetHeightMode(int heightMode) { mHeightMode = heightMode; }
		unsigned int AddCapsuleObstacle(const float pos[3], const float radiux, const float height);
		unsigned int AddBoxObstacle(const float bmin[3], const float bmax[3]);
		unsigned int AddBoxObstacle(const float center[3], const float halfExtents[3], const float yRadians);
		void RemoveObstacle(unsigned int obstacleId);

		inline float* GetBoundsMin() { return mBoundsMin; }
		inline float* GetBoundsMax() { return mBoundsMax; }

	public:
		inline dtTileCache* GetTileCache() { return mTileCache; }
		inline dtNavMesh* GetMesh() { return mMesh; }
		dtNavMeshQuery* GetQuery();
	protected:
		dtNavMesh* loadStaticMesh(const char* path, int& errCode);
		dtNavMesh* loadDynamicMesh(const char* path, int& errCode);
		dtNavMesh* createStaticMesh(const char* path, int& errCode);

		bool mbStaticMesh;
		int mMaxNode;
		dtNavMesh* mMesh;
		dtTileCache* mTileCache;
		dtNavMeshQuery* mQuery;

		float mBoundsMin[3];
		float mBoundsMax[3];

		int mHeightMode;
		CLinearAllocator* mTalloc;
		CFastLZCompressor* mTcomp;
		CMeshProcess* mTmproc;
		dtNavMeshQuery* mQueryForHeightMode2;
		static std::unordered_map<std::string, dtNavMesh*> mStaticMesh;
		static std::mutex mMutex;
	};
};

#endif // !_MYAOI_DETOUR_H__

