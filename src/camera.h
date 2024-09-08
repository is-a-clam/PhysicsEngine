#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <algorithm>

class Camera
{
private:
    // Camera Values
    float radius, pitch, yaw;
    
    // Viewport Values
    float fov, aspectRatio;

    // Mouse Values
    const float sensitivity = 0.3f;
    float lastX, lastY;

    Camera();
public:
    bool dragging;

    static Camera &getInstance();
    void mouseDragCallback(double xpos, double ypos);
    void scrollCallback(double xoffset, double yoffset);
    void framebufferCallback(int width, int height);
    glm::vec3 getPosition();
    glm::mat4 getViewTransform();
    glm::mat4 getProjectionTransform();

    Camera(Camera const&) = delete;
    void operator=(Camera const&) = delete;
};

#endif