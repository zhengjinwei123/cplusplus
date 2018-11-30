// genMeshTool.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "InputGeom.h"
#include "SampleInterfaces.h"
#include "Sample_SoloMesh.h"
#include "Sample_TempObstacles.h"
#include "Sample_TileMesh.h"
#include "Filelist.h"

#include <string>
#include <vector>
#include <iostream>

Sample* createSolo() { return new Sample_SoloMesh(); }
Sample* createTile() { return new Sample_TileMesh(); }
Sample* createTempObstacle() { return new Sample_TempObstacles(); }

using namespace std;

void save(string fileName,string inputDir,string outputPath)
{
	string path = inputDir + "/" + fileName;
	BuildContext ctx;
	InputGeom* geom = new InputGeom;

	if (!geom->load(&ctx, path))
	{
		delete geom;
		geom = nullptr;
	}

	Sample* sample = createTile();
	sample->setContext(&ctx);
	sample->handleMeshChanged(geom);
	sample->handleSettings();

	sample->handleBuild();

	string filePureName = fileName.substr(0, fileName.rfind("."));

	string output_path = outputPath + "/" + filePureName +".tile.bin";

	sample->SaveToFile(output_path.c_str());

	delete sample;

	sample = createTempObstacle();
	sample->setContext(&ctx);
	sample->handleMeshChanged(geom);
	sample->handleSettings();


	sample->handleBuild();

	output_path = outputPath + "/" + filePureName +".tilecache.bin";
	sample->SaveToFile(output_path.c_str());

	delete sample;
	sample = nullptr;
}

int main()
{
	string inputDir = "../unity3dMeshs";
	string outputDir = "../../Meshes";

	typedef std::vector<string> tfileListVec;
	tfileListVec fileList;
	scanDirectory(inputDir, ".obj", fileList);

	for (auto it : fileList)
	{
		cout << "process-->" << it << endl;
		save(it,inputDir,outputDir);
		cout << endl << endl;
	}

	system("pause");
    return 0;
}

