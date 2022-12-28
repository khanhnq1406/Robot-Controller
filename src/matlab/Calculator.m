syms t1 t2 t3 a1 a2 a3 a4  L1 L2 L3 t4  d1 d2 d3
a1=L1;
a2=0;
a3=L2;
a4=L3;
apha1= 0;
apha2= sym(pi/2);
apha3= 0;
apha4= 0;
d1=d1;
d2=0;
d3=0;
d4=0;
t1=t1;
t2=t2;
t3=t3;
t4=0;
T_01=[cos(t1)           -sin(t1)            0                   a1;
    sin(t1)*cos(apha1) cos(t1)*cos(apha1) -sin(apha1)   -sin(apha1)*d1;
    sin(t1)*sin(apha1) cos(t1)*sin(apha1) cos(apha1)    cos(apha1)*d1;
    0                   0                   0              1]
T_12=[cos(t2)           -sin(t2)            0                   a2;
    sin(t2)*cos(apha2) cos(t2)*cos(apha2) -sin(apha2)   -sin(apha2)*d2;
    sin(t2)*sin(apha2) cos(t2)*sin(apha2) cos(apha2)    cos(apha2)*d2;
    0                   0                   0              1]
T_23=[cos(t3)           -sin(t3)            0                   a3;
    sin(t3)*cos(apha3) cos(t3)*cos(apha3) -sin(apha3)   -sin(apha3)*d3;
    sin(t3)*sin(apha3) cos(t3)*sin(apha3) cos(apha3)    cos(apha3)*d3;
    0                   0                   0              1]
T_34=[cos(t4)           -sin(t4)            0                   a4;
    sin(t4)*cos(apha4) cos(t4)*cos(apha4) -sin(apha4)   -sin(apha4)*d4;
    sin(t4)*sin(apha4) cos(t4)*sin(apha4) cos(apha4)    cos(apha4)*d4;
    0                       0                   0              1]


%%
T_04=T_01*T_12*T_23*T_34
Tx=simplify(T_04(1,4))
Ty=simplify(T_04(2,4))
Tz=simplify(T_04(3,4))
%px=L1 + L3*cos(t2 + t3)*cos(t1) + L2*cos(t1)*cos(t2) + L4*cos(t2 + t3 + t4)*cos(t1);
%py=sin(t1)*(L3*cos(t2 + t3) + L2*cos(t2) + L4*cos(t2 + t3 + t4));
%pz=d1 + L3*sin(t2 + t3) + L2*sin(t2) + L4*sin(t2 + t3 + t4);

%%
syms Px Py Pz
T =     [   cos(t1)*cos(t2)*cos(t3) - cos(t1)*sin(t2)*sin(t3),  - cos(t1)*cos(t2)*sin(t3) - cos(t1)*cos(t3)*sin(t2),    sin(t1),           Px;
            cos(t2)*cos(t3)*sin(t1) - sin(t1)*sin(t2)*sin(t3),  - cos(t2)*sin(t1)*sin(t3) - cos(t3)*sin(t1)*sin(t2),    -cos(t1),          Py;
            cos(t2)*sin(t3) + cos(t3)*sin(t2),                   cos(t2)*cos(t3) - sin(t2)*sin(t3),                         0,             Pz;
                                       0,                                           0,                                       0,             1];


T_01 =[cos(t1),     -sin(t1),   0,   L1;
        sin(t1),    cos(t1),    0,   0;
             0,        0,       1,  d1;
             0,        0,       0,  1];
 
 
T_12 =  [cos(t2),   -sin(t2),    0,      0;
              0,        0,      -1,     -d2;
        sin(t2),    cos(t2),     0,      0;
              0,        0,       0,      1];
 
 
T_23 =  [cos(t3), -sin(t3),     0,      L2;
        sin(t3),  cos(t3),      0,      0;
              0,        0,      1,      d3;
              0,        0,      0,      1];
         
 T_34 =     [1, 0,  0,  L3;
            0,  1,  0,  0;
            0,  0,  1,  0;
            0,  0,  0,  1];
             
T_n=inv(T_01)*T;
T_n1=simplify(T_n(1,4))
T_n2=simplify(T_n(2,4))
T_n3=simplify(T_n(3,4))
T_m=T_12*T_23*T_34;
T_m1=simplify(T_m(1,4))
T_m2=simplify(T_m(2,4))
T_m3=simplify(T_m(3,4))

% In calculating inverse kinematic
syms t23 nx2 ny2 c2 nx ny nz
nx2 = expand((L3*cos(t23)+L2*cos(t2))^2)
ny2 = expand((L3*sin(t23)+L2*sin(t2))^2)
simplify(nx2+ny2)

expand(cos(t2+t3))
expand(sin(t2+t3))

c2 = simplify((nx+(ny-L3*cos(t2)*sin(t3))/(L3*cos(t3)+L2)*sin(t3))/(L3*cos(t3)+L2))