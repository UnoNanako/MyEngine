#pragma once

class DirectXCommon;
class Sprite;
class Model;
class SphereModel;
class Texture;
class Camera;
class LightList;

class GamePlayScene
{
public:
	void Initialize(DirectXCommon* dxCommon);
	void Finalize();
	void Update();
	void Draw(DirectXCommon* dxCommon);

private:
	Sprite* sprite;
	Model* model;
	Model* floorModel;
	Model* terrainModel;
	SphereModel* sphere;
	Texture* texture;
	Texture* terrainTexture;
	Camera* camera;
	LightList* mDirectionalLight;
	LightList* mPointLight;
	LightList* mSpotLight;
};

