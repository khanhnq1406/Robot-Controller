clc; 
clear all;
% TIM THETA1
l1=1;l2=1;d1=1;l3=1;
x0=0.8; y0=0.4; z0=0.5;
the1= basic_011(y0,-x0,0)
% TIM THETA2_1
a2_1=2*l2*(x0*cos(the1(1))+y0*sin(the1(1))-d1); 
b2_1=2*z0*l2;
d2_1=(x0*cos(the1(1))+y0*sin(the1(1))-d1)^2 + l2^2 -l3^2 + z0^2;
the2_1=basic_011(a2_1,b2_1,d2_1)
% TIM THETA2_2
a2_2=2*l2*(x0*cos(the1(2))+y0*sin(the1(2))-d1); 
b2_2=2*z0*l2;
d2_2=(x0*cos(the1(2))+y0*sin(the1(2))-d1)^2 + l2^2 -l3^2 + z0^2;
the2_2=basic_011(a2_2,b2_2,d2_2);
% TIM THETA3
the3_1=atan2((z0-l2*sin(the2_1(1))),(x0*cos(the1(1))+y0*sin(the1(1))-d1-l2*cos(the2_1(1)))) - the2_1(1);
the3_2=atan2((z0-l2*sin(the2_1(2))),(x0*cos(the1(1))+y0*sin(the1(1))-d1-l2*cos(the2_1(2)))) - the2_1(2);
the3_3=atan2((z0-l2*sin(the2_2(1))),(x0*cos(the1(2))+y0*sin(the1(2))-d1-l2*cos(the2_2(1)))) - the2_2(1);
the3_4=atan2((z0-l2*sin(the2_2(2))),(x0*cos(the1(2))+y0*sin(the1(2))-d1-l2*cos(the2_2(2)))) - the2_2(2);
% %%%%%%%%%%%%%%%
theta=[ the1(1) the2_1(1) the3_1;
        the1(1) the2_1(2) the3_2;
        the1(2) the2_2(1) the3_3;
        the1(2) the2_2(2) the3_4]
