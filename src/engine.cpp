#include "engine.h"

Engine::Engine() : m_wireframe(false), m_World(VIEW_DISTANCE / (CHUNK_SIZE_X / 2), VIEW_DISTANCE / (CHUNK_SIZE_Z / 2))
{
}

Engine::~Engine()
{
}

void Engine::Init()
{
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cerr << " Error while initializing glew .. abording (" << glewGetErrorString(err) << ") " << std::endl;
		abort();
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)Width() / (float)Height(), 0.1f, 1000.0f);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LINE_SMOOTH);
	// TP03
	glEnable(GL_CULL_FACE);
	// Light
	GLfloat light0Pos[4] = { 0.0f, CHUNK_SIZE_Y, 0.0f, 1.0f };
	GLfloat light0Amb[4] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat light0Diff[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light0Spec[4] = { 0.2f, 0.2f, 0.2f, 1.0f };

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0Amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0Spec);

	CenterMouse();
	HideCursor();

}

void Engine::DeInit()
{
}

void Engine::LoadResource()
{
	std::cout << "Loading and compiling shaders..." << std::endl;
	if (!m_shader01.Load(SHADER_PATH "shader01.vert", SHADER_PATH "shader01.frag", true))
	{
		std::cout << "Failed to load shader" << std::endl;
		exit(1);
	}
	// Bloc Air
	BlockInfo* BlocAir = new BlockInfo(BTYPE_AIR, "Air");
	m_listBloc->Set(BTYPE_AIR % 4, BTYPE_AIR / 4, *BlocAir);

	// Bloc Grass
	TextureAtlas::TextureIndex texGrassIndex = m_textureAtlas.AddTexture(TEXTURE_PATH "grass.png");
	BlockInfo* BlocGrass = new BlockInfo(BTYPE_GRASS, "Grass");
	BlocGrass->GenerateTexCoord(texGrassIndex, m_textureAtlas);
	m_listBloc->Set(BTYPE_GRASS % 4, BTYPE_GRASS / 4, *BlocGrass);

	// Bloc Dirt
	TextureAtlas::TextureIndex texDirtIndex = m_textureAtlas.AddTexture(TEXTURE_PATH "dirt.jpg");
	BlockInfo* BlocDirt = new BlockInfo(BTYPE_DIRT, "Dirt");
	BlocDirt->GenerateTexCoord(texDirtIndex, m_textureAtlas);
	m_listBloc->Set(BTYPE_DIRT % 4, BTYPE_DIRT / 4, *BlocDirt);

	// Bloc Stone
	TextureAtlas::TextureIndex texStoneIndex = m_textureAtlas.AddTexture(TEXTURE_PATH "stone.png");
	BlockInfo* BlocStone = new BlockInfo(BTYPE_STONE, "Stone");
	BlocStone->GenerateTexCoord(texStoneIndex, m_textureAtlas);
	m_listBloc->Set(BTYPE_STONE % 4, BTYPE_STONE / 4, *BlocStone);

	// Bloc Sand
	TextureAtlas::TextureIndex texSandIndex = m_textureAtlas.AddTexture(TEXTURE_PATH "sand.jpg");
	BlockInfo* BlocSand = new BlockInfo(BTYPE_SAND, "Sand");
	BlocSand->GenerateTexCoord(texSandIndex, m_textureAtlas);
	m_listBloc->Set(BTYPE_SAND % 4, BTYPE_SAND / 4, *BlocSand);

	// Bloc SandStone
	TextureAtlas::TextureIndex texSandRockIndex = m_textureAtlas.AddTexture(TEXTURE_PATH "sandstone.jpg");
	BlockInfo* BlocSandRock = new BlockInfo(BTYPE_SANDSTONE, "SandStone");
	BlocSandRock->GenerateTexCoord(texSandRockIndex, m_textureAtlas);
	m_listBloc->Set(BTYPE_SANDSTONE % 4, BTYPE_SANDSTONE / 4, *BlocSandRock);

	//Bloc Feuille
	TextureAtlas::TextureIndex texFeuilleIndex = m_textureAtlas.AddTexture(TEXTURE_PATH "leaves.png");
	BlockInfo* BlocFeuille = new BlockInfo(BTYPE_LEAF, "Leaf");
	BlocFeuille->GenerateTexCoord(texFeuilleIndex, m_textureAtlas);
	m_listBloc->Set(BTYPE_LEAF % 4, BTYPE_LEAF / 4, *BlocFeuille);

	//Bloc Bois
	TextureAtlas::TextureIndex texBoisIndex = m_textureAtlas.AddTexture(TEXTURE_PATH "wood.png");
	BlockInfo* BlocBois = new BlockInfo(BTYPE_WOOD, "Wood");
	BlocBois->GenerateTexCoord(texBoisIndex, m_textureAtlas);
	m_listBloc->Set(BTYPE_WOOD % 4, BTYPE_WOOD / 4, *BlocBois);

	//Bloc Planche
	TextureAtlas::TextureIndex texPlankIndex = m_textureAtlas.AddTexture(TEXTURE_PATH "woodPlank.png");
	BlockInfo* BlocPlank = new BlockInfo(BTYPE_PLANK, "Plank");
	BlocPlank->GenerateTexCoord(texPlankIndex, m_textureAtlas);
	m_listBloc->Set(BTYPE_PLANK % 4, BTYPE_PLANK / 4, *BlocPlank);

	// Bloc Unknown
	TextureAtlas::TextureIndex texUnknownIndex = m_textureAtlas.AddTexture(TEXTURE_PATH "tile.jpg");
	BlockInfo* BlocUnknown = new BlockInfo(BTYPE_UNKNOWN, "Unknown");
	BlocUnknown->GenerateTexCoord(texUnknownIndex, m_textureAtlas);
	m_listBloc->Set(BTYPE_UNKNOWN % 4, BTYPE_UNKNOWN / 4, *BlocUnknown);

	LoadTexture(m_skybox[0], TEXTURE_PATH "Skybox_Front.png", true);
	LoadTexture(m_skybox[1], TEXTURE_PATH "Skybox_Left.png", true);
	LoadTexture(m_skybox[2], TEXTURE_PATH "Skybox_Back.png", true);
	LoadTexture(m_skybox[3], TEXTURE_PATH "Skybox_Right.png", true);
	LoadTexture(m_skybox[4], TEXTURE_PATH "Skybox_Top.png", true);
	LoadTexture(m_skybox[5], TEXTURE_PATH "Skybox_Bottom.png", true);
	LoadTexture(m_textureCrosshair, TEXTURE_PATH "cross.bmp");
	LoadTexture(m_textureFont, TEXTURE_PATH "font.bmp");
	if (!m_textureAtlas.Generate(128, false)) 
	{
		std::cout << "Unable to generate texture atlas..." << std::endl;
	}

	/*m_listChunks->Reset(new Chunk());
	for (size_t z = 0; z < VIEW_DISTANCE / (CHUNK_SIZE_Z / 2); z++)
	{
		for (size_t x = 0; x < VIEW_DISTANCE / (CHUNK_SIZE_X / 2); x++)
		{
			m_listChunks->Set(x, z, new Chunk((x * 16) - VIEW_DISTANCE, (z * 16) - VIEW_DISTANCE));
		}
	}*/

	/*LoadTexture(m_textureFloor, TEXTURE_PATH "checker.bmp");
	LoadTexture(m_textureCube, TEXTURE_PATH "sandrock.jpg");
	LoadTexture(m_textureStalker, TEXTURE_PATH "tile.jpg");*/
}

