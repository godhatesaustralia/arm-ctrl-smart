import numpy as np
import math

l = [1.0,1.0,1.0]

pi2 = math.pi/2
cos = math.cos
sin = math.sin

def p(x):
    theta=[pi2-x[0],pi2-x[0]-x[1],pi2-x[0]-x[1]-x[2]]
    return np.array([
        l[0]*cos(theta[0]) + l[1]*cos(theta[1]) + l[2]*cos(theta[2]),
        l[0]*sin(theta[0]) + l[1]*sin(theta[1]) + l[2]*sin(theta[2])
    ])

def j(x):
    theta=[x[0],x[0]+x[1],x[0]+x[1]+x[2]]
    p1=[l[0]*cos(theta[0]),l[1]*cos(theta[1]),l[2]*cos(theta[2])]
    p2=[-l[0]*sin(theta[0]),-l[1]*sin(theta[1]),-l[2]*sin(theta[2])]
    return np.array([
        [p1[0]+p1[1]+p1[2], p1[1]+p1[2], p1[2]],
        [p2[0]+p2[1]+p2[2], p2[1]+p2[2], p2[2]],
    ])

def mp(A):
    return np.linalg.pinv(A)

def improve(cur, target):
    p0 = p(cur)
    jp = mp(j(cur))
    dp = target - p0
    return cur + np.matmul(jp,dp)


x0=np.array([0.2,0.4,0.8]).transpose()
p1=(2,2)
it = x0
print(p(x0))
for i in range(10):
    it = improve(it, p1)
    print(p(it))