#include "sphere.hpp"
#include "foxmath.h"
#include <math.h>


Sphere::Sphere() :
    _r(R_SPHERE),
    _step_angle(STEP_ANGLE_SPHERE)
{
    _genVectorVerticesAndIndices();
}


Sphere::Sphere(const float r, const float step_angle) :
    _r(r),
    _step_angle(step_angle)
{
    _genVectorVerticesAndIndices();
}


/* 获取绘制三角形的数量 */
unsigned int Sphere::getNumTrianglesinSphere()
{
    return vertices.size()*3 / 6;
}


/**
 * 算法参考：https://dhbloo.github.io/2020/03/12/Sphere/#%E7%90%83%E5%9D%90%E6%A0%87%E8%BD%AC%E6%8D%A2
 */
void Sphere::_genVectorVerticesAndIndices()
{
    /* 储存球上的所有的点 */
    std::vector<QVector3D> points;


    /* 绘制上半球的所有顶点 */
    const unsigned int num_point_circle = 360.0f / _step_angle;  // 每个圈要绘制几个点
    const unsigned int num_circle       = 180.0f / _step_angle;  // 半球上需要绘制圈圈的个数


    /* 开始从最底部处一圈一圈的向上绘制，注意：最底部的点都是重叠了的 */
    float current_xy_angle = -90.0f;  // xy代表在[右]手坐标系下，x 轴与 y 轴的夹角
    for (unsigned long i = 0; i <= num_circle; i++)
    {
        float current_xz_angle = 0.0f;  // 水平角度
        qDebug() << "\n[INFO] ---> 生成第：" << i << "圈， 垂直角度：" << current_xy_angle;

        /* 圈上的点 */
        for (unsigned long j = 0; j <= num_point_circle; j++)
        {
            /* 【重点 | 注意】sin() 默认是弧度！！，不是角度！！ */
            float x = _r * sin(current_xz_angle*M_PI/180) * cos(current_xy_angle*M_PI/180);
            float y = _r * sin(current_xy_angle*M_PI/180);
            float z = _r * cos(current_xz_angle*M_PI/180) * cos(current_xy_angle*M_PI/180);

            points.push_back(QVector3D(x, y, z));

            current_xz_angle += _step_angle;
        }
        current_xy_angle += _step_angle;
    }


    for (int i = 0; i < points.size(); i++)
    {
//        qDebug() << "当前 i = " << i << "取模：" << i % (num_point_circle + 1) << "真实顶点数量：" << points.size();
//        if ((i % (num_point_circle + 1) == 0) && (i != 0))
//        {
//            qDebug() << "->跳过 i = " << i;
//            continue;
//        }


        /* 正三角 */
        QVector3D current_point          = points[i + 0];
        QVector3D current_next_point     = points[i + 1];
        QVector3D current_next_top_point = points[i + 1 + num_point_circle + 1];

        QVector3D current_normal = getNormalVector(current_point,
                                                   current_next_point,
                                                   current_next_top_point);  // 法线

        vertices.push_back(current_point);
        vertices.push_back(current_normal);

        vertices.push_back(current_next_point);
        vertices.push_back(current_normal);

        vertices.push_back(current_next_top_point);
        vertices.push_back(current_normal);

        /* 倒三角 */
                  current_point         = points[i + 0];
        QVector3D current_top_point     = points[i + 0 + num_point_circle + 1];
        QVector3D current_top_next_point= points[i + 1 + num_point_circle + 1];

        current_normal = -getNormalVector(current_point,
                                          current_top_point,
                                          current_top_next_point);  // 法线


        vertices.push_back(current_point);
        vertices.push_back(current_normal);

        vertices.push_back(current_top_point);
        vertices.push_back(current_normal);

        vertices.push_back(current_top_next_point);
        vertices.push_back(current_normal);
    }
    qDebug() << "[INFO] 球体顶点生成结束，顶点数" << points.size();
}
