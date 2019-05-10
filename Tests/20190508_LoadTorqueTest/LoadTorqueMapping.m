
tau = [4.9, 6.7, 5.8];
n = [211, 455, 980];
Vdc = [95.98, 95.98, 95.98];
V_RE = [16.1, 23.1, 20.4];
I = [4.2, 6, 5.25];
Rexternal = V_RE./I;
R_parallel = [1.1, 1.1, 1.1];
Rs = -(R_parallel.*Rexternal)./(R_parallel-Rexternal);

c = tau ./ ((Vdc.*n)./(Rexternal+Rs));