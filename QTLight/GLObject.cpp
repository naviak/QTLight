#include "GLObject.h"
#include "meshLoader.h"
#include "textureLoader.h"

GLObject::GLObject(std::string&& name) : _name(name)
{
}

void GLObject::initialize()
{
	setMesh();
}

void GLObject::render(QOpenGLShaderProgram& program)
{
	_modelMatrix.rotate(_rotationParam.w(),
		_rotationParam.x(), _rotationParam.y(), _rotationParam.z());
	program.setUniformValue("normalMatrix", _modelMatrix.inverted().transposed());
	program.setUniformValue("model", _modelMatrix);
	for (auto& mesh : meshes) 
	{
		mesh.render(program);
	}
}

void GLObject::setPos(const QVector3D& pos)
{
	_pos = pos;
	_modelMatrix.translate(_pos);	
}

void GLObject::setRotation(const QVector4D& rot)
{
	_rotationParam = rot;
}

QVector3D GLObject::getPos() const
{
	return _pos;
}

std::string GLObject::getName() const
{
	return _name;
}

bool GLObject::setMesh()
{
	if (!MeshLoader::loadMesh(_name,
		meshes)) {
		return false;
	}
	return true;
}

