clear all
clc

% VARIAVEIS
M = 0.5; %massa carrinho
m = 0.099; %massa pendulo
l = 0.38;
% J = 0.0051; %inércia
b = 0.02; % atrito carro
% c = 0.0026; % atrito pendulo
g = 9.8;


%%
load ID_dataSIAI.mat;
T= t(129:286,1)-t(129);
VReal = Vin(129:286,1);
VDes = p(129:286,1);
%figure(1);plot(TemposR,AnguloR); grid on

Vss=mean(VReal(50:60));


global a
global b
global Vss
global K

%figure;
%plot(TemposR,AnguloR,'r');
%hold on;
%plot(TempoSim,AnguloSim,'b');
%legend('Real','Simulado');


funcao_objetivo= @ (parametros) erro_velocidades (parametros);
parametros_iniciais = [3 4];
parametros_otimizados = fminsearch(funcao_objetivo, parametros_iniciais)

%parametros_otimizados

% figure;
% plot(T,VReal,'r');
% hold on;
% plot(T,VDes,'b');
% legend('Real','Simulado');
