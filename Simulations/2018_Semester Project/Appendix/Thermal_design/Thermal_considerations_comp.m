%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% * Thermal considerations for inverter design
% * Project Go-Kart
% * Description: 1
%       This script calculates the Mosfet losses in the inverter.
%       The antiparallel diode conduction losses are neglected
%       It is possible to change the Mosfet parameters, and the number of
%       devices in parallel
%
% * Calculations are based on:
%       Application Note, V 1. 1 , July 2006Infi
%       MOSFET Power Losses - Calculation Using the DataSheet Parameters 
%       by Dr. Du�an Graovac, Marco P�rschel, Andreas Kiep
%       Infinion, Automotive power 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
clc, clear, close all
format shortEng
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                           Script input parameters
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Inverter input parameters
    VDC   = 38;
    I_rms = 190;%150%89.8;%175;%89.8;%%%263;%251
    I_pk  = 210;%165%92.4;%180;%92.4;%%%371;%355.75;92.4;
    PF    = 0.76;
    phi   = acos(PF);
    fs    = 10000;

% Mosfet Parameters
    n_parallel    = 2;              % Select number of Fets in parallel
    Use_Fets_xlsx = 1;
    
    if Use_Fets_xlsx == 0
        Mosfet_name= ['AUIRFS3006-7P']
        R_DS_ON    = 1.5*1.5E-3;    %Corrected for current and temperatur
        tr         = 61E-9;
        tf         = 69E-9;
        trr        = 48E-9;
        Qg         = 200E-9;        %Coloumb
        Qrr        = 62E-9;
        R_thJC     = 0.4;
        V_plateau  = 3.8;           %See graph or datasheet table
        R_G        = 2.1;
        Crss_RI    = 3000E-12;
        Crss_VDC   = 700E-12;
        
        n_inputs = 1
    else
        file = 'Fets.xlsx';
        disp(['Using data from ',file])
        
        % Determine number of inputs
        [num,txt] = xlsread(file,1,'1:1');
        n_inputs = length(txt)-3;
        xlRange = [char(64+3+1),'1:',char(64+3+n_inputs),'13']; %Set range
        
        % Read in data
        [num,txt]  = xlsread(file,1,xlRange);
        Mosfet_name= txt;
        R_DS_ON    = num(1,:).*1E-3;
        tr         = num(2,:).*1E-9;
        tf         = num(3,:).*1E-9;
        trr        = num(4,:).*1E-9;
        Qg         = num(5,:).*1E-9;         %Coloumb
        Qrr        = num(6,:).*1E-9;
        R_thJC     = num(7,:);
        V_plateau  = num(8,:);               %See graph or datasheet table
        R_G        = num(9,:);
        Crss_RI    = num(10,:).*1E-12;
        Crss_VDC   = num(11,:).*1E-12;
        Price      = num(12,:);
    end

%for n_parallel = 1:4
    
% Gate driver
    V_dr.on    = 15;
    V_dr.off   = -8.7;
    I_G_pk     = (Qg./min([tr;tf]));
    I_dr_pk    = I_G_pk*n_parallel;
    R_G_ext    = 10;%V_dr.on./(I_G_pk);
    
    R_G_tot    = R_G+R_G_ext;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                              Calculations
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Conduction losses 
    P.con_device_max  =  R_DS_ON*(I_pk/n_parallel)^2;
    P.con_device_avg  = (R_DS_ON*(I_rms/n_parallel)^2);
        %Dividing by 2 as the average power conduction loss is per leg!
        %As the two switches in the leg are on half the time during a cycle
    P.con_Total       = P.con_device_avg*n_parallel*6;
%    Conduction_losses = struct2dataset(P); %Display nicely in Cmd Window

