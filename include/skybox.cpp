#include "skybox.h"

SkyBox::SkyBox(){
  core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
}

SkyBox::~SkyBox(){
  if(VBO != 0)
      core->glDeleteBuffers(1, &VBO);
}

void SkyBox::setPosXPath(const QString &path){
  paths["posX"] = path;
}

void SkyBox::setPosYPath(const QString &path){
  paths["posY"] = path;
}

void SkyBox::setPosZPath(const QString &path){
  paths["posZ"] = path;
}

void SkyBox::setNegXPath(const QString &path){
  paths["negX"] = path;
}

void SkyBox::setNegYPath(const QString &path){
  paths["negY"] = path;
}

void SkyBox::setNegZPath(const QString &path){
    paths["negZ"] = path;
}

void SkyBox::setCubePath(const QString &posX, const QString &posY, const QString &posZ, const QString &negX, const QString &negY, const QString &negZ){
  this->setPosXPath(posX);
  this->setPosYPath(posY);
  this->setPosZPath(posZ);
  this->setNegXPath(negX);
  this->setNegYPath(negY);
  this->setNegZPath(negZ);
  this->init();
}

void SkyBox::init(){
  /*********** 1.cubemap纹理绑定 **************/
  if(paths.size() < 6)
    qDebug() << "ERROR::SKYBOX::INIT skybox textures's size less than 6!!!Pleass check the size of paths";

  /*
   * 帮助文档里说明，
   * 除void setData(const QImage &image, MipMapGeneration genMipMaps = GenerateMipMaps)这个函数的调用会自动分配物理内存外
   * 其他重载的setData()函数均需要提前分配纹理的内存
   * 在分配纹理内存之前，需要确定纹理的
   * Format，
   * dimension， 等同于Size，尺寸的意思
   * mipmap levels(当然，这个Vries也没要求生成多级纹理，故忽略),
   * array layer
   * cubeMap faces
   * 然后再分配内存。
   * 没办法，手动分配纹理内存，就是这么麻烦，还要确定QImage的存储格式为24位RGB
  */
  QImage posX = QImage(paths["posX"]).convertToFormat(QImage::Format_RGB888); //Right，默认纹理位32位RGB，不符合要求，必须转为24位RGB。
  QImage negX = QImage(paths["negX"]).convertToFormat(QImage::Format_RGB888); //Left
  QImage posY = QImage(paths["posY"]).convertToFormat(QImage::Format_RGB888); //Top
  QImage negY = QImage(paths["negY"]).convertToFormat(QImage::Format_RGB888); //Bottom
  QImage posZ = QImage(paths["posZ"]).convertToFormat(QImage::Format_RGB888); //Front
  QImage negZ = QImage(paths["negZ"]).convertToFormat(QImage::Format_RGB888); //Back

  texture = new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);

  texture->setSize(posX.width(), posX.height(), posX.depth()); //这个我猜测 是确定一面纹理的尺寸，然后allocate分配函数，根据TargeCubeMap，分配六面纹理的空间
  texture->setFormat(QOpenGLTexture::RGBFormat);
  texture->allocateStorage(QOpenGLTexture::RGB, QOpenGLTexture::UInt8); //分配内存

  texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveX, QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void*)posX.bits());
  texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveY, QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void*)posY.bits());
  texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveZ, QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void*)posZ.bits());
  texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeX, QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void*)negX.bits());
  texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeY, QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void*)negY.bits());
  texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeZ, QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void*)negZ.bits());

  texture->setMinificationFilter(QOpenGLTexture::Linear);     //纹理放大或缩小时，像素的取值方法 ，线性或就近抉择
  texture->setMagnificationFilter(QOpenGLTexture::Linear);
  texture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);   //设置纹理边缘的扩展方法
  texture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);
  //texture->setWrapMode(QOpenGLTexture::DirectionR, QOpenGLTexture::ClampToEdge); //Qt 显示不支持TargetCubeMap纹理类型R方向的扩展，不知道为什么，注释掉这个语句，一样可以正常运行


  /*********** 2.几何造型绑定 **************/
  float vertices[] = {
    // positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
    };

  core->glGenBuffers(1, &VBO);

  core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
  core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void SkyBox::draw(){
  core->glActiveTexture(GL_TEXTURE0);
  texture->bind();

  core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
  core->glEnableVertexAttribArray(0);
  core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

  core->glDrawArrays(GL_TRIANGLES, 0, 36);
}
