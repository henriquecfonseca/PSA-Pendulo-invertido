% VARIAVEIS
M = 0.5;     %massa do carro
m = 0.099;   %massa do pêndulo
l = 0.38;    %comprimento do pêndulo
J = 0.0001;  %inércia do pêndulo
B = 0.2;     %atrito do carro
c = 0.002644555192158;   %atrito do pêndulo
g = 9.8;     %aceleração gravítica


% equaçao da velocidade = [K/((s+a)*(s+b))]

K = 11.6671;
a = 11.3737;
b = 0.0111;


s = tf('s');

% zpk(G1)
% sisotool(G1)


G1=[m*l*s/((J+m*l^2)*s^2+s*c-m*g*l)]*180/(pi)*([K/((s+a)*(s+b))]/1000);
zpk(G1)
%sisotool(G1)

Pendulo=[m*l*s/((J+m*l^2)*s^2+s*c-m*g*l)]*180/(pi);

carro = [K/((s+a)*(s+b))]/1000;

Controlo_angulo = (46.092*(s+0.3686)*(s+5.276))/s;

X_V = (carro/s)/(1+Controlo_angulo*(G1));
zpk(X_V);
%sisotool(X_V)

Kp= -26.257*6;
Kd= -26.257;