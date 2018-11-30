#pragma once
#ifndef _MYAOI_SCENE_MANAGER_H__
#define _MYAOI_SCENE_MANAGER_H__

#include "Aoi/scene.h"

#include <unordered_map>
#include <mutex>
namespace aoi
{
	class Scene;

	typedef  std::unordered_map<unsigned int, Scene*> tSceneMapType;

	class SceneManager {
	private:
		SceneManager();
		~SceneManager();
		SceneManager(const SceneManager&);
		SceneManager& operator=(const SceneManager&);
	public:
		static SceneManager* GetInstance();
		static void Destory();
		void Release();
	public:
		void AddScene(Scene *pScene);
		Scene* GetScene(unsigned int sceneId);
		Scene* CreateScene(unsigned int sceneId, const std::string strPath, bool bStatic = true);
	private:
		tSceneMapType  mSceneMap;
		static SceneManager* mPinstance;
		static std::mutex mMutex;
	};
}

#endif // !_MYAOI_SCENE_MANAGER_H__
