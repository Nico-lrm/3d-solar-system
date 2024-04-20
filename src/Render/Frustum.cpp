#include "Frustum.hpp"

namespace SPN
{
    Frustum createFrustumFromCamera(const std::unique_ptr<Camera>& camera)
    {
        auto z_near{ camera->getNear() };
        auto z_far{ camera->getFar() / 100 };
        auto aspect{ camera->getAspect() };
        auto fov_y{ camera->getFovY() };
        auto camera_pos{ camera->getPosition() };
        auto camera_right{ camera->getRight() };
        auto camera_up{ camera->getUp() };
        auto camera_orientation{ camera->getOrientation() };

        Frustum frustum;
        const double halfVSide{ z_far * tanf(glm::radians(fov_y)) };
        const double halfHSide{ halfVSide * aspect };
        const glm::dvec3 frontMultFar{ z_far * camera_orientation };

        // On calcule la valeur de chaque face pour voir si nos objets sont présents dans ces faces, si oui ils sont affichés
        frustum.nearFace = { glm::dvec3(0.0) + z_near * camera_orientation, camera_orientation };
        frustum.farFace = { glm::dvec3(0.0) + frontMultFar, -camera_orientation };
        frustum.rightFace = { glm::dvec3(0.0), glm::cross(frontMultFar - camera_right * halfHSide, camera_up) };
        frustum.leftFace = { glm::dvec3(0.0), glm::cross(camera_up,frontMultFar + camera_right * halfHSide) };
        frustum.topFace = { glm::dvec3(0.0), glm::cross(camera_right, frontMultFar - camera_up * halfVSide) };
        frustum.bottomFace = { glm::dvec3(0.0), glm::cross(frontMultFar + camera_up * halfVSide, camera_right) };

        return frustum;
    }

    bool isOnOrForwardPlane(const Plane& plane, const glm::dvec3& center, const double& radius)
	{
		return plane.getSignedDistanceToPlane(center) > -radius;
	}

    bool isOnFrustum(const Frustum& frustum, const glm::vec3& position, const glm::vec3& scale)
    {
        glm::dvec3 center{ position };
        double radius{ scale.x };

        return (isOnOrForwardPlane(frustum.leftFace, center, radius) &&
                isOnOrForwardPlane(frustum.rightFace, center, radius) &&
                isOnOrForwardPlane(frustum.farFace, center, radius) &&
                isOnOrForwardPlane(frustum.nearFace, center, radius) &&
                isOnOrForwardPlane(frustum.topFace, center, radius) &&
                isOnOrForwardPlane(frustum.bottomFace, center, radius));
    }
}