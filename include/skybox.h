#ifndef SKYBOX_H
#define SKYBOX_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLTexture>
#include <QMap>
#include <QDebug>

class SkyBox
{
public:
  SkyBox();
  ~SkyBox();
  void setPosXPath(const QString& path);
  void setPosYPath(const QString& path);
  void setPosZPath(const QString& path);
  void setNegXPath(const QString& path);
  void setNegYPath(const QString& path);
  void setNegZPath(const QString& path);
  void setCubePath(const QString& posX, const QString& posY, const QString& posZ,
                   const QString& negX, const QString& negY, const QString& negZ);

  void init();
  void draw();
private:
  QOpenGLFunctions_3_3_Core *core;
  QOpenGLTexture *texture;
  GLuint VBO;

  QMap<QString, QString> paths;
};

#endif // SKYBOX_H
