
%%
ax1 = subplot(2,1,1);

plot(ax1,Param_A_100.Time,Param_A_100.ai0,Param_A_100.Time,Param_B_100.ai0,Param_A_100.Time,Param_D_100.ai0);

title(ax1,'Battery Parameters @ 100% SOC')
xlabel('Time[s]')
ylabel('Voc[V]')
legend({'Battery A','Battery B','Battery D'},'Location','north')
ax2 = subplot(2,1,2);
plot(ax2,Param_A_100.Time,Param_A_100.ai7);
xlabel('Time[s]')
ylabel('I[A]')
