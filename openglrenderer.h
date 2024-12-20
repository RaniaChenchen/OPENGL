
// #ifndef OPENGLRENDERER_H
// #define OPENGLRENDERER_H

// #include <QQuickItem>

// class OpenGLRenderer : public QQuickItem
// {
//     Q_OBJECT
// public:
//     explicit OpenGLRenderer(QQuickItem *parent = nullptr);
// };

// #endif // OPENGLRENDERER_H
#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include <QQuickFramebufferObject>
#include <QOpenGLFunctions>

class OpenGLRenderer : public QQuickFramebufferObject::Renderer, protected QOpenGLFunctions {
public:
    OpenGLRenderer();
    ~OpenGLRenderer();

    void render() override;
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;
};

#endif // OPENGLRENDERER_H
