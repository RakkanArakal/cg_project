# 古风设计游戏作业报告



​		本游戏是基于qt5.0,使用QOpenGL系列函数实现底层OpenGL绘图方法的一款古风设计游戏。

​        在游戏中，玩家可以在画布界面根据自己的创意，通过创造Beizier控制顶点并且进行拖动的方式，编辑轮廓曲线生成3D模型。玩家可以为其附上高达6种不同的纹理。模型的显示与曲线实时同步，意味着玩家可以即时修改模型上的瑕疵。模型设计完成后，玩家可以保存模型，在场景界面中导入。

​        在场景界面中，玩家可以导入已设计好的模型，在模型控制台中选中模型后对其进行放缩，移动或移除。选中多个模型后可以多个模型同时放缩，移动。在光照控制台中，玩家可以进行对场景光照模式的更换以及光照参数的更改。场景同时搭配了落花特效，满足玩家一切需求！




### 实现过程



首先在网上学习到了使用Qt里的openGL库也能完成相应的图形显示，并且Qt平台的GUI操作较为便利，所以决定在Qt进行项目的搭建。创建完菜单界面后，按照要求将主要功能分到两个子界面中实现，在画板界面中依次实现了以下功能：

- Bezier曲线的生成及绘制
- 窗口坐标至3D世界坐标的变换
- 根据Bezier曲线生成旋转体模型 
- 3D模型的移动，放缩
- 模型的存储及载入

接着在场景界面中依次实现了以下功能：

- 天空盒及可移动相机的实现
- 地板及初始模型的载入
- 模型载入及队列按钮的绑定
- 模型选中后的移动及放缩
- 光照系统的加入
- 落花的实现

游戏代码部分至此结束。





### 具体方案

#### Bezier曲线：

当屏幕上生成的控制顶点大于2个时，便开始生成Bezier曲线并进行绘制。使用的Casteljau递推公式为：
$$
P_i^r(t) = (1-t) P_i^{r-1}(t)  + tP_{i+1}^{r-1}(t)\\
r = 1,2,...,n  \:\:\:\:\:\:\:\:  i = 0,1,...,n-r \:\:\:\:\:\:\:\: t \in(0,1)
$$
存储Bezier曲线每个点的是一个大小为150的QVector，运算的步长**t**为1/150，Bezier曲线的阶次**r**由玩家点击产生的控制顶点数所决定。

#### 坐标变换：

窗口大小设置为1280*800且固定不可拖动，相机视角位置为（0，0，3）。计算得屏幕对应坐标如下：


对应变换公式为：
$$
\color{Red} x \color{black} =    [(x-640)/640]*2.0f\\
\color{Red}  y \color{black} =    - [(x-400)/400]*1.25f
$$
由于Y轴的方向不同，计算y坐标时需要取负值。

Bezier控制顶点，控制顶点之间的连线以及Bezier曲线便能经过坐标变换出现在屏幕上。

而设置背景时由于要考虑到，开启深度检测之后，模型显示必须位于背景之前，所以将背景作为纹理绑定到了右上角顶点为（4.0f,2.5f,-3.0f)的长方形上。

#### 生成旋转体：

旋转体模型通过绘制三角面片的方式生成。


将该Bezier曲线围绕Y轴旋转一周，每隔10°取下一个点，通过简单的半径弧度制运算便能得到整个模型上所有点的坐标。在VBO按照A、B、C、D的顺序存入点数据，使用**GL_TRIANGLE_STRIP**的方式绘制，便能得到旋转体模型。将纹理绑定至该模型时，按照此法绘制的模型的起始点A对应纹理坐标的（1.0f，1.0f），终点对应（0.0f，0.0f），同样通过简单的计算便能将纹理坐标一一对应至模型上。

#### 模型的移动及缩放

在画板界面中，模型绘制或载入后都需要通过坐标变换移动到相应位置，如菜单栏的4个预载入模型，实际上是简单绘制了4个空白QPushButton，再将4个固定模型移动到对应按钮后面。

#### 模型存储及载入

考虑到空间利用率以及Bezier曲线类的复用性，存储文件里仅仅保存了该模型的纹理名称以及每个控制顶点在窗口界面上的坐标。每次载入时，将文件里的各个点读入至控制顶点所在QVector，再经由Bezier类生成相应曲线后绘制模型，所以此处的模型载入实际上相当于将画板清除后重新再按照记录在画板上点了那么多个控制顶点。

#### 相机、天空盒、地面及初始模型的载入

到了场景界面，天空盒和相机的实现基本都参考LearnOpenGL上的方式直接实现。由于模型无法直接放置至天空盒底部，重新生成了一块地砖纹理的平面作为地面，但仍无法避免移动时产生的突兀感，最后只能通过限制相机移动来减缓。初始模型为预载入模型里的一张桌子，直接放置在场景中并绑定队列1。

#### 场景界面中的模型

为了能够实现多个模型同时移动的效果（例如茶盘里装着茶杯，想要两个模型一起移动），选择了类似即时战略游戏中编队的方式，生成8个队列按钮，但每个按钮只能绑定一个模型。载入模型时，将其绘制时需要的参数都存放在一个myModel结构体中，并使用QMap保存，删除模型时同时删除记录即可。未选中模型时可以自由移动相机视角，选中模型后一切操作变为对模型的移动和放缩，此处需要将传入相机类的移动参数直接对应修改选中模型的对应参数，便能实现模型移动及放缩。

#### 光照系统

载入场景时默认使用反光度为8.0冯氏光照模型，通过点击光照按钮可以切换为默认反光度为32.0的Blinn-Phong模型，加入了QSlider滚动条组件来进行反光度的修改，范围为0-50。

根据场景需求把片段着色器中的漫反射光照系数从0.05f调高至0.20f，其余参数照常。

#### 落花的实现

学习了粒子系统后，发现其本质上也就是对模型的绘制，于是决定自己手动实现一个花瓣结构体，成员分别为可以支持透明纹理的平面，其当前坐标及其下落速度。场景界面初始化时，在每10*10的位置上生成一个花瓣（贴了花瓣纹理的1x1平面），使其匀速下落，下落速度为0.25至0.05之间的随机值，每帧画面更新时更新其所在高度，同时根据自己的下落速度和当前位置确定一个旋转角度及旋转轴。当其落到地面上时，将其放回高空同时生成新的下落速度。通过花瓣按钮开关控制是否显示。



### 参考资料

[LearnOpenGL CN (learnopengl-cn.github.io)](https://learnopengl-cn.github.io/)
