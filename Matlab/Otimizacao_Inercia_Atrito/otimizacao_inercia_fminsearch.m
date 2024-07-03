% VARIAVEIS
M = 0.5;     %massa carrinho
m = 0.099;   %massa pendulo
l = 0.38;    %comprimento pendulo
%J = 0.0068  %inercia solidworks; 
B = 0.02;    %atrito carro
%c = 0.0026; %atrito pendulo
g = 9.8;     %aceleracao gravitica


load dados_angulo_novo(1).mat
AnguloReal = AnguloR(33:788,1);
TemposR = t(33:788,1)-t(33,1);
%figure(1);plot(TemposR,AnguloR); grid on

global J
global c


funcao_objetivo= @ (parametros) erro_inercia_novo (parametros);
parametros_iniciais = [0.00001 0.00001];
parametros_otimizados = fminsearch(funcao_objetivo, parametros_iniciais)


