#version 330 core

layout (location = 0) in vec3 oc_position;
layout (location = 1) in vec3 oc_normal;

out vec3 wc_position;
out vec3 wc_normal;

uniform mat4 m_transform;
uniform mat3 m_normal_transform;
uniform mat4 mvp_transform;

void main()
{
   wc_position = (m_transform * vec4(oc_position, 1.0)).xyz;
   wc_normal = normalize(m_normal_transform * oc_normal);
   gl_Position = mvp_transform * vec4(oc_position, 1.0);
}