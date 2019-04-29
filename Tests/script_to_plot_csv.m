close all;

%Measurement values from excel reading
data = csvread('20190429_SVM_SW_test/SVM_SW_test.csv');
%Messwerte in Variablen speichern
t = data(:,1);
vOL = data(:, 2);


%Filter
%vin1000f = smoothdata(vOL,'gaussian',20);
 
figure
plot(t, vOL)
xlim([0, 0.2])
xlabel('Time[s]')
ylabel('Voltage[V]')
legend('SVM, Single phase')


