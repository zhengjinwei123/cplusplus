//#include "MyAoi/Include/sceneManager.h"
//#include "MyAoi/Include/point3f.h"
//#include "MyAoi/Include/agent.h"
//#include "MyAoi/Include/scene.h"
//#include "MyAoi/Include/agentManager.h"
//
//#include <string.h>
//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//void main()
//{
//	std::string path = "./Meshes/nav_test.obj.tile.bin";
//
//	auto sceneManager= my_aoi::SceneManager::GetInstance();
//	my_aoi::Scene* scene  = sceneManager->CreateScene(1, path.c_str(), false);
//
//	for (int i = 0; i < 100; i++)
//	{
//		my_aoi::Agent* agent = my_aoi::AgentManager::GetInstance()->CreateAgent(1+i,2, 2);
//		
//		if (!agent->EnterScene(scene->GetId()))
//		{
//			cout << "½øÈë³¡¾°Ê§°Ü:" << agent->GetId() << endl;
//			my_aoi::AgentManager::GetInstance()->DestroyAgent(agent->GetId());
//		}
//		//my_aoi::AgentManager::GetInstance()->DestroyAgent(agent->GetId());
//	}
//
//
//	//float pos[3] = { 21.8504f,-2.26952f,6.06484f };
//	//float pos2[3] = { 26.8504f,3.26952f,6.06484f };
//	//scene->AddBoxObstacle(pos, pos2);
//
//	/*my_aoi::Agent* agent2 = new my_aoi::Agent(10, 0, 10, 2, 2, 2);
//	agent2->EnterScene(scene->GetId(), my_aoi::Point3f(46.6001f, 5.25789f, 7.61557f));
//	
//	cout << scene->TotalObjects() << endl;
//
//	std::vector<my_aoi::Agent*> allAgentList;
//	scene->GetAllObjects(allAgentList);
//
//	for (auto a : allAgentList)
//	{
//		cout << a->GetX() << "," << a->GetY() << "," << a->GetZ() << "---" << a->GetWidth() << "," << a->GetHeight() << endl;
//	}
//
//
//	if (agent->Move(my_aoi::Point3f(50.0452f, -2.06952f, 15.8371f)))
//	{
//		std::vector<my_aoi::Point3f> pathList = agent->GetPath();
//		std::vector<my_aoi::Point3f>::iterator it = pathList.begin();
//		for (it; it != pathList.end(); ++it)
//		{
//			agent->MoveToNext(*it);
//			cout << "(" << agent->GetX() << "," << agent->GetY() << "," << agent->GetZ() << ")" << endl << endl;
//		}
//	}
//
//	agent->LeaveScene();
//	agent->LeaveGame();*/
//
//	my_aoi::AgentManager::GetInstance()->Release();
//	my_aoi::SceneManager::GetInstance()->Release();
//
//	my_aoi::AgentManager::Destroy();
//	my_aoi::SceneManager::Destory();
//
//	system("pause");
//}