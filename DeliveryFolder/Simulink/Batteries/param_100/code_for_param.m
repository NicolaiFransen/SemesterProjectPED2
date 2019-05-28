dataA=xlsread('Param_A_100.xlsx')
t=[0:1:1999];
firstA=dataA(:,3);
secondA=dataA(:,2)

dataB=xlsread('Param_B_100.xlsx')

firstB=dataB(:,3);
secondB=dataB(:,2)


dataD=xlsread('Param_D_100.xlsx')

firstD=dataD(:,3);
secondD=dataD(:,2)

%%
ax1 = subplot(2,1,1);

plot(ax1,Param_A_100.Time,firstA,Param_A_100.Time,firstB,Param_A_100.Time,firstD);


title(ax1,'Battery Parameters @ 100% SOC')
xlabel('Time[s]')
ylabel('Voc[V]')
legend({'Battery A','Battery B','Battery D'},'Location','north')
ax2 = subplot(2,1,2);
plot(ax2,Param_A_100.Time,secondA);
xlabel('Time[s]')
ylabel('I[A]')
