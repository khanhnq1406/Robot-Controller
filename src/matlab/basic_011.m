function out = basic_011(a1,b1,d1)
    anp=atan2(b1,a1);
    theta(1)=atan2(sqrt(1-(d1*d1/((a1*a1)+(b1*b1)))),d1/(sqrt((a1*a1)+(b1*b1))))+anp;
    theta(2)=atan2(-sqrt(1-(d1*d1/((a1*a1)+(b1*b1)))),d1/(sqrt((a1*a1)+(b1*b1))))+anp;
    out=theta;
    
    
end