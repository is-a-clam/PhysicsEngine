#version 330 core

const vec3 light_pos = vec3(10.0, 10.0, 10.0);
const vec3 light_color = vec3(1.0, 1.0, 1.0);
const vec3 object_color = vec3(0.6, 0.3, 0.7);

const float ambient_const = 0.3;
const float diffuse_const = 1.0;

in vec3 wc_position;
in vec3 wc_normal;

out vec4 color;

uniform vec3 wc_camera_position;

void main()
{
   vec3 to_light = normalize(light_pos - wc_position);
   vec3 to_camera = normalize(wc_camera_position - wc_position);

   vec3 ambient = object_color * ambient_const * light_color;
   vec3 diffuse = object_color * diffuse_const * light_color * max(0.0, dot(wc_normal, to_light));
   vec3 illumination = ambient + diffuse;

   color = vec4(illumination, 1.0);
}