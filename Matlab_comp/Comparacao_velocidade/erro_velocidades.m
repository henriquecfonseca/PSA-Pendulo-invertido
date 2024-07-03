function error = erro_velocidades(parametros)
global a
global b
global Vss
global K



a = parametros(1);
b = parametros(2);
K = Vss*b/300;

out = sim('velocidades.slx');
VelR = out.Data.signals(1).values;
VelD = out.Data.signals(2).values;
t=out.Data.time;

% Compute error (e.g., mean squared error)
error = mean((VelD - VelR).^2);


end