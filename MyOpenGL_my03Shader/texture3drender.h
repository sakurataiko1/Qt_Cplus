//#ifndef TEXTURE3DRENDER_H
//#define TEXTURE3DRENDER_H


//class Texture3DRender
//{
//public:
//    Texture3DRender();
//};

//#endif // TEXTURE3DRENDER_H
//-----------------------------------

#ifndef TEXTURE3DRENDER_H
#define TEXTURE3DRENDER_H

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLExtraFunctions>
class Texture3DRender
{
public:
    Texture3DRender() = default;
    void initsize();
    void render(QOpenGLExtraFunctions *f,QMatrix4x4 &pMatrix,QMatrix4x4 &vMatrix,QMatrix4x4 &mMatrix,QVector3D &cameraLocation,QVector3D &lightLocation);

private:
    QOpenGLShaderProgram program_;
    QOpenGLTexture *texture_{nullptr};
    QOpenGLBuffer vbo_;
};

#endif // TEXTURE3DRENDER_H

