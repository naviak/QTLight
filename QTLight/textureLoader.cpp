#include "textureLoader.h"

bool TextureLoader::loadTexture(const std::string& path, std::shared_ptr<QOpenGLTexture>& texture,
	QOpenGLTexture::Filter filter)
{
	const auto textureImage = QImage(path.c_str());

	if (!textureImage.isNull()) {
		texture.reset(new QOpenGLTexture(textureImage));
		texture->setWrapMode(QOpenGLTexture::MirroredRepeat);
		texture->setMinificationFilter(filter);
		return true;
	}
	return false;
}
