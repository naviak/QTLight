#pragma once
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QColor>

#include "mesh.h"
class GLObject : protected QOpenGLFunctions
{
public:
    explicit GLObject(std::string&& name);
    virtual ~GLObject() = default;
    void initialize();
	void render(QOpenGLShaderProgram& program);

	void setPos(const QVector3D& pos);
	void setRotation(const QVector4D& rot);

	QVector3D getPos() const;
	std::string getName() const;
protected:
	bool setMesh();
	std::vector<Mesh> meshes;
	QVector3D _pos;
	QVector4D _rotationParam;
	QMatrix4x4 _modelMatrix;
private:
	std::string _name;
};
