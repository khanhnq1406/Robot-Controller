#include <cmath>
void forwardKinematic() {
  float theta1R, theta2R, theta3R;
  theta1R = theta1 * 3.14159/180;
  theta2R = theta2 * 3.14159/180;
  theta3R = theta3 * 3.14159/180;
  Px = L1 - L3 * (cos(theta1R) * sin(theta2R) * sin(theta3R) - cos(theta1R)*cos(theta2R*cos(theta3R))) + L2 * cos(theta1R)*cos(theta2R);
  Py = sin(theta1R)*(L3*cos(theta2R+theta3R)+L2*cos(theta2R));
  Pz = d1 + L3*sin(theta2R + theta3R) + L2*sin(theta2R);
  PxUpdate = Px;
  PyUpdate = Py;
  PzUpdate = Pz;

}

void inverseKinematic() {
  theta1 = atan2(Py, Px - L1) * (180 / 3.141592);
  float nx = Px*cos(theta1*3.14159/180) + Py * sin(theta1*3.14159/180) - L1 * cos(theta1*3.14159/180);
  float ny = Pz - d1;
  float c3 = (pow(nx, 2) + pow(ny, 2) - pow(L3, 2) - pow(L2, 2)) / (2 * L3 * L2);
  float s3 = sqrt(1 - pow(c3, 2));
  theta3 = atan2(s3, c3) * (180 / 3.141592);
  float c2 =  (nx*(L3*c3+L2)+L3*s3*ny)/(pow((L3*c3+L2),2)+pow(L3,2)*pow(s3,2));
  float s2 = (ny*(L3*c3+L2)-L3*s3*nx)/(pow((L3*c3+L2),2)+pow(L3,2)*pow(s3,2));
  theta2 = atan2(s2,c2) * (180 / 3.141592);
  theta1Update = theta1;
  theta2Update = theta2;
  theta3Update = theta3;

}