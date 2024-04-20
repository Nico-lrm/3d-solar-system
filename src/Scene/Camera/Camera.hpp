#ifndef CAMERA_HPP
#define CAMERA_HPP 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/compatibility.hpp>

namespace SPN
{
    // Direction pour le déplacement de la caméra
    enum class CameraDirection {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    // Valeur par défaut pour la caméra
    constexpr float YAW = -90.f;
    constexpr float PITCH = 0.0f;
    constexpr float SPEED = 1.f;
    constexpr float SENSITIVITY = 0.1f;
    constexpr float ZOOM = 45.0f;

    class Camera
    {
        protected:
            // Vecteurs
            glm::dvec3 _position = glm::vec3(0.0, 0.0, 0.0);
            glm::dvec3 _target_position = glm::vec3(0.0, 0.0, 0.0);
            glm::dvec3 _prev_position = glm::vec3(0.0, 0.0, 0.0);

            glm::dvec3 _orientation = glm::vec3(0.0f, 0.0, -1.0);
            glm::dvec3 _target_orientation = glm::vec3(0.0, 0.0, -1.0);
            glm::dvec3 _up = glm::vec3(0.0, 0.0, 0.0);
            glm::dvec3 _right = glm::vec3(0.0, 0.0, 0.0);
            glm::dvec3 _world_up = glm::vec3(0.0, 1.0, 0.0);

            // Angles d'Euler
            float _yaw;
            float _pitch;

            // Options
            float _movement_speed = SPEED;
            float _sensitivity = SENSITIVITY;
            float _zoom = ZOOM;

            // Taille de la fenêtre (pour la caméra)
            unsigned int _width;
            unsigned int _height;

            // Plan
            double _near = .00001;
            double _far = 46000.0;

            double _duration = 5.0;
            double _time = 0.0;

            // Mise a jour du _target_orientation
            void updateVector()
            {
                // On modifie l'orientation de la caméra
                glm::dvec3 newOrientation;
                newOrientation.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
                newOrientation.y = sin(glm::radians(_pitch));
                newOrientation.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
                _target_orientation = glm::normalize(newOrientation);

                _right = glm::normalize(glm::cross(_orientation, _world_up));
                _up = glm::normalize(glm::cross(_right, _orientation));
            };

        public:
            Camera(glm::vec3 position = glm::vec3(0.0, 0.0, 0.0), glm::vec3 worldup = glm::vec3(0.0, 1.0, 0.0), float yaw = YAW, float pitch = PITCH) : _position(position), _world_up(worldup), _yaw(yaw), _pitch(pitch)
            {
                _target_position = _position;
                _target_position.z -= 2.;
                updateVector();
            };

            virtual ~Camera() = default;

            // Déplacement
            virtual void Move(const CameraDirection& cam_dir, const float& deltatime) = 0;
            virtual void Look(float xoffset, float yoffset) = 0;
            virtual void Update(const float& deltatime) = 0;

            // Getter matrices & position
            glm::dmat4 getViewMatrix()
            {
                glm::dmat4 view = glm::dmat4(1.);
                view = glm::lookAt(glm::dvec3(0.0), glm::dvec3(0.0) + _orientation, _up);
                return view;
            }

            glm::dmat4 getProjMatrix()
            {
                glm::dmat4 projection{ glm::dmat4(1.0) };
                projection = glm::perspective(glm::radians(static_cast<double>(_zoom)), static_cast<double>(_width) / _height, _near, _far);
                return projection;
            }

            glm::dmat4 getViewProjMatrix()
            {
                return getProjMatrix() * getViewMatrix();
            }

            glm::dvec3 getPosition()
            {
                return this->_position;
            }

            glm::dvec3 getRight()
            {
                return this->_right;
            }

            glm::dvec3 getUp()
            {
                return this->_up;
            }

            glm::dvec3 getOrientation()
            {
                return this->_orientation;
            }

            double getNear()
            {
                return this->_near;
            }

            double getFar()
            {
                return this->_far;
            }

            double getAspect()
            {
                return static_cast<double>(_width/_height);
            }

            double getFovY()
            {
                return this->_zoom;
            }

            void MoveCamera(const glm::vec3& new_pos)
            {
                this->_target_position = new_pos;
            }
    };
};

#endif