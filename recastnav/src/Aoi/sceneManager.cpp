#include "Aoi/scene.h"
#include "Aoi/sceneManager.h"
#include <assert.h>

namespace aoi {
	std::mutex  SceneManager::mMutex;
	SceneManager* SceneManager::mPinstance;

	SceneManager::SceneManager() {
		mSceneMap.clear();
	}


	SceneManager::~SceneManager() {
		tSceneMapType::iterator  it = mSceneMap.begin();
		while (it != mSceneMap.end()) {
			delete it->second;
			it->second = NULL;
		}
		mSceneMap.clear();
	}

	void SceneManager::Destory() {
		if (mPinstance) {
			std::lock_guard<std::mutex> lock(mMutex);
			if (mPinstance) {
				delete mPinstance;
				mPinstance = NULL;
			}
		}
	}

	void SceneManager::Release()
	{
		tSceneMapType::iterator it = mSceneMap.begin();
		for (; it != mSceneMap.end(); ++it)
		{
			delete it->second;
			it->second = nullptr;
		}
		mSceneMap.clear();
	}


	SceneManager* SceneManager::GetInstance() {
		if (NULL == mPinstance) {
			std::lock_guard<std::mutex> lock(mMutex);
			if (NULL == mPinstance) {
				mPinstance = new SceneManager();
			}
		}
		return mPinstance;
	}


	Scene* SceneManager::CreateScene(unsigned int sceneId, const std::string strPath, bool bStatic) {
		Scene *pScene = NULL;
		pScene = new Scene(!bStatic);
		pScene->SetId(sceneId);
		int errCode = pScene->Load(strPath.c_str());
		assert(errCode == 0);
		AddScene(pScene);
		return pScene;
	}

	void SceneManager::AddScene(Scene *pScene) {
		assert(pScene != NULL);
		unsigned int sceneId = pScene->GetId();
		tSceneMapType::iterator it = mSceneMap.find(sceneId);
		if (it != mSceneMap.end()) {
			return;
		}
		mSceneMap.insert(std::pair<unsigned int, Scene*>(sceneId, pScene));
	}


	Scene* SceneManager::GetScene(unsigned int sceneId) {
		tSceneMapType::iterator it = mSceneMap.find(sceneId);
		if (it != mSceneMap.end()) {
			return it->second;
		}
		return NULL;
	}
}
