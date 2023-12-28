#pragma once

class DirectXCommon;
class Sprite;
class Model;
class SphereModel;
class Texture;
class Camera;

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
	SphereModel* sphere;
	Texture* texture;
	Camera* camera;
};

