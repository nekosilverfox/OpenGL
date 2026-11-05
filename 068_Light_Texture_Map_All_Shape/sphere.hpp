#ifndef SPHERE_H
#define SPHERE_H


#include <vector>
#include <QMatrix4x4>


//将球横纵划分成50*50的网格
const float R_SPHERE = 1.0f;
const float STEP_ANGLE_SPHERE = 90.0f;


class Sphere
{
public:
    Sphere();
    Sphere(const float r, const float step_angle);

    /* 获取绘制三角形的数量 */
    unsigned int getNumTrianglesinSphere();

    unsigned long getPointCount();


private:
    void _genVectorVerticesAndIndices();


public:
    std::vector<QVector3D> vertices;  // 顶点

    QMatrix4x4 mat_model;

private:
    float _r;
    float _step_angle;
};

#endif // SPHERE_H
