//#include "texture3drender.h"

//Texture3DRender::Texture3DRender()
//{

//}
//----------------------------------

#include "texture3drender.h"

void Texture3DRender::initsize()
{
    program_.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,"vsrc.vert");
    program_.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,"fsrc.frag");

    GLfloat texData[]{
        255,0,0,255,255,255,255,255,
        255,255,255,255,255,0,0,255,
        255,255,255,255,255,0,0,255,
        255,255,255,255,255,0,0,255,
        255,0,0,255,255,255,255,255
    };
    texture_ = new QOpenGLTexture(QOpenGLTexture::Target3D);
    texture_->create();
    texture_->setSize(2,2,2);
    texture_->setFormat(QOpenGLTexture::RGBA8_UNorm);
    texture_->allocateStorage();
    texture_->setData(QOpenGLTexture::RGBA,QOpenGLTexture::Float32,texData);
    texture_->setMinMagFilters(QOpenGLTexture::Nearest,QOpenGLTexture::Nearest);
    texture_->setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::ClampToEdge);
    texture_->setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::ClampToEdge);
    texture_->setWrapMode(QOpenGLTexture::DirectionR,QOpenGLTexture::ClampToEdge);

    GLfloat xSize=0.2f;
    GLfloat y1Size=0.1f;
    GLfloat y2Size=0.2f;
    GLfloat y3Size=0.3f;
    GLfloat y4Size=0.4f;
    GLfloat z1Size=0.4f;
    GLfloat z2Size=0.3f;
    GLfloat z3Size=0.2f;
    GLfloat z4Size=0.1f;
    GLfloat vertices[]{
            //第四个（最下面）立方体的下面
            xSize,0,0,
            xSize,0,z1Size,
            -xSize,0,z1Size,
            -xSize,0,z1Size,
            -xSize,0,0,
            xSize,0,0,
            //第四个（最下面）立方体的上面
            xSize,y1Size,0,
            -xSize,y1Size,0,
            -xSize,y1Size,z1Size,
            -xSize,y1Size,z1Size,
            xSize,y1Size,z1Size,
            xSize,y1Size,0,
            //第四个（最下面）立方体的前面
            xSize,y1Size,z1Size,
            -xSize,y1Size,z1Size,
            -xSize,0,z1Size,
            -xSize,0,z1Size,
            xSize,0,z1Size,
            xSize,y1Size,z1Size,
            //第四个（最下面）立方体的后面
            xSize,y1Size,0,
            xSize,0,0,
            -xSize,0,0,
            -xSize,0,0,
            -xSize,y1Size,0,
            xSize,y1Size,0,
            //第四个（最下面）立方体的左面
            -xSize,y1Size,z1Size,
            -xSize,y1Size,0,
            -xSize,0,0,
            -xSize,0,0,
            -xSize,0,z1Size,
            -xSize,y1Size,z1Size,
            //第四个（最下面）立方体的右面
            xSize,y1Size,z1Size,
            xSize,0,z1Size,
            xSize,0,0,
            xSize,0,0,
            xSize,y1Size,0,
            xSize,y1Size,z1Size,

            //第三个立方体的上面
            xSize,y2Size,0,
            -xSize,y2Size,0,
            -xSize,y2Size,z2Size,
            -xSize,y2Size,z2Size,
            xSize,y2Size,z2Size,
            xSize,y2Size,0,
            //第三个立方体的前面
            xSize,y2Size,z2Size,
            -xSize,y2Size,z2Size,
            -xSize,y1Size,z2Size,
            -xSize,y1Size,z2Size,
            xSize,y1Size,z2Size,
            xSize,y2Size,z2Size,
            //第三个立方体的后面
            xSize,y2Size,0,
            xSize,y1Size,0,
            -xSize,y1Size,0,
            -xSize,y1Size,0,
            -xSize,y2Size,0,
            xSize,y2Size,0,
            //第三个立方体的左面
            -xSize,y2Size,z2Size,
            -xSize,y2Size,0,
            -xSize,y1Size,0,
            -xSize,y1Size,0,
            -xSize,y1Size,z2Size,
            -xSize,y2Size,z2Size,
            //第三个立方体的右面
            xSize,y2Size,z2Size,
            xSize,y1Size,z2Size,
            xSize,y1Size,0,
            xSize,y1Size,0,
            xSize,y2Size,0,
            xSize,y2Size,z2Size,

            //第二个立方体的上面
            xSize,y3Size,0,
            -xSize,y3Size,0,
            -xSize,y3Size,z3Size,
            -xSize,y3Size,z3Size,
            xSize,y3Size,z3Size,
            xSize,y3Size,0,
            //第二个立方体的前面
            xSize,y3Size,z3Size,
            -xSize,y3Size,z3Size,
            -xSize,y2Size,z3Size,
            -xSize,y2Size,z3Size,
            xSize,y2Size,z3Size,
            xSize,y3Size,z3Size,
            //第二个立方体的后面
            xSize,y3Size,0,
            xSize,y2Size,0,
            -xSize,y2Size,0,
            -xSize,y2Size,0,
            -xSize,y3Size,0,
            xSize,y3Size,0,
            //第二个立方体的左面
            -xSize,y3Size,z3Size,
            -xSize,y3Size,0,
            -xSize,y2Size,0,
            -xSize,y2Size,0,
            -xSize,y2Size,z3Size,
            -xSize,y3Size,z3Size,
            //第二个立方体的右面
            xSize,y3Size,z3Size,
            xSize,y2Size,z3Size,
            xSize,y2Size,0,
            xSize,y2Size,0,
            xSize,y3Size,0,
            xSize,y3Size,z3Size,

            //第一个立方体的上面
            xSize,y4Size,0,
            -xSize,y4Size,0,
            -xSize,y4Size,z4Size,
            -xSize,y4Size,z4Size,
            xSize,y4Size,z4Size,
            xSize,y4Size,0,
            //第一个立方体的前面
            xSize,y4Size,z4Size,
            -xSize,y4Size,z4Size,
            -xSize,y3Size,z4Size,
            -xSize,y3Size,z4Size,
            xSize,y3Size,z4Size,
            xSize,y4Size,z4Size,
            //第一个立方体的后面
            xSize,y4Size,0,
            xSize,y3Size,0,
            -xSize,y3Size,0,
            -xSize,y3Size,0,
            -xSize,y4Size,0,
            xSize,y4Size,0,
            //第一个立方体的左面
            -xSize,y4Size,z4Size,
            -xSize,y4Size,0,
            -xSize,y3Size,0,
            -xSize,y3Size,0,
            -xSize,y3Size,z4Size,
            -xSize,y4Size,z4Size,
            //第一个立方体的右面
            xSize,y4Size,z4Size,
            xSize,y3Size,z4Size,
            xSize,y3Size,0,
            xSize,y3Size,0,
            xSize,y4Size,0,
            xSize,y4Size,z4Size,

            //第四个（最下面）立方体的下面
            0,-1,0, 0,-1,0, 0,-1,0,
            0,-1,0, 0,-1,0, 0,-1,0,
            //第四个（最下面）立方体的上面
            0,1,0, 0,1,0, 0,1,0,
            0,1,0, 0,1,0, 0,1,0,
            //第四个（最下面）立方体的前面
            0,0,1, 0,0,1, 0,0,1,
            0,0,1, 0,0,1, 0,0,1,
            //第四个（最下面）立方体的后面
            0,0,-1, 0,0,-1, 0,0,-1,
            0,0,-1, 0,0,-1, 0,0,-1,
            //第四个（最下面）立方体的左面
            -1,0,0, -1,0,0, -1,0,0,
            -1,0,0, -1,0,0, -1,0,0,
            //第四个（最下面）立方体的右面
            1,0,0, 1,0,0, 1,0,0,
            1,0,0, 1,0,0, 1,0,0,

            //第三个立方体的上面
            0,1,0, 0,1,0, 0,1,0,
            0,1,0, 0,1,0, 0,1,0,
            //第三个立方体的前面
            0,0,1, 0,0,1, 0,0,1,
            0,0,1, 0,0,1, 0,0,1,
            //第三个立方体的后面
            0,0,-1, 0,0,-1, 0,0,-1,
            0,0,-1, 0,0,-1, 0,0,-1,
            //第三个立方体的左面
            -1,0,0, -1,0,0, -1,0,0,
            -1,0,0, -1,0,0, -1,0,0,
            //第三个立方体的右面
            1,0,0, 1,0,0, 1,0,0,
            1,0,0, 1,0,0, 1,0,0,

             //第二个立方体的上面
             0,1,0, 0,1,0, 0,1,0,
             0,1,0, 0,1,0, 0,1,0,
             //第二个立方体的前面
             0,0,1, 0,0,1, 0,0,1,
             0,0,1, 0,0,1, 0,0,1,
             //第二个立方体的后面
             0,0,-1, 0,0,-1, 0,0,-1,
             0,0,-1, 0,0,-1, 0,0,-1,
             //第二个立方体的左面
             -1,0,0, -1,0,0, -1,0,0,
             -1,0,0, -1,0,0, -1,0,0,
             //第二个立方体的右面
             1,0,0, 1,0,0, 1,0,0,
             1,0,0, 1,0,0, 1,0,0,

             //第一个立方体的上面
             0,1,0, 0,1,0, 0,1,0,
             0,1,0, 0,1,0, 0,1,0,
             //第一个立方体的前面
             0,0,1, 0,0,1, 0,0,1,
             0,0,1, 0,0,1, 0,0,1,
             //第一个立方体的后面
             0,0,-1, 0,0,-1, 0,0,-1,
             0,0,-1, 0,0,-1, 0,0,-1,
             //第一个立方体的左面
             -1,0,0, -1,0,0, -1,0,0,
             -1,0,0, -1,0,0, -1,0,0,
             //第一个立方体的右面
             1,0,0, 1,0,0, 1,0,0,
             1,0,0, 1,0,0, 1,0,0,
    };
    vbo_.create();
    vbo_.bind();
    vbo_.allocate(vertices,sizeof vertices);
}

