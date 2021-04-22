#pragma once

#include "Renderer.h"

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_Filepath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
	unsigned int m_TextureSlot;
public:
	Texture(const std::string& path);
	~Texture();
	Texture(const Texture&);

	void Bind(unsigned int slot = 0);
	void Unbind() const;

	inline int GetRendererID() const { return m_RendererID; }
	inline std::string GetFilePath() const { return m_Filepath; }
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline int GetTextureSlot() const { return m_TextureSlot; }
};