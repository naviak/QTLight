#include "earthWidget.h"

#include <QKeyEvent>

#include "MouseInput.h"

EarthWidget::EarthWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    label = new QLabel(this);
    label->move(width() - 50, 0);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    
}

void EarthWidget::initializeGL()
{
    _shader.addShaderFromSourceFile(QOpenGLShader::Vertex, "Shaders/obj.vs");
    _shader.addShaderFromSourceFile(QOpenGLShader::Fragment, "Shaders/obj.fs");
    _shader.link();
    _shader.bind();

    std::shared_ptr<GLObject> earth = std::make_shared<GLObject>("Earth");
    earth->setPos({ 0.f, 0.f, -1.f });
    earth->setRotation({ 0.f, 1.f, 0.f, 0.3f });
    earth->initialize();
    std::shared_ptr<GLObject> sun = std::make_shared<GLObject>("Sun");
    sun->setPos({ -10.f, 0.f, -1.5f });
    sun->setRotation({ 0.f, 1.f, 0.f, 0.3f });



    //std::shared_ptr<GLObject> male = std::make_shared<GLObject>("Male");
    //male->setPos({ 10.f, 0.f, -1.f });
    //male->setRotation({ 0.f, 1.f, 0.f, 0.3f });
	
    _objects.push_back(std::move(sun));
    _objects.push_back(std::move(earth));
    //_objects.push_back(std::move(male));
	
	sample_palette.setColor(QPalette::Window, Qt::darkGreen);
    setFocusPolicy(Qt::StrongFocus);
}

void EarthWidget::paintGL()
{
    label->setAutoFillBackground(true);
    label->setText(std::to_string(1 / fps.getFPS()).c_str());
    label->setPalette(sample_palette);
    label->show();
    QMatrix4x4 projection;
    projection.perspective(30.f, 1.7f, 0.1f, 100.0f);
    _shader.setUniformValue("view", _camera.getViewMatrix());
    _shader.setUniformValue("viewPos", _camera.position);
    _shader.setUniformValue("projection", projection);

    for (auto& obj : _objects) {
        if (obj->getName() == "Sun") {
            _shader.setUniformValue("lightPos", obj->getPos());
            _shader.setUniformValue("isLighter", 1);
        }
        else {
            _shader.setUniformValue("isLighter", 0);
        }

        obj->render(_shader);
    }

    moveCamera();
    Input::reset();
    MouseInput::reset();
    update();
}

void EarthWidget::wheelEvent(QWheelEvent* event)
{
    auto dr = 0.f;
    const auto offset = 1.f;
    if (event->angleDelta().y() > 0) {
        dr = offset * _camera.front.z() / abs(_camera.front.z());
    }
    else if (event->angleDelta().y() < 0) {
        dr = -offset * _camera.front.z() / abs(_camera.front.z());
    }
    _camera.position = { _camera.position.x() + dr * _camera.front.x(),
                    _camera.position.y() + dr * _camera.front.y(),
                    _camera.position.z() + dr * _camera.front.z() };
}