#ifndef BLOCKINFO_H__
#define BLOCKINFO_H__

#include <iostream>
#include <string>
#include "define.h"
#include "textureatlas.h"

class BlockInfo
{
public:
	BlockInfo();
    BlockInfo(BlockType type, const std::string& nom);
    ~BlockInfo();

    BlockType GetType() const;

    void SetDurabilite(int durabilite);
    int GetDurabilite() const;

    void Afficher() const;
	void GenerateTexCoord(int idx, TextureAtlas& texAtlas);
	float m_texCoordX, m_texCoordY, m_largeur, m_hauteur;
private:
    BlockType m_type;
    std::string m_nom;
    int m_durabilite;
};

#endif // BLOCKINFO_H__
