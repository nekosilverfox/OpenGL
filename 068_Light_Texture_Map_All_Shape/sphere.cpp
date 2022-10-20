#include "sphere.hpp"
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
    return vertices.size() / 3;
}



void Sphere::_genVectorVerticesAndIndices()
{
#if 0
    std::vector<float> tmp_vetices;


    /* 绘制上半球的所有顶点 */
    const unsigned int num_point_circle = 360.0f / _angle_step; // 每个圈要绘制几个点
    const unsigned int num_circle = 180.0 / _angle_step;  // 半球上需要绘制圈圈的个数
    const float step_r = _r / (float)num_circle;    // 每向上一圈，需要缩小半径的步长

    /* 开始从赤道处一圈一圈的向上绘制 */
    float current_y = 0.0;
    float current_y_angle = 0.0;
    float current_r = _r;
    for (int i = 0; i < num_circle; i++)
    {
        float current_angle = 0.0f;

        /* 圈上的点 */
        for (int j = 0; j <= num_point_circle; j++)
        {
            tmp_vetices.push_back(current_r*cos(current_angle*M_PI/180)); // x，【重点】sin() 默认是弧度！！，不是角度！！
            tmp_vetices.push_back(current_y);                           // y
            tmp_vetices.push_back(current_r*sin(current_angle*M_PI/180)); // z
            current_angle += _angle_step;
        }

        current_r -= step_r;
        current_y_angle += acos(current_r / _r);
        current_y = _r * sin(current_y_angle*M_PI/180);
    }

    this->vertices = tmp_vetices;


#endif
#if 0
    /*2-计算球体顶点*/
    //生成球的顶点
    for (unsigned int y = 0; y <= _y_segments; y++)
    {
        for (unsigned int x = 0; x <= _x_segments; x++)
        {
            float xSegment = (float)x / (float)_x_segments;
            float ySegment = (float)y / (float)_y_segments;
            float xPos = cos(xSegment * 2.0f * M_PI) * sin(ySegment * M_PI);
            float yPos = cos(ySegment * M_PI);
            float zPos = sin(xSegment * 2.0f * M_PI) * sin(ySegment * M_PI);
            vertices.push_back(xPos);
            vertices.push_back(yPos);
            vertices.push_back(zPos);
        }
    }

    //生成球的Indices
    for (unsigned int i = 0; i < _y_segments; i++)
    {
        for (unsigned int j = 0; j < _x_segments; j++)
        {
            indices.push_back(i * (_x_segments + 1) + j);
            indices.push_back((i + 1) * (_x_segments + 1) + j);
            indices.push_back((i + 1) * (_x_segments + 1) + j+1);
            indices.push_back(i* (_x_segments + 1) + j);
            indices.push_back((i + 1) * (_x_segments + 1) + j + 1);
            indices.push_back(i * (_x_segments + 1) + j + 1);
        }
    }
#endif

#if 0
    const float r = 1.0f;
    const int stacks = 10, sectors = 2 * stacks;
    std::vector<float> verts, norms, texCoords;
    std::vector<int> indices;

    for (int j = 0; j <= stacks; j++) {
        float v   = (float)j / stacks;
        float phi = M_PI * v;

        for (int i = 0; i <= sectors; i++) {
            float u     = (float)i / sectors;
            float theta = 2 * M_PI * u;

            verts.push_back(r * sin(phi) * cos(theta));
            verts.push_back(r * cos(phi));
            verts.push_back(r * cos(phi) * sin(theta));
            norms.push_back(sin(phi) * cos(theta));
            norms.push_back(cos(phi));
            norms.push_back(cos(phi) * sin(theta));
            texCoords.push_back(u); texCoords.push_back(v);
        }
    }

    for (int j = 0; j < stacks; j++) {
        int k1 = j * (sectors + 1);
        int k2 = k1 + sectors + 1;

        for (int i = 0; i < sectors; i++, k1++, k2++) {
            if (j != 0) {
                indices.push_back(k1);
                indices.push_back(k1 + 1);
                indices.push_back(k2);
            }

            if (j != stacks - 1) {
                indices.push_back(k2);
                indices.push_back(k1 + 1);
                indices.push_back(k2 + 1);
            }
        }
    }
    this->vertices = verts;
    this->indices = indices;
#endif

#if 0
    unsigned int indexCount;
    std::vector<QVector3D> positions;
    std::vector<QVector2D> uv;
    std::vector<QVector3D> normals;
    std::vector<unsigned int> indices;

    const unsigned int X_SEGMENTS = 64;
    const unsigned int Y_SEGMENTS = 64;
    const float PI = 3.14159265359;
    for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
    {
        for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
        {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

            positions.push_back(QVector3D(xPos, yPos, zPos));
            uv.push_back(QVector2D(xSegment, ySegment));
            normals.push_back(QVector3D(xPos, yPos, zPos));
        }
    }

    bool oddRow = false;
    for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
    {
        if (!oddRow) // even rows: y == 0, y == 2; and so on
        {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
            {
                indices.push_back(y       * (X_SEGMENTS + 1) + x);
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            }
        }

      // 这里奇偶分开添加是有道理的，奇偶分开添加，就能首位相连，自己可以拿笔画一画
        else
        {
            for (int x = X_SEGMENTS; x >= 0; --x)
            {
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                indices.push_back(y       * (X_SEGMENTS + 1) + x);
            }
        }
        oddRow = !oddRow;
    }
    indexCount = indices.size();

    std::vector<float> data;
    for (unsigned int i = 0; i < positions.size(); ++i)
    {
        data.push_back(positions[i].x());
        data.push_back(positions[i].y());
        data.push_back(positions[i].z());
        if (uv.size() > 0)
        {
            data.push_back(uv[i].x());
            data.push_back(uv[i].y());
        }
        if (normals.size() > 0)
        {
            data.push_back(normals[i].x());
            data.push_back(normals[i].y());
            data.push_back(normals[i].z());
        }
    }
#endif
}