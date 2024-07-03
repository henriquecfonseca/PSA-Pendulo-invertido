% VARIAVEIS
clear all
clc
M = 0.5;      %massa carrinho
m = 0.099;    %massa pendulo
l = 0.38;     %comprimento do pendulo
J = 0.0001;   %inércia do pendulo
B = 0.02;     % atrito carro
c = 0.002644555192158;   % atrito pendulo
g = 9.8;      %aceleração gravítica

 



%%
%Driver inicial
load Data_driver1.mat;
% T= t(129:286,1)-t(129);
% VReal = Vin(129:286,1);
% VDes = p(129:286,1);



%Driver final
load ident_500mm.mat;
T= t(1:3000);
PosReal = p(1:3000);
VDes = vDes(1:3000);


%Vss=mean(VReal(50:60));

global a
global b
global K
% global Vss


funcao_objetivo= @ (parametros) erro_velocidades_FINAL (parametros);
parametros_iniciais = [1,1,1];
parametros_otimizados = fminsearch(funcao_objetivo, parametros_iniciais)


% figure;
% plot(T,VReal,'r');
% hold on;
% plot(T,VDes,'b');
% legend('Real','Simulado');