void Engine::UnloadResource()
{
}

void Engine::Render(float elapsedTime)
{
	static float gameTime = elapsedTime;

	gameTime += elapsedTime;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#pragma region SkyBox
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	
	glLoadIdentity();
	
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);


	m_player->ApplyRotation();

	glColor4f(1, 1, 1, 1);
	
	// Render the front quad
	m_skybox[0].Bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, 0.6f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, 0.6f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, -0.4f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, -0.4f, 0.5f);
	glEnd();

	// Render the back quad
	m_skybox[2].Bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0.5f, 0.6f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.6f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, -0.4f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, -0.4f, -0.5f);
	glEnd();


	// Render the right quad
	m_skybox[3].Bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0.5f, 0.6f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, 0.6f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, -0.4f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, -0.4f, 0.5f);
	glEnd();

	// Render the left quad
	m_skybox[1].Bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, 0.6f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.6f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, -0.4f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, -0.4f, -0.5f);
	glEnd();


	// Render the top quad
	m_skybox[4].Bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, 0.6f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, 0.6f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.6f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.6f, 0.5f);
	glEnd();

	// Render the bottom quad
	m_skybox[5].Bind();
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.4f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, -0.4f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, -0.4f, -0.5f);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.4f, 0.5f);
	glEnd();

	glPopAttrib();
	glPopMatrix();

