#include <cstddef>
#include <math.h>
#include <Arduino.h>

namespace smart_arm
{
    /// @brief It's a vector of three floats. Yay
    struct Vector3 : public Printable 
    {
        float x = 0;
        float y = 0;
        float z = 0; 
        float Length = 0, InvLength = NAN;

        Vector3() = default;

        Vector3(float xin, float yin, float zin)
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

        public:Vector3& operator+(const Vector3& o) const {
            return Vector3(x + o.x, y + o.y, z + o.z); 
        }

        Vector3& operator+=(const Vector3& o) {
            this->x += o.x;
            this->y += o.y;
            this->z += o.z;
            _setLength();
        }

        Vector3& operator-(const Vector3& o) const {
            return Vector3(x - o.x, y - o.y, z - o.z); 
        }

        Vector3& operator-=(const Vector3& o) {
            this->x -= o.x;
            this->y -= o.y;
            this->z -= o.z;
            _setLength();
        }

        Vector3& operator*(const Vector3& o) const {
            return Vector3(x*o.x, y*o.y, z*o.z);
        }

        Vector3& operator*=(const Vector3& o) {
            this->x *= o.x;
            this->y *= o.y;
            this->z *= o.z;

            _setLength();
        }

        Vector3& operator*(const float& f) const {
            return Vector3(x * f, y * f, z * f);
        }
        
        Vector3& operator*=(const float& f) {
            this->x *= f;
            this->y *= f;
            this->z *= f;
            _setLength();
        }

        Vector3& operator/(const float& f) const {
            return Vector3(x / f, y / f, z / f);
        }

        Vector3& operator/=(const float& f) {
            this->x /= f;
            this->y /= f;
            this->z /= f;
            _setLength();
        }

        float& Dot(const Vector3& o) const {
            float r = this->x*o.x + this->y*o.y + this->z*o.z; 
            return r;
        }

        /// @brief Find overall angle between vectors
        /// @param o other vector 
        /// @return Angle between vectors in radians OR NAN idk
        float& AngleBetween(const Vector3& o) const {
            float r = NAN;
            float f = Dot(o) * this->InvLength * o.InvLength;

            if (r < -1 || r > 1) 
                return r;

            r = acos(f);
            return r;
        }
        
        Vector3& Cross(const Vector3& o) const {
            return Vector3(y*o.z - z*o.y, z*o.x - x*o.z, x*o.y - y*o.x); 
        }

        Vector3& Normalize() {
           this->x *= InvLength;
           this->y *= InvLength;
           this->z *= InvLength;
        
           this->Length = this->InvLength = 1;
        }

        // internals

        private:void _setLength()
        {
            Length = sqrt(x*x + y*y + z*z);
            InvLength = Length != 0 ? 1 / Length : 0;
            // you will NOT take my syntactic sugar from meeeeeeeee
        }
    };

    void p_x(float (&x)[3], float (&t)[3])
    {
        float sub = x[0];
        for (int i = 0; i < 3; i++)
        {
            t[i] = M_PI_2 - sub;
            if (i < 2) sub -= x[i + 1];
        }
    }
}