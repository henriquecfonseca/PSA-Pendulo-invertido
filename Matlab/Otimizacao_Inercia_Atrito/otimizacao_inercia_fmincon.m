% VARIÁVEIS
M = 0.5; % massa do carrinho
m = 0.099; % massa do pêndulo
l = 0.38;  % comprimento do pêndulo
g = 9.8;   % aceleração grvitica

% Carregar dados
load dados_angulo_novo(1).mat
AnguloReal = AnguloR(33:788,1);
TemposR = t(33:788,1)-t(33,1);

global J
global c

% Função objetivo
funcao_objetivo = @(parametros) erro_inercia_novo(parametros);

% Parâmetros iniciais
parametros_iniciais = [0.001, 0.001];

% Limites inferiores para garantir que os parâmetros sejam positivos
limites_inferiores = [1e-10, 1e-4];

% Configurações da otimização
options = optimoptions('fmincon', ...
    'Display', 'iter-detailed', ...
    'Algorithm', 'sqp', ...
    'MaxIterations', 1000, ...
    'MaxFunctionEvaluations', 5000, ...
    'StepTolerance', 1e-12, ...
    'OptimalityTolerance', 1e-12, ...
    'FunctionTolerance', 1e-12);

% Otimização com fmincon
[parametros_otimizados, fval, exitflag, output] = fmincon(funcao_objetivo, ...
    parametros_iniciais, [], [], [], [], limites_inferiores, [], [], options);

% Configurações de precisão
format long;

% Exibir os parâmetros otimizados com alta precisão
disp('Parâmetros Otimizados:');
disp(parametros_otimizados);

% Exibir valor da função objetivo
disp('Valor da Função Objetivo:');
disp(fval);

% Usar fprintf para controle detalhado
fprintf('Parâmetros Otimizados com Alta Precisão:\n');
fprintf('J: %.15f\n', parametros_otimizados(1));
fprintf('c: %.15f\n', parametros_otimizados(2));

% Exibir detalhes da otimização
disp('Detalhes da Otimização:');
disp(output);

