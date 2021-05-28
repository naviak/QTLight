#pragma once

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_3_0>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include "vertex.h"
struct Material {
	QColor diffuse, specular;
};

class Mesh;
using MeshPtr = std::unique_ptr<Mesh>;

class Mesh final : protected QOpenGLFunctions_3_0 {
public:
	Mesh();
	Mesh(const Mesh& mesh);
	~Mesh();

	void initialize();
	void render(QOpenGLShaderProgram& program);
	void rotate(QVector4D rotparam);
	void translate(QVector3D pos);
	QMatrix4x4 _modelMatrix;
	Vertices vertices;
	Indices indices;
	QOpenGLBuffer _vertexBuf, _indexBuf;
	std::shared_ptr<QOpenGLTexture> texture, normalMap;

	GLMod mode = GLMod::TRIANGLES;

	Material material = { { 255, 255, 175 },
											 { 255, 255, 255} };
};