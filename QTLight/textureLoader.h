#pragma once
#include <QOpenGLTexture>

class TextureLoader
{
public:
	static bool loadTexture(const std::string& path, std::shared_ptr<QOpenGLTexture>& texture, QOpenGLTexture::Filter filter);
};

