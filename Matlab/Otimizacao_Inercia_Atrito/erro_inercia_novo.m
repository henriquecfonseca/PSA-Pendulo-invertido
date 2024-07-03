function error = erro_inercia_novo(parametros)

global J
global c



J = parametros (1);
c = parametros (2);


out = sim('otimizacao_inercia_final.slx');
angR = out.Data.signals(1).values(:,1);
AnguloSim = out.Data.signals(2).values(:,1);

% Compute error (e.g., mean squared error)
error = mean((AnguloSim - angR).^2);


end