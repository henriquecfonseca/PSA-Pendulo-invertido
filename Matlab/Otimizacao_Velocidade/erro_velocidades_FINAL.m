function error = erro_velocidades_FINAL(parametros)


global a
global b
global K
%global Vss

a= parametros (1);
b = parametros (2);
K= parametros (3);
%K= Vss*b/300;

out = sim('modelo_velocidade.slx');
VelR = out.Data.signals(1).values;
VelD = out.Data.signals(2).values;
t=out.Data.time;

% Compute error (e.g., mean squared error)
error = mean((VelD - VelR).^2);

end