
// hi!
/*
what this needs t odo
input -> validate -> translate into motion -> initiate motion
-> monitor -> terminate ok
*/
#include <math.h>
#include <Arduino.h>
#include <BasicLinearAlgebra/BasicLinearAlgebra.h>
#include <Geometry/Geometry.h>
#include  <Kinematics/src/Kinematics.h>
#include <vector3d.cpp>

namespace smart_arm
{
    const static float PI2 = M_PI_2;

    float L[] = {1, 1, 1};
    float X[] = {0, 0, 0};
    
    void p_x_tmp(float (&x)[3], float (&r)[2])
    {
        float theta[] = 
        {
            PI2 - x[0], 
            PI2 - x[0] - x[1], 
            PI2 - x[0] - x[1] - x[2]
        };

        r[0] = L[0] * cos(theta[0]) + L[1] * cos(theta[1]) + L[2] * cos(theta[2]);
        r[1] = L[0] * sin(theta[0]) + L[1] * sin(theta[1]) + L[2] * sin(theta[2]);
    }

    void j_x_tmp(float (&x)[3], float (&r)[2][3])
    {
        float theta[] = 
        {
            x[0], 
            x[0] + x[1], 
            x[0] + x[1] + x[2]
        };

        float p1[] = 
        {
            L[0] * cos(theta[0]), 
            L[1] * cos(theta[1]), 
            L[2] * cos(theta[2])
        };

        float p2[] = 
        {
            -L[0] * sin(theta[0]), 
            -L[1] * sin(theta[1]), 
            -L[2] * sin(theta[2])
        };

        r[0][0] = p1[0] + p1[1] + p1[2];
        r[0][1] = p1[1] + p1[2];
        r[0][2] = p1[2];
        r[1][0] = p2[0] + p2[1] + p2[2];
        r[1][1] = p2[1]+ p2[2];
        r[1][2] = p2[2];
    }
    
    void setup()
    {

    }

    void loop()
    {
        Vector3 a, b, c;
        a = Vector3(1, 3, 5);
        float d = 7;
        b = a * d;
        c = a + b;
    }
}