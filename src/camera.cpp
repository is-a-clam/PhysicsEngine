#include "camera.h"


Camera::Camera(): radius(5.0f), pitch(0.0f), yaw(-90.0f), fov(45.0f) {};

Camera &Camera::getInstance()
{
    static Camera instance;
    return instance;
};

void Camera::mouseDragCallback(double xpos, double ypos)
{
    if (!dragging)
    {
        lastX = xpos;
        lastY = ypos;
        dragging = true;
    }

    yaw += (xpos - lastX) * sensitivity;
    pitch += (lastY - ypos) * sensitivity;
    pitch = std::min(89.0f, std::max(-89.0f, pitch));

    lastX = xpos;
    lastY = ypos;
}

void Camera::scrollCallback(double xoffset, double yoffset)
{
    fov -= (float) yoffset;
    fov = std::min(45.0f, std::max(1.0f, fov));
}

void Camera::framebufferCallback(int width, int height)
{
    aspectRatio = (float) width / (float) height;
}

glm::vec3 Camera::getPosition()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    return -(radius * direction);
}

glm::mat4 Camera::getViewTransform()
{
    return glm::lookAt(getPosition(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::getProjectionTransform()
{
    return glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
}