% Switching losses
    %2.2.1 Switch-on transient
        I_Don  = I_pk/n_parallel;   %Assuming peak
        I_Doff = I_pk/n_parallel;   %Assuming peak 
        I_Gon  = (V_dr.on-V_plateau)./R_G_tot;

        C_GD1  = Crss_VDC;   %Off state
        C_GD2  = Crss_RI;    %On state

        tfu1   = (VDC-R_DS_ON*I_Don).*C_GD1./I_Gon;
        tfu2   = (VDC-R_DS_ON*I_Don).*C_GD2./I_Gon;
        tfu    = (tfu1+tfu2)/2;
    
    %2.2.2 Switch-off transient
        I_Goff = (V_dr.off-V_plateau)./R_G_tot;
        
        tru1   = (VDC-R_DS_ON*I_Don).*C_GD1./I_Goff;
        tru2   = (VDC-R_DS_ON*I_Don).*C_GD2./I_Goff;
        tru    = (tru1+tru2)/2;
    
    %2.2.3 Switching energies and losses
    %Mosfet turn on
        E.onM    = VDC*I_Don*(tr+tfu)./2+Qrr*VDC;
        IFrrpeak = 2*Qrr/trr; %Reverse recovery current peak
    
    %Diode turn on, approx of worst case
        E.onD    = 1/4*Qrr*VDC;

    %Mosfet switch off
        E.offM   = VDC*I_Doff*(tru+tf)/2;
    
        P.sw_Mosfet   = (E.onM+E.offM)*fs;
        P.sw_DiodeRR  =  E.onD*fs;
    
        P.sw_Device   = P.sw_Mosfet+P.sw_DiodeRR;
    
    %Gate drive losses (THIS IS OUR OWN DERIVATION)
        P.dr_Qg = 1/2*Qg.*(V_dr.on-V_dr.off)*2*n_parallel;
        P.dr_Rg = P.dr_Qg;
        P.dr_Total = (P.dr_Qg + P.dr_Rg)*fs*6;
    
    P.sw_Total  = P.sw_Device*n_parallel*6;
    P.Total     = P.sw_Total+P.con_Total+P.dr_Total;
    
    %P_SW = VDC*(I_Don*(tr+tf)/2+Qrr+1/4*Qrr+I_Doff*(tr+tf/2))*fs
    %table(P_con_max,P_con_avg,P_SW)