#pragma endregion Skybox

	// Transformations initiales
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	m_player->ApplyRotation();
	CheckCollision(elapsedTime);
	glTranslatef(0.5f, 0.5f, 0.5f);
	// Plancher
	// Les vertex doivent etre affiches dans le sens anti-horaire (CCW)
	m_textureAtlas.Bind();
	// Chunk Render
	m_shader01.Use();
	
	for (size_t z = 0; z < VIEW_DISTANCE / (CHUNK_SIZE_Z / 2); z++)
	{
		for (size_t x = 0; x < VIEW_DISTANCE / (CHUNK_SIZE_X / 2); x++)
		{
			Chunk* chunk = m_World.m_Map.Get(x, z);
			if (chunk->IsDirty())
				chunk->Update(m_listBloc);
			chunk->Render();
		}
	}

	Shader::Disable();

	GetBlocAtCursor();
	if (m_keyLClick) {
		m_elapsedTimeOnBlock += elapsedTime;
		Chunk* chunk = m_World.ChunkAt(m_currentBlock.x, m_currentBlock.y, m_currentBlock.z);
		BlockType bt = chunk->GetBloc(m_currentBlock.x % CHUNK_SIZE_X, m_currentBlock.y, m_currentBlock.z % CHUNK_SIZE_Z);
		if (m_elapsedTimeOnBlock > BREAK_TIME_MAP[bt]) {
			Chunk* chunk = m_World.ChunkAt(m_currentBlock.x, m_currentBlock.y, m_currentBlock.z);
			chunk->RemoveBloc(m_currentBlock.x % CHUNK_SIZE_X, m_currentBlock.y, m_currentBlock.z % CHUNK_SIZE_Z);
			m_elapsedTimeOnBlock = 0.f;
		}
	}

	if (m_keyF3)
	{
		if (m_wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		DrawHud();
		if (m_wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		CalculateFps();
	}
}

void Engine::KeyPressEvent(unsigned char key)
{
	switch (key)
	{
	case 36:	// ESC
		Stop();
		break;
	case 94:	// F10
		SetFullscreen(!IsFullscreen());
		break;
	case 22:
		m_keyW = true;
		break;
	case 18:
		m_keyS = true;
		break;
	case 0:
		m_keyA = true;
		break;
	case 3:
		m_keyD = true;
		break;
	case 38:
		m_keyShift = true;
		break;
	case 57:
		m_keyJump = true;
		break;
	case 37:
		m_keyCrouch = true;
		break;
	case 87:
		(m_keyF3 ? m_keyF3 = false : m_keyF3 = true);
		break;
	default:
		std::cout << "Unhandled key: " << (int)key << std::endl;
	}

}

void Engine::KeyReleaseEvent(unsigned char key)
{
	switch (key)
	{
	case 24:       // Y
		m_wireframe = !m_wireframe;
		if (m_wireframe)
		  	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 22:
		m_keyW = false;
		break;
	case 18:
		m_keyS = false;
		break;
	case 0:
		m_keyA = false;
		break;
	case 3:
		m_keyD = false;
		break;
	case 38:
		m_keyShift = false;
		break;
	case 57:
		m_keyJump = false;
		break;
	case 37:
		m_keyCrouch = false;
		break;
	}
}

void Engine::MouseMoveEvent(int x, int y)
{
	// Centrer la souris seulement si elle n'est pas d�j� centr�e
	// Il est n�cessaire de faire la v�rification pour �viter de tomber
	// dans une boucle infinie o� l'appel � CenterMouse g�n�re un
	// MouseMoveEvent, qui rapelle CenterMouse qui rapelle un autre 
	// MouseMoveEvent, etc

	if (x == (Width() / 2) && y == (Height() / 2))
		return;

	MakeRelativeToCenter(x, y);
	m_player->TurnLeftRight((float)x);
	m_player->TurnTopBottom((float)y);

	CenterMouse();
}

void Engine::MousePressEvent(const MOUSE_BUTTON &button, int x, int y)
{
	if (MOUSE_BUTTON_LEFT) {
		m_keyLClick = true;
	}
	else if (MOUSE_BUTTON_RIGHT) {
		m_keyRClick = true;
	}
}

void Engine::MouseReleaseEvent(const MOUSE_BUTTON &button, int x, int y)
{
	if (MOUSE_BUTTON_LEFT) {
		m_keyLClick = false;
		m_elapsedTimeOnBlock = 0.f;
	}
	else if (MOUSE_BUTTON_RIGHT) {
		m_keyRClick = false;
	}
}

void Engine::DrawHud()
{
	// Setter le blend function , tout ce qui sera noir sera transparent
	glDisable(GL_LIGHTING);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, Width(), 0, Height(), -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	// Bind de la texture pour le font
	m_textureFont.Bind();
	std::ostringstream ss;
	ss << " Fps : " << GetFps();
	PrintText(10, Height() - 25, ss.str());
	//ss.str("");
	//ss << "Chunk : " << m_player->CurrentChunkPos();
	//PrintText(10, 50, ss.str());
	//ss.str("");
	//ss << "Vitesse: " << m_player->vitesseY;
	//if (m_player->vitesseY != 0)
	//{
	//	std::cout << "";
	//}
	//PrintText(10,30,ss.str());
	/*ss.str("");
	ss << "Bloc : " << m_player->BlocUnder();
	PrintText(10, 30, ss.str());*/
	ss.str("");
	ss << " Position : " << m_player->Position(); // IMPORTANT : on utilise l � operateur << pour afficher la position
	PrintText(10, 10, ss.str());
	// Affichage du crosshair
	m_textureCrosshair.Bind();
	static const int crossSize = 32;
	glLoadIdentity();
	glTranslated(Width() / 2 - crossSize / 2, Height() / 2 - crossSize / 2, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2i(0, 0);
	glTexCoord2f(1, 0);
	glVertex2i(crossSize, 0);
	glTexCoord2f(1, 1);
	glVertex2i(crossSize, crossSize);
	glTexCoord2f(0, 1);
	glVertex2i(0, crossSize);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Engine::PrintText(unsigned int x, unsigned int y, const std::string & t)
{
	glLoadIdentity();
	glTranslated(x, y, 0);
	for (unsigned int i = 0; i < t.length(); ++i)
	{
		float left = (float)((t[i] - 32) % 16) / 16.0f;
		float top = (float)((t[i] - 32) / 16) / 16.0f;
		top += 0.5f;
		glBegin(GL_QUADS);
		glTexCoord2f(left, 1.0f - top - 0.0625f);
		glVertex2f(0, 0);
		glTexCoord2f(left + 0.0625f, 1.0f - top - 0.0625f);
		glVertex2f(12, 0);
		glTexCoord2f(left + 0.0625f, 1.0f - top);
		glVertex2f(12, 12);
		glTexCoord2f(left, 1.0f - top);
		glVertex2f(0, 12);
		glEnd();
		glTranslated(8, 0, 0);
	}
}


bool Engine::LoadTexture(Texture& texture, const std::string& filename, bool bWrap, bool stopOnError)
{
	texture.Load(filename, bWrap);
	if (!texture.IsValid())
	{
		std::cerr << "Unable to load texture (" << filename << ")" << std::endl;
		if (stopOnError)
			Stop();

		return false;
	}

	return true;
}

void Engine::CheckCollision(float fTime)
{
	Vector3f pos = m_player->Position();
	Vector3f delta = m_player->SimulateMove(m_keyW, m_keyS, m_keyA, m_keyD, m_keyShift, m_keyJump, m_keyCrouch, fTime);

	BlockType bt1, bt2, bt3;

	bt1 = m_World.BlockAt(pos.x + delta.x, pos.y, pos.z);
	bt2 = m_World.BlockAt(pos.x + delta.x, pos.y - 0.9f, pos.z);
	bt3 = m_World.BlockAt(pos.x + delta.x, pos.y - 1.7f, pos.z);
	if (bt1 != BTYPE_AIR || bt2 != BTYPE_AIR || bt3 != BTYPE_AIR)
		delta.x = 0;

	bt1 = m_World.BlockAt(pos.x, pos.y + delta.y, pos.z);
	bt2 = m_World.BlockAt(pos.x, pos.y - 0.9f + delta.y, pos.z);
	bt3 = m_World.BlockAt(pos.x, pos.y - 1.7f + delta.y, pos.z);
	if (bt1 != BTYPE_AIR || bt2 != BTYPE_AIR || bt3 != BTYPE_AIR) {
		delta.y = 0;
		if (m_player->m_vitessePersonnage.y < 0)
		{
			m_player->m_vitessePersonnage.y = 0;
		}
	}

	bt1 = m_World.BlockAt(pos.x, pos.y, pos.z + delta.z);
	bt3 = m_World.BlockAt(pos.x, pos.y - 0.9f, pos.z + delta.z);
	bt2 = m_World.BlockAt(pos.x, pos.y - 1.7f, pos.z + delta.z);
	if (bt1 != BTYPE_AIR || bt2 != BTYPE_AIR || bt3 != BTYPE_AIR)
		delta.z = 0;

	pos += delta;
	m_player->SetPosition(pos);
	m_player->ApplyTranslation();
}

void Engine::GetBlocAtCursor()
{
    int x = Width() / 2;
    int y = Height() / 2;

    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    posX += .5f;
    posY += .5f;
    posZ += .5f;

    // Le cast vers int marche juste pour les valeurs entiere, utiliser une fonction de la libc si besoin
    // de valeurs negatives
    int px = (int)(posX);
    int py = (int)(posY);
    int pz = (int)(posZ);

    bool found = false;

    if((m_player->Position() - Vector3f(posX, posY, posZ)).Length() < MAX_SELECTION_DISTANCE)
    {
        // Apres avoir determine la position du bloc en utilisant la partie entiere du hit
        // point retourne par opengl, on doit verifier de chaque cote du bloc trouve pour trouver
        // le vrai bloc. Le vrai bloc peut etre different a cause d'erreurs de precision de nos
        // nombres flottants (si z = 14.999 par exemple, et qu'il n'y a pas de blocs a la position
        // 14 (apres arrondi vers l'entier) on doit trouver et retourner le bloc en position 15 s'il existe
        // A cause des erreurs de precisions, ils arrive que le cote d'un bloc qui doit pourtant etre a la
        // position 15 par exemple nous retourne plutot la position 15.0001
        for(int x = px - 1; !found && x <= px + 1; ++x)
        {
            for(int y = py - 1; !found && x >= 0 && y <= py + 1; ++y)
            {
                for(int z = pz - 1; !found && y >= 0  && z <= pz + 1; ++z)
                {
                    if(z >= 0)
                    {
                        BlockType bt = m_World.BlockAt(x, y, z);
                        if (bt == BTYPE_AIR)
                            continue;

                        m_currentBlock.x = x;
                        m_currentBlock.y = y;
                        m_currentBlock.z = z;

						if (Tool::InRangeWithEpsilon<float>(posX, x, x+1, 0.05) && Tool::InRangeWithEpsilon<float>(posY, y, y+1, 0.05) && Tool::InRangeWithEpsilon<float>(posZ, z, z+1, 0.05))
                        {
                            found = true;
                        }
                    }
                }
            }
        }
    }

    if(!found)
    {
        m_currentBlock.x = -1;
    }
    //else
    //{
    //    // Find on which face of the bloc we got an hit
    //    m_currentFaceNormal.Zero();
	//
    //    // Front et back:
    //    if(Tool::EqualWithEpsilon<float>(posZ, m_currentBlock.z, 0.005f))
    //        m_currentFaceNormal.z = -1;
    //    else if(Tool::EqualWithEpsilon<float>(posZ, m_currentBlock.z + 1, 0.005f))
    //        m_currentFaceNormal.z = 1;
    //    else if(Tool::EqualWithEpsilon<float>(posX, m_currentBlock.x, 0.005f))
    //        m_currentFaceNormal.x = -1;
    //    else if(Tool::EqualWithEpsilon<float>(posX, m_currentBlock.x + 1, 0.005f))
    //        m_currentFaceNormal.x = 1;
    //    else if(Tool::EqualWithEpsilon<float>(posY, m_currentBlock.y, 0.005f))
    //        m_currentFaceNormal.y = -1;
    //    else if(Tool::EqualWithEpsilon<float>(posY, m_currentBlock.y + 1, 0.005f))
    //        m_currentFaceNormal.y = 1;
    //}
}