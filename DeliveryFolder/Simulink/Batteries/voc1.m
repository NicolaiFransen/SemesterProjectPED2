
data=xlsread('Param_d_50.xlsx')
t=[0:1:1999];
firstC=data(:,3);
secondC=data(:,2);


%%
ax1 = subplot(2,1,1); % top subplot

plot(ax1,t,firstC);

hold on
plot(VOC1,'Linewidth',1)
ylabel('Voc[V]')

title(ax1,'Validating battery simulation')
legend({'Experimental','Simulation'},'Location','north','Fontsize',11)
ax2 = subplot(2,1,2); % bottom subplot
plot(ax2,t,secondC);

xlabel('Time[s]')
ylabel('I[A]')