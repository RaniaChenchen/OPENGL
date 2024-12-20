

// #include "openglrenderer.h"

// OpenGLRenderer::OpenGLRenderer(QQuickItem *parent) : QQuickItem(parent)
// {
//     // Code d'initialisation de l'OpenGL
// }
#include "openglrenderer.h"
#include <QOpenGLFramebufferObject>

OpenGLRenderer::OpenGLRenderer() {
    initializeOpenGLFunctions();
}

OpenGLRenderer::~OpenGLRenderer() {}

void OpenGLRenderer::render() {
    // Votre logique OpenGL pour dessiner
}

QOpenGLFramebufferObject *OpenGLRenderer::createFramebufferObject(const QSize &size) {
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4); // Anti-aliasing
    return new QOpenGLFramebufferObject(size, format);
}
