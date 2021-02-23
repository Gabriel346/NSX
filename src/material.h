#ifndef MATERIAL_H
#define MATERIAL_H

#include <QString>

class QOpenGLShaderProgram;
class QMatrix4x4;
class QVector3D;
class QOpenGLTexture;

class Material // TODO QObject
{
public:
    Material();

    QString name;

    QString vertex_shader_filename;
    QString fragment_shader_filename;

    //File vertex_shader
    //File fragment_shader

    QOpenGLShaderProgram *shaderProgram;

    void setModelViewProj(const QMatrix4x4&);
    void setModelInverseTranspose(const QMatrix4x4&);
    void setColor(const QVector3D&);
    void setLight(const QVector3D&);

    int u_modelViewProj;
    int u_modelInverseTranspose;
    int u_light;

    // parametri variabili
    int u_color;
    QOpenGLTexture *texture;


    void testVariables();



};

#endif // MATERIAL_H