%X(n_parallel) = P;
%end
% figure
% title('Total losses vs parallel devices')
% subplot(1,2,1)
% y =   [X.dr_Total;...
%        X.sw_Total;...
%        X.con_Total];
%     bar(y','stacked')
%     legend('Driver','Switching','Conduction')
%     title('Total losses vs parallel devices')
%     ylabel('Total power loss [W]')
%     xlabel('n devices in parallel')
% subplot(1,2,2)
%     bar(y');%,'stacked')
%     legend('Driver','Switching','Conduction')
%     title('Total losses vs parallel devices')
%     ylabel('Total power loss [W]')
%     xlabel('n devices in parallel')
%     set(gca,'yscale','log')
P

% Thermal management
    K.cu  = 394;    %W/(m*K)
    K.sol = 50;     %W/(m*K)
    K.ins = 3;      %W/(m*K)
    K.Al  = 237;    %W/(m*K)
    K.TP = 100;     %W/(m*K)
    t.cu  = 35E-6;  %m
    t.sol = 500E-6;  %m
    t.ins = 100E-6;  %m
    t.Al  = 1.5E-3;   %m
    t.TP  = 500E-6;   %m
    A     = 10E-3*12E-3;    %m^2
         
    Tsink   = 50;
    dTj     = (P.con_device_max+P.sw_Device).*R_thJC;
    dTsol   = (P.con_device_max+P.sw_Device).*t.sol/(A*K.sol);
    dTcu    = (P.con_device_max+P.sw_Device).*t.cu/(A*K.cu);
    dTins   = (P.con_device_max +P.sw_Device).*t.ins/(A*K.ins);
    dTAl    = (P.con_device_max+P.sw_Device).*t.Al/(A*K.Al);
    dTTP    = (P.con_device_max+P.sw_Device).*t.TP/(A*K.TP);
    TJ = Tsink+dTAl+dTins+dTcu+dTsol+dTj;
    table(dTj,dTsol,dTcu,dTins,dTAl,Tsink,TJ)

    %Thermal resistance for the heatsink selection of IPOT012N08N
    Tj = 100;
    Ta = 25;
    R_thJC = 0.4;
    R_thCS = t.sol/(A*K.sol);
    R_thSC = t.cu/(A*K.cu);
    R_thCI = t.ins/(A*K.ins);
    R_thIA = t.Al/(A*K.Al);
    R_thAP = t.TP/(A*K.TP);
    Ploss = 9.1546;                  %where did this number come from????
    Rthsa = (((Tj-Ta)/Ploss)-R_thJC-R_thCS-R_thSC-R_thCI-R_thIA-R_thAP);
  %Since we have 12 mosfet in the Inverter:
  Heatsink =  Rthsa/12


normal_bar_plots = 1;
if(normal_bar_plots ==1)
plot_row = 1;
plot_col = 2;
    
subplot(plot_row,plot_col,1)
y_values = [P.con_Total;P.sw_Total;P.dr_Total];
bar(y_values','stacked')
title('Inverter power loss')
ylabel('Power [W]')
set(gca,'xticklabel',Mosfet_name,'XTickLabelRotation',20,'TickDir','out')
%set(gca,'yscale','log')
legend('Conduction','Switching','Driver')
legend('Location','eastoutside');
for b = 1:length(P.Total)
    text(b,P.Total(b)+2,['\SigmaP=',sprintf('%0.0f',P.Total(b)),' W'],...
        'VerticalAlignment','bottom','HorizontalAlignment','center')
end

subplot(plot_row,plot_col,2)
y_values = [Tsink*ones(1,length(Mosfet_name));dTAl;dTins;dTcu;dTsol;dTj];
bar(y_values','stacked')
title('Layer structure temperature (Assuming T_{sink}=50℃)')
ylabel('Temperature [℃]')
set(gca,'xticklabel',Mosfet_name,'XTickLabelRotation',20,'TickDir','out')
y_lim = ylim;
ylim([45 y_lim(2)+15])
%set(gca,'yscale','log')
legend('Heat sink','Aluminium','Insulator','Copper','Solder','Mosfet')
legend('Location','eastoutside');
for b = 1:length(TJ)
    text(b,TJ(b)+2,['T_J=',sprintf('%0.0f',TJ(b)),'℃'],...
        'VerticalAlignment','bottom','HorizontalAlignment','center')
end

% subplot(plot_row,plot_col,3)
% y_values = [Price*6*n_parallel];
% bar(y_values')
% title('Total device cost')
% ylabel('Cost [DKK]')
% set(gca,'xticklabel',Mosfet_name,'XTickLabelRotation',20,'TickDir','out')
% y_lim = ylim;
% ylim([0 y_lim(2)+15])
% %set(gca,'yscale','log')
% legend('Cost')
% legend('Location','eastoutside');
% for b = 1:length(TJ)
%     text(b,y_values(b)+2,[sprintf('%0.0f',y_values(b)),'kr'],...
%         'VerticalAlignment','bottom','HorizontalAlignment','center')
% end

else

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

y_lim = [0 n_inputs+1.5];

subplot(1,2,1)
y_values = [P.con_Total;P.sw_Total;P.dr_Total];
barh(y_values','stacked')
title('Inverter power loss')
xlabel('Power [W]')
set(gca,'yticklabel',Mosfet_name,'TickDir','out','YDir','reverse')
x_lim = xlim;
xlim([0 x_lim(2)*1.30])
%set(gca,'yscale','log')
ylim(y_lim)

legend('Conduction','Switching','Driver')
legend('Location','best','Orientation','horizontal');
for b = 1:length(P.Total)
    text(P.Total(b) + (max(x_lim)-min(x_lim))*0.03,b,...
        ['\SigmaP=',sprintf('%0.0f',P.Total(b)),' W'],...
        'VerticalAlignment','middle','HorizontalAlignment','left')
end

subplot(1,2,2)

if ismatrix(Mosfet_name)
    n = length(Mosfet_name);
else
    n = 1;
end

y_values = [Tsink*ones(1,n);dTAl;dTins;dTcu;dTsol;dTj];
barh(y_values','stacked')
title('Layer temperature')
xlabel('Temperature [�C]')
set(gca,'yticklabel',Mosfet_name,'TickDir','out','YDir','reverse')
x_lim = xlim;
xlim([45 x_lim(2)+(x_lim(2)-45)*0.30])
ylim(y_lim)
%set(gca,'yscale','log')
legend('Heat sink','Aluminium','Insulator','Copper','Solder','Mosfet')
a = legend('Location','best','Orientation','horizontal');
for b = 1:length(TJ)
    text(TJ(b)+(max(x_lim)-min(x_lim))*0.03,b,...
        ['T_J=',sprintf('%0.0f',TJ(b)),'�C'],...
        'VerticalAlignment','middle','HorizontalAlignment','left')
end


% subplot(1,3,3)
% y_values = [Price*6*n_parallel];
% barh(y_values')
% title('Total device cost')
% xlabel('Cost [DKK]')
% set(gca,'yticklabel','','TickDir','out')
% x_lim = xlim;
% xlim([0 x_lim(2)+15])
% %set(gca,'yscale','log')
% legend('Cost')
% legend('Location','south');
% for b = 1:length(TJ)
%     text(b,y_values(b)+2,[sprintf('%0.0f',y_values(b)),'kr'],...
%         'VerticalAlignment','bottom','HorizontalAlignment','center')
% end

end


% Track max temperature
    width   = 10E-3;    %m
    len  = 10E-3;    %m
    t.cu    = 70E-6;
    rho_cu  = 1.68E-8;  %Ohm*m
    R_track = rho_cu*len/(width*t.cu)
    P_track = I_pk.^2*R_track
    dTcu    = P_track*t.cu/(A*K.cu)
    T_track = Tsink+dTAl+dTins+dTcu
    
    
    
    
  Diode_loss = (0.7*I_rms/n_parallel)+(2.12E-3*(I_rms/n_parallel)^2);
  Switch_loss = P.con_Total(3)/12+P.sw_Device(3)+P.dr_Total(3)/12
  JT = ((R_thJC+0.08333+740*10^-6+277*10^-3+52.74*10^-3+41.6*10^-3+0.84)*Switch_loss)+25
  CT = JT - (Switch_loss*R_thJC)
  JT = Switch_loss*R_thJC+50.5
  Switch_loss
  
