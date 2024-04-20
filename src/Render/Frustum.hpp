#ifndef FRUSTUM_HPP
#define FRUSTUM_HPP
#pragma once

#include <glm/glm.hpp>
#include <memory>
#include "../Scene/Camera/Camera.hpp"

namespace SPN
{
    /**
     * @brief Structure représentant une face, utilisé pour calculer le frustum de la caméra (partie visible)
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    struct Plane
    {
        glm::dvec3 normal{ 0.f, 1.f, 0.f };
        double distance{ 0.f };

        Plane() = default;
        Plane(const glm::dvec3& p1, const glm::dvec3& norm) : normal(glm::normalize(norm)), distance(glm::dot(normal, p1))
        {}

        float getSignedDistanceToPlane(const glm::dvec3& point) const
        {
            return static_cast<float>(glm::dot(normal, point) - distance);
        }
    };

    /**
     * @brief Structure représentant le frustum de la caméra
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    struct Frustum
    {
        Plane topFace;
        Plane bottomFace;
        Plane rightFace;
        Plane leftFace;
        Plane farFace;
        Plane nearFace;
    };

    Frustum createFrustumFromCamera(const std::unique_ptr<Camera>& camera);
    bool isOnOrForwardPlane(const Plane& plane, const glm::dvec3& center, const double& radius);
    bool isOnFrustum(const Frustum& frustum, const glm::vec3& position, const glm::vec3& scale);
}


#endif