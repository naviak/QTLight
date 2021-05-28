#pragma once
#include <QVector3D>
#include <QVector2D>
struct Vertex {
	QVector3D pos;
	QVector3D normal;
	QVector2D texCoord;
};
enum class GLMod { TRIANGLES = 0, QUADS = 1 };
using Vertices = std::vector<Vertex>;
using Indices = std::vector<unsigned>;
