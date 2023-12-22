#pragma once

class WinApiManager;
class DirectXCommon;
class ImGuiManager;
class Input;
class Sprite;
class SpriteCommon;
class Model;
class Texture;
class SphereModel;

class Game
{
public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();
	DirectXCommon* GetDxCommon() { return dxCommon; }
private:
	WinApiManager* winApiManager;
	Input* input;
	DirectXCommon* dxCommon;
	SpriteCommon* spriteCommon;
	Sprite* sprite;
	Model* model;
	SphereModel* sphere;
	Texture* texture;
	ImGuiManager* imgui;
};

