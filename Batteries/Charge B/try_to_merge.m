data=xlsread('Param_d_50.xlsx')
t=[0:1:1999];
firstC=data(:,3);
secondC=data(:,2)

%%
ax1 = subplot(2,1,1); % top subplot

plot(ax1,t,firstC);
title(ax1,'Applying short current pulse on battery D @ 50% SOC')
xlabel('Time[s]')
ylabel('Voc[V]')

ax2 = subplot(2,1,2); % bottom subplot
plot(ax2,t,secondC);

xlabel('Time[s]')
ylabel('I[A]')
cap=trapz(t,secondC);