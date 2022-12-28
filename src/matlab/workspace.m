
clc;
clear all;
close all;
L1 = 114.55; L2 = 162; L3 = 130; d1 = 164.54; d2 = 69.5; d3 = 16;
% tt=0;
% for the1=0:0.5:10
%     for the2=0:0.5:10
%         for the3=0:0.5:10
%             if(the1+the2+the3)==0 
%             tt=tt+1
%             x= L1 - L3 * (cosd(the1) * sind(the2) * sind(the3) - cosd(the1)*cosd(the2)*cosd(the3)) + L2 * cosd(the1)*cosd(the2);
%             y= sind(the1)*(L3*cosd(the2+the3)+L2*cosd(the2));
%             z= d1 + L3*sind(the2 + the3) + L2*sind(the2);
%                 emtry(:,tt) =[x;y;z];
% 
%             end
%         end
%     end
% end
the1 = 0:0.5:180;
the2 = -30:0.5:90;
the3 = -20:0.5:120;
x= L1 - L3 .* (cosd(the1) .* sind(the2) .* sind(the3) - cosd(the1).*cosd(the2).*cosd(the3)) + L2 .* cosd(the1).*cosd(the2);
y= sind(the1).*(L3*cosd(the2+the3)+L2.*cosd(the2));
z= d1 + L3.*sind(the2 + the3) + L2.*sind(the2);
plot3(x,y,z,'o');
% figure(1);



% t1=linspace(0,90);
% t2=linspace(-10,50);
% t3=linspace(0,120);
% [the1,the2,the3]=ndgrid(t1,t2,t3); 
% x= L1 - L3 .* (cosd(the1) .* sind(the2) .* sind(the3) - cosd(the1).*cosd(the2.*cosd(the3))) + L2 .* cosd(the1).*cosd(the2);
% y= sind(the1).*(L3.*cosd(the2+the3)+L2.*cosd(the2));
% z=d1 + L3.*sind(the2 + the3) + L2.*sind(the2);
% plot3(x(:),y(:),z(:),'.')