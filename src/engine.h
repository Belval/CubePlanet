#ifndef ENGINE_H__
#define ENGINE_H__
#include <iostream>
#include <algorithm>
#include <cmath>
#include <sstream>
#include "define.h"
#include "openglcontext.h"
#include "texture.h"
#include "shader.h"
#include "chunk.h"
#include "blockinfo.h"
#include "textureatlas.h" 
#include "array2d.h"
#include "player.h"
#include "world.h"

class Engine : public OpenglContext
{
public:
    Engine();
    virtual ~Engine();
    virtual void Init();
    virtual void DeInit();
    virtual void LoadResource();
    virtual void UnloadResource();
    virtual void Render(float elapsedTime);
    virtual void KeyPressEvent(unsigned char key);
    virtual void KeyReleaseEvent(unsigned char key);
    virtual void MouseMoveEvent(int x, int y);
    virtual void MousePressEvent(const MOUSE_BUTTON &button, int x, int y);
    virtual void MouseReleaseEvent(const MOUSE_BUTTON &button, int x, int y);
	virtual void DrawHud();
	virtual void PrintText(unsigned int x, unsigned int y, const std::string& t);
	virtual void CheckCollision(float fTime);
	virtual void GetBlocAtCursor();
private:
	bool LoadTexture(Texture& texture, const std::string& filename, bool bWrap = false, bool stopOnError = true);

private:
    bool m_wireframe;
	bool m_keyW = false, m_keyA = false, m_keyS = false, m_keyD = false, m_keySpace = false, m_keyShift = false, m_keyJump = false, m_keyCrouch = false, m_keyF3 = true, m_keyLClick = false, m_keyRClick = false;

	TextureAtlas m_textureAtlas;
	Texture* m_skybox = new Texture[6];
	Texture m_textureFont;
	Texture m_textureCrosshair;
	Shader m_shader01;

	World m_World;
	Player* m_player = new Player(&m_World);

	float m_elapsedTimeOnBlock = 0.f;
	Vector3<int> m_currentBlock;
	//Chunk m_testChunk;
	//Chunk m_testChunk2;
	Array2d<BlockInfo>* m_listBloc = new Array2d<BlockInfo>(sqrt(TEXTURE_ATLAS_SIZE), sqrt(TEXTURE_ATLAS_SIZE));

};

#endif // ENGINE_H__
