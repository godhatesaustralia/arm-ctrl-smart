#include <cmath>
#include <Arduino.h>
#include <BasicLinearAlgebra/BasicLinearAlgebra.h>
#include <Geometry/Geometry.h>
#include  <Kinematics/src/Kinematics.h>

namespace smart_arm
{
        struct Vector3D {
        double 
            x = 0,
            y = 0, 
            z = 0, 
            Length = 0,
            InvLength = 0;

        Vector3D();

        Vector3D(float xin, float yin, float zin)
        {
            x = xin;
            y = yin;
            z = zin;
            _setLength();
        }

        private:void _setLength()
        {
            Length = sqrt(x*x + y*y + z*z);
            InvLength = 1 / Length;
        }
        
        Vector3D& operator+(const Vector3D& o) const {
            return Vector3D(x + o.x, y + o.y, z + o.z); 
        }

        Vector3D& operator-(const Vector3D& o) const {
            return Vector3D(x - o.x, y - o.y, z - o.z); 
        }

        public:Vector3D& operator*(const double& d) const {
            return Vector3D(x * d, y * d, z * d);
        }
        
        Vector3D& operator*=(const double& d) {
            this->x *= d;
            this->y *= d;
            this->z *= d;
            _setLength();
        }

        Vector3D& operator/=(const double& d) {
            this->x /= d;
            this->y /= d;
            this->z /= d;
            _setLength();
        }

        Vector3D& Dot(const Vector3D& o) const {
            return Vector3D(x * o.x, y * o.y, z * o.z); 
        }
        
        Vector3D Normalize() const {
            return Vector3D(x * InvLength, y * InvLength, z * InvLength);
        }

        Vector3D Cross(const Vector3D& o) const {
            return Vector3D(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x); 
        }
        
    };
}