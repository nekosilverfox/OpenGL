#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;


in VS_OUT {
    vec3 g_axis_fragPos;
} gs_in[];  // 注意，这里是对于图元来说的。也就是三角形的各个点



out vec3 res_g_axis_normal;
out vec3 res_g_axis_fragPos;



uniform float time;
uniform float del_h;  // 高度偏移量
uniform float del_b;  // 底部圆心偏移量

uniform mat4 mat_model;
uniform mat4 mat_view;
uniform mat4 mat_projection;

vec4 explode(vec4 position, vec3 normal)
{
    float magnitude = 100.0;
    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude;
    return position + vec4(direction, 0.0);
//    return vec4(position.x * del_b,
//                position.y * del_h,
//                position.z * del_b,
//                position.w);
}


vec4 changePos(vec4 position)
{
    return vec4(position.x,
                position.y,
                position.z,
                position.w);
}

vec3 GetNormal()
{
        vec3 a = changePos(gl_in[0].gl_Position).xyz - changePos(gl_in[1].gl_Position).xyz;
        vec3 b = changePos(gl_in[2].gl_Position).xyz - changePos(gl_in[1].gl_Position).xyz;
        return cross(a, b);

//    int is_frout = -1;
////    if (gl_VertexID % 2 == 0)
////    {
////        is_frout = -1;
////    }
//    return normalize(
//              cross(changePos(gl_in[0].gl_Position).xyz, changePos(gl_in[1].gl_Position).xyz)
//            + cross(changePos(gl_in[1].gl_Position).xyz, changePos(gl_in[2].gl_Position).xyz)
//            + cross(changePos(gl_in[2].gl_Position).xyz, changePos(gl_in[0].gl_Position).xyz)
//            ) * is_frout;

}


void main() {
    vec3 new_normal = GetNormal();
    vec4 new_pos;


    new_pos = gl_in[0].gl_Position;
    gl_Position = mat_projection * mat_view * mat_model * new_pos;
    res_g_axis_normal = mat3(transpose(inverse(mat_model))) * new_normal;
    res_g_axis_fragPos  = vec3(mat_model * new_pos);
    EmitVertex();

    new_pos = gl_in[1].gl_Position;
    gl_Position = mat_projection * mat_view * mat_model * new_pos;
    res_g_axis_normal = mat3(transpose(inverse(mat_model))) * new_normal;
    res_g_axis_fragPos  = vec3(mat_model * new_pos);
    EmitVertex();

    new_pos = gl_in[2].gl_Position;
    gl_Position = mat_projection * mat_view * mat_model * new_pos;
    res_g_axis_normal = mat3(transpose(inverse(mat_model))) * new_normal;
    res_g_axis_fragPos  = vec3(mat_model * new_pos);
    EmitVertex();

    EndPrimitive();
}
