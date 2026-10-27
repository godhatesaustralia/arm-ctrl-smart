#include <math.h>
#include <Arduino.h>

namespace smart_arm
{
    /// @brief It's a vector of three doubles. Yay
    struct Vector3D : public Printable 
    {
        double x = 0;
        double y = 0;
        double z = 0; 
        double Length = 0, InvLength = NAN;

        Vector3D() = default;

        Vector3D(float xin, float yin, float zin)
        {
            x = xin;
            y = yin;
            z = zin;
            _setLength();
        }

        std::size_t printTo(Print& p) const override {
            std::size_t s = p.print('[');
            s += p.print(x);
            s += p.print(", ");
            s += p.print(y);
            s += s += p.print(", ");
            s += p.print(z);
            s += p.print(']');
            return s;
        }

        public:Vector3D& operator+(const Vector3D& o) const {
            return Vector3D(x + o.x, y + o.y, z + o.z); 
        }

        Vector3D& operator+=(const Vector3D& o) {
            this->x += o.x;
            this->y += o.y;
            this->z += o.z;
            _setLength();
        }

        Vector3D& operator-(const Vector3D& o) const {
            return Vector3D(x - o.x, y - o.y, z - o.z); 
        }

        Vector3D& operator-=(const Vector3D& o) {
            this->x -= o.x;
            this->y -= o.y;
            this->z -= o.z;
            _setLength();
        }

        Vector3D& operator*(const Vector3D& o) const {
            return Vector3D(x*o.x, y*o.y, z*o.z);
        }

        Vector3D& operator*=(const Vector3D& o) {
            this->x *= o.x;
            this->y *= o.y;
            this->z *= o.z;

            _setLength();
        }

        Vector3D& operator*(const double& d) const {
            return Vector3D(x * d, y * d, z * d);
        }
        
        Vector3D& operator*=(const double& d) {
            this->x *= d;
            this->y *= d;
            this->z *= d;
            _setLength();
        }

        Vector3D& operator/(const double&d) const {
            return Vector3D(x / d, y / d, z / d);
        }

        Vector3D& operator/=(const double& d) {
            this->x /= d;
            this->y /= d;
            this->z /= d;
            _setLength();
        }

        double& Dot(const Vector3D& o) const {
            double r = this->x*o.x + this->y*o.y + this->z*o.z; 
            return r;
        }

        /// @brief Find overall angle between vectors
        /// @param o other vector 
        /// @return Angle between vectors in radians OR NAN idk
        double& AngleBetween(const Vector3D& o) const {
            double r = NAN;
            double d = Dot(o) * this->InvLength * o.InvLength;

            if (r < -1 || r > 1) 
                return r;

            r = acos(d);
            return r;
        }
        
        Vector3D Cross(const Vector3D& o) const {
            return Vector3D(y*o.z - z*o.y, z*o.x - x*o.z, x*o.y - y*o.x); 
        }

        Vector3D& Normalize() {
           this->x *= InvLength;
           this->y *= InvLength;
           this->z *= InvLength;
        
           this->Length = this->InvLength = 1;
        }

        // my things mine all mine
        private:void _setLength()
        {
            Length = sqrt(x*x + y*y + z*z);
            InvLength = 1 / Length;
        }
    };
}