#pragma once
#include <QOpenGLShaderProgram>
#include <QLabel>
#include <QPalette>
#include <QOpenGLWidget>
#include <QMouseEvent>
#include "camera.h"
#include "GLObject.h"
#include "MouseInput.h"
#include "fpsmonitor.h"
#include "Input.h"

class EarthWidget final : public QOpenGLWidget {
	Q_OBJECT

public:
	explicit EarthWidget(QWidget* parent = nullptr);

protected:
	void initializeGL() override;
	void paintGL() override;
	QSize sizeHint() const override { return QSize(1200, 480); }
	void moveCamera() {
		std::map<int, QVector3D> controls = {
			{Qt::Key_W, {0,0,1}},
			{Qt::Key_S, {0,0,-1}},
			{Qt::Key_A, {-1,0,0}},
			{Qt::Key_D, {1,0,0}},
			{Qt::Key_E, {0,1,0}},
			{Qt::Key_Q, {0,-1,0}} };

		for (auto& [key, dir] : controls)
		{
			if (Input::keyPressed(key))
			{
				_camera.translate(dir * 0.1f);
			}
		}
		if (Input::keyPressed(Qt::LeftButton))
			_camera.look(MouseInput::delta().x() * 0.5f, MouseInput::delta().y() * 0.5f);
	};
	void wheelEvent(QWheelEvent* event) override;
	void keyPressEvent(QKeyEvent* e) override
	{
		Input::pressKey(e->nativeVirtualKey());
		QOpenGLWidget::keyPressEvent(e);
	}

	void keyReleaseEvent(QKeyEvent* e) override
	{
		Input::releaseKey(e->nativeVirtualKey());
		QOpenGLWidget::keyReleaseEvent(e);
	}

	void mouseMoveEvent(QMouseEvent* e) override
	{
		MouseInput::mouseCallback(e->pos());
		QOpenGLWidget::mouseMoveEvent(e);
	}

	void mousePressEvent(QMouseEvent* e) override
	{
		Input::pressKey(e->button());
		QOpenGLWidget::mousePressEvent(e);
	}

	void mouseReleaseEvent(QMouseEvent* e) override
	{
		Input::releaseKey(e->button());
		QOpenGLWidget::mouseReleaseEvent(e);
	}
	void resizeGL(int w, int h) override
	{
		projection.setToIdentity();
		projection.perspective(60.0f, GLfloat(w) / h, 0.01f, 100.0f);
		label->move(width() -50, 0);
	}
private:
	QOpenGLShaderProgram _shader;
	QMatrix4x4 projection;
	std::vector<std::shared_ptr<GLObject>> _objects;
	Camera _camera;
	QLabel* label;
	FpsMonitor fps;
	QPalette sample_palette;
	bool isPressed;
	QPoint presPos;
};
