#define STB_IMAGE_IMPLEMENTATION
#include<QTime>
#include<QMouseEvent>
#include "openwidget.h"

OpenWidget::OpenWidget()
{


}

OpenWidget::~OpenWidget()
{
    //释放VAOVBO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
}

void OpenWidget::initializeGL()
{
    initializeOpenGLFunctions();

    //glClearColor(0.0f, 0.0f, 0.0f, 0.1f);
    //深度测试
    glEnable(GL_DEPTH_TEST);
    //线框模式
    //glPolygonMode(GL_FRONT_AND_BACK ,GL_LINE );
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);  // Antialias the lines
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //着色器
    shaderProgram=new QOpenGLShaderProgram;
    vshader=new QOpenGLShader(QOpenGLShader::Vertex,shaderProgram);
    fshader=new QOpenGLShader(QOpenGLShader::Fragment,shaderProgram);
    vshader->compileSourceCode(
                "#version 330 core\n"
                "layout (location = 0) in vec3 aPos;\n"
                "layout (location = 1) in vec3 PosColor;\n"
                "layout (location = 2) in vec2 aTexCoord;\n"
                "out vec3 positionColor;\n"
                "out vec2 TexCoord;\n"
                "uniform mat4 model;\n"
                "uniform mat4 view;\n"
                "uniform mat4 projection;\n"
                " void main()\n"
                " {\n"
                " gl_Position =projection * view * model * vec4(aPos, 1.0);\n"
                " positionColor=PosColor;\n"
                "TexCoord = aTexCoord;\n"
                " }\n"
                );
    fshader->compileSourceCode(
                "#version 330 core\n"
                "out vec4 FragColor;\n"
                "in vec3 positionColor;\n"
                "in vec2 TexCoord;\n"
                "uniform sampler2D ourTexture;\n"
                "void main()\n"
                "{\n"
                "FragColor = texture(ourTexture, TexCoord) * vec4(positionColor, 1.0);\n"
                "}\n"
                );
    shaderProgram->addShader(vshader);
    shaderProgram->addShader(fshader);
    shaderProgram->link();
    //纹理
    glEnable(GL_TEXTURE_2D);//允许采用2D纹理技术
    glShadeModel(GL_SMOOTH);//设置阴影平滑模式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//当所显示的纹理比加载进来的纹理小时，采用GL_LINEAR的方法来处理
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//当所显示的纹理比加载进来的纹理大时，采用GL_LINEAR的方法来处理
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int width, height, nrChannels;


    //    unsigned char *data = stbi_load("D:/1 a project/Fractal_Tree/Fractal_Tree/IMG_20200408_142732.jpg", &width, &height, &nrChannels, 0);
    //        if (data)
    //       {
    //            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //            glGenerateMipmap(GL_TEXTURE_2D);
    //         }
    //        else
    //        {
    //              qDebug("Failed to load texture" );
    //         }
    //    stbi_image_free(data);


    glUniform1i(glGetUniformLocation(shaderProgram->programId(), "texture"), 0);
    //顶点数据
    float vertices[] = {
        // 位置              // 颜色         //纹理
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,1.0f, 0.0f,
        0.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,0.5f, 1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //绑定VAO
    glBindVertexArray(VAO);

    //绑定VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //把顶点数组复制到VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //纹理坐标
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //解除绑定VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //解除绑定VAO
    glBindVertexArray(0);
}
void OpenWidget::paintGL()
{
    QMetaObject::invokeMethod(this,"update",Qt::QueuedConnection);
    glClearColor(0.3f, 0.3f, 0.3f, 0.3f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //paint
    //激活着色器
    glUseProgram(shaderProgram->programId());
    // Transform坐标变换矩阵
    float ra=QTime(0,0,0).secsTo(QTime::currentTime());

    QMatrix4x4 projection, view;
    projection.perspective(camera->zoom, (GLfloat)width()/(GLfloat)height(), 0.1f, 2000.f);
    view = camera->getViewMatrix();

//    glm::mat4 model(1);//model矩阵，局部坐标变换至世界坐标
//    model = glm::rotate(model, (float)glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//    glm::mat4 view(1);//view矩阵，世界坐标变换至观察坐标系
//    view = camera.GetViewMatrix();
//    glm::mat4 projection(1);//projection矩阵，投影矩阵
//    projection = glm::perspective(glm::radians(camera.Zoom), (float)this->width()/this->height(), 0.1f, 100.0f);
//    glUniformMatrix4fv(glGetUniformLocation(shaderProgram->programId(),"model"), 1, GL_FALSE,&model[0][0]);
//    glUniformMatrix4fv(glGetUniformLocation(shaderProgram->programId(),"view"), 1, GL_FALSE,&view[0][0]);
//    glUniformMatrix4fv(glGetUniformLocation(shaderProgram->programId(),"projection"), 1, GL_FALSE,&projection[0][0]);


    //绑定顶点缓存对象
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, texture);
    //开始绘制
    glDrawArrays(GL_TRIANGLES, 0, 6);
    //解除绑定
    glBindVertexArray(0);
}


void OpenWidget::keyPressEvent(QKeyEvent *event){
    GLuint key = event->key();
    if(key >= 0 && key <= 1024)
        this->keys[key] = GL_TRUE;

    if(key == Qt::Key_Escape){
        this->close();
        delete this;
    }
}
void OpenWidget::keyReleaseEvent(QKeyEvent *event){
    GLuint key = event->key();
    if(key >= 0 && key <= 1024)
        this->keys[key] = GL_FALSE;
}

void OpenWidget::mouseMoveEvent(QMouseEvent *event){
    GLint xpos = event->pos().x();
    GLint ypos = event->pos().y();
    if(isLeftMousePress){
        if (isFirstMouse){
            lastX = xpos;
            lastY = ypos;
            isFirstMouse = GL_FALSE;
        }

        GLint xoffset = xpos - lastX;
        GLint yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;
        camera->processMouseMovement(xoffset, yoffset);

    }
    //    updateGL();
}

void OpenWidget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton)//注意是button（）不是buttons（）；
        isLeftMousePress = GL_TRUE;
}

void OpenWidget::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){ //注意是button（）不是buttons（）；
        isLeftMousePress = GL_FALSE;
        isFirstMouse = GL_TRUE;
    }
}