void Texture3DRender::render(QOpenGLExtraFunctions *f, QMatrix4x4 &pMatrix, QMatrix4x4 &vMatrix, QMatrix4x4 &mMatrix, QVector3D &cameraLocation, QVector3D &lightLocation)
{
    f->glEnable(GL_CULL_FACE);
    f->glEnable(GL_DEPTH_TEST);

    program_.bind();
    vbo_.bind();
    f->glActiveTexture(GL_TEXTURE0 + 0);
    program_.setUniformValue("uPMatrix",pMatrix);
    program_.setUniformValue("uVMatrix",vMatrix);
    program_.setUniformValue("uMMatrix",mMatrix);
    program_.setUniformValue("uCamera",cameraLocation);
    program_.setUniformValue("uLightLocation",lightLocation);
    program_.setUniformValue("sTexture",0);

    program_.enableAttributeArray(0);
    program_.enableAttributeArray(1);
    program_.setAttributeBuffer(0,GL_FLOAT,0,3,3*sizeof(GLfloat));
    program_.setAttributeBuffer(1,GL_FLOAT,21*6*3*sizeof(GLfloat),3,3*sizeof(GLfloat));
    texture_->bind(0);
    f->glDrawArrays(GL_TRIANGLES,0,21 * 6);

    program_.disableAttributeArray(0);
    program_.disableAttributeArray(1);
    texture_->release();
    vbo_.release();
    program_.release();

    f->glDisable(GL_CULL_FACE);
    f->glDisable(GL_DEPTH_TEST);

}
