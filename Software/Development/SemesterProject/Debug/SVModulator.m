function y = fcn(u)
% Space Vector Modulation

y                = zeros(3,1);

vsd              = u(1);  % V_alfa
vsq              = u(2);  % V_beta
Vdc              = u(3);  % DC link voltage 

% =========================================================================
% Set the voltage limits

weight           = Vdc/(sqrt(3)*sqrt(vsd*vsd+vsq*vsq));
dlimit           = abs(vsd*weight);
qlimit           = abs(vsq*weight);
if (abs(vsd)>dlimit)
    vsd          = (3*sign(vsd)*dlimit)/(2*Vdc);
else
    vsd          = (3*vsd)/(2*Vdc);
end

if(abs(vsq)>qlimit)
    vsq          = (3*sign(vsq)*qlimit)/(2*Vdc);
else
    vsq          = (3*vsq)/(2*Vdc);
end

duty_a           = 0;
duty_b           = 0;
duty_c           = 0;

% =========================================================================

if ((vsd>=0) && (vsq>=0)) 	
     if (vsq < sqrt(3)*vsd)
         % sector 0
         t1      = 0.5*(vsd-(vsq/sqrt(3)));
         t2      = vsq/sqrt(3);
         temp    = 0.5-t1-t2;
         duty_a  = 1-temp; 
         duty_b  = 1-(temp+2*t1);
         duty_c  = temp;
     else
         % sector 1
         t1      = 0.5*((vsq/sqrt(3))-vsd);
         t2      = 0.5*((vsq/sqrt(3))+vsd);
         temp    = 0.5-t1-t2;
         duty_b  = 1-temp; 
         duty_a  = 1-(temp+2*t1);
         duty_c  = temp;
     end
end

if ((vsd<0) && (vsq>0))
    if (vsq < (sqrt(3)*abs(vsd))) 
        % sector 2
        t1       = (vsq/sqrt(3));
        t2       = 0.5*(abs(vsd)-(vsq/sqrt(3)));
        temp     = 0.5-t1-t2;
        duty_b   = 1-temp; 		
        duty_c   = 1-(temp+2*t1);
        duty_a   = temp;
    else
        % sector 1
        t1       = 0.5*((vsq/sqrt(3))-vsd);
        t2       = 0.5*((vsq/sqrt(3))+vsd);
        temp     = 0.5-t1-t2;
        duty_b   = 1-temp; 	
        duty_a   = 1-(temp+2*t1);
        duty_c   = temp;
    end
end
       
if ((vsd<0) && (vsq<=0)) 	
    if (abs(vsq) <= sqrt(3)*abs(vsd)) 
        % Sector 3
        t1       = (abs(vsq)/sqrt(3));
        t2       = 0.5*(abs(vsd)-(abs(vsq)/sqrt(3)));
        temp     = 0.5-t1-t2;
        duty_c   = 1-temp; 			
        duty_b   = 1-(temp+2*t1);
        duty_a   = temp;
    else
        % Sector 4
        t1       = 0.5*((abs(vsq)/sqrt(3))-vsd);
        t2       = 0.5*((abs(vsq)/sqrt(3))+vsd);
        temp     = 0.5-t1-t2;
        duty_c   = 1-temp; 
        duty_a   = 1-(temp+2*t1);
        duty_b   = temp;
    end
end
   

if ((vsd>=0) && (vsq<0))	
    if(abs(vsq)<=vsd*sqrt(3))
        % Sector 5
        t1       = 0.5*(vsd-(abs(vsq)/sqrt(3)));
        t2       = (abs(vsq)/sqrt(3));
        temp     = 0.5-t1-t2;
        duty_a   = 1-temp; 				
        duty_c   = 1-(temp+2*t1);
        duty_b   = temp;
    else
        % Sector 4
        t1       = 0.5*((abs(vsq)/sqrt(3))-vsd);
        t2       = 0.5*((abs(vsq)/sqrt(3))+vsd);
        temp     = 0.5-t1-t2;
        duty_c   = 1-temp; 
        duty_a   = 1-(temp+2*t1);
        duty_b   = temp;
    end
end

% =========================================================================

y(1) = duty_a;
y(2) = duty_b;
y(3) = duty_c;

% =========================================================================