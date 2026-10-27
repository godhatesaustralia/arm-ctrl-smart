
// hi!
/*
what this needs t odo
input -> validate -> translate into motion -> initiate motion
-> monitor -> terminate ok
*/
#include <cmath>
#include <Arduino.h>
#include <BasicLinearAlgebra/BasicLinearAlgebra.h>
#include <Geometry/Geometry.h>
#include  <Kinematics/src/Kinematics.h>
#include <vector3d.cpp>

using namespace std;

namespace smart_arm
{
    void setup()
    {

    }

    void loop()
    {
        Vector3D a, b, c;
        a = Vector3D(1, 3, 5);
        double d = 7;
        b = a * d;
        c = a + b;
    }
}