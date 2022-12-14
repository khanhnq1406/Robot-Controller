clear;
close all;

%syms L1 L2 L3 the1 the2 the3 d1 ;
L1=1;
L2=1;
L3=1;
% bo nghiem 1
%  the1=   0.7854;
%  the2=   1.3546;
%  the3=   -1.3314;
% % bo nghiem 2
%  the1=   0.7854;
%  the2=   0.0233;
%  the3=   1.3314;
% % bo nghiem 3
%  the1=   -2.3562;
%  the2=    2.9063;
%  the3=    -0.6387;
% % bo nghiem 4
%  the1=   -2.3562;
%  the2=    2.2676;
%  the3=    0.6387;

the1 = -2.6779; the2 = 2.6815; the3 = 0.4042;
DH = [0  0    0 the1;
      L1 pi/2 0 the2;
      L2 0    0 the3];
T_0_i = eye(4);


for  i=1:3
    the = DH(i,4); d = DH(i,3); anp = DH(i,2);  a = DH(i,1);
    T_i_1_i = [cos(the)            -sin(the)                   0           a;
              (sin(the)*cos(anp))  cos(the)*cos(anp)           -sin(anp)   -sin(anp)*d;
              (sin(the)*sin(anp))  cos(the)*sin(anp)           cos(anp)    cos(anp)*d;
              0                    0                           0           1];
    T_0_i = (T_0_i *  T_i_1_i);
    T_0_i_s(:,:,i) = T_0_i;
end  
T_i_1_i;
P_2_EE = [L3; 0;0;1];
P_0_EE = (T_0_i*P_2_EE)
% simplify(P_0_EE)
% plot robot configuration
P_0_B = [0; 0; -1.5];
plot3([P_0_B(1),0], [P_0_B(2),0], [P_0_B(3),-0.5], '-x', 'linewidth', 2);
hold on;
plot3([0,T_0_i_s(1,4,2)],[0,T_0_i_s(2,4,2)],[-0.5,T_0_i_s(3,4,2)], '-rO', 'linewidth', 2);
hold on;
plot3([T_0_i_s(1,4,2),T_0_i_s(1,4,3)],[T_0_i_s(2,4,2),T_0_i_s(2,4,3)],[T_0_i_s(3,4,2),T_0_i_s(3,4,3)], '-bO', 'linewidth', 2);
hold on;
plot3([T_0_i_s(1,4,3),P_0_EE(1)],[T_0_i_s(2,4,3),P_0_EE(2)],[T_0_i_s(3,4,3),P_0_EE(3)], '-mO', 'linewidth', 2);
hold on;
xlabel('x'); ylabel('y'); zlabel('z');
xlim([-5 5]); ylim([-5 5]); zlim([-5 5]);
