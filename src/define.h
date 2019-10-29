#ifndef DEFINE_H__
#define DEFINE_H__
#include <GL/glew.h>
#include <SFML/Window.hpp>

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int64;


#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 128
#define CHUNK_SIZE_Z 16

typedef uint8 BlockType;
enum BLOCK_TYPE {BTYPE_AIR, BTYPE_DIRT, BTYPE_STONE, BTYPE_SAND, BTYPE_SANDSTONE, BTYPE_LEAF, BTYPE_WOOD, BTYPE_PLANK, BTYPE_UNKNOWN};


#define TEXTURE_PATH        "../cubeplanet/media/textures/"
#define TEXTURE_ATLAS_SIZE  16
#define VIEW_DISTANCE       128
#define VITESSE_ACCROUPI	5
#define VITESSE_MARCHE		10
#define VITESSE_COURSE		15
#define GRAVITY				-9.8f

#define SHADER_PATH "../cubeplanet/media/shader/"

#endif // DEFINE_H__
