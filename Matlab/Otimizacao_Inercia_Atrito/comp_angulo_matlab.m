%%
clc;
close all;
clear all;
numSec=25;
DT = 5; % ms
NP = numSec*1000/5;
t=zeros(NP,1);
AnguloR=zeros(size(t));
%%p=zeros(size(t));
%s1 = serial('/dev/tty.usbserial-1430');   % define serial port
%s1 = serial('/dev/tty.usbmodem14301');
%s1 = serial('/dev/tty.usbmodem14401');
s1 = serial('COM21');  
s1.BaudRate=115200;               % define baud rate (equal to arduino)
set(s1, 'terminator', 'LF');    % define the terminator for println
fopen(s1);

try                             % use try catch to ensure fclose
    
                                % signal the arduino to start collection
w=fscanf(s1,'%s');              % must define the input % d or %s, etc.
if (w=='A')
    display(['Collecting data']);
    fprintf(s1,'%s\n','A');     % establishContact just wants 
                                % something in the buffer
end

i=0;
t0=tic;
while (toc(t0)<=numSec)
    i=i+1;
    t(i)=fscanf(s1,'%f')/1000.;
    AnguloR(i)=fscanf(s1,'%d');       % must define the input % d, %f, %s, etc.
    %%p(i)=fscanf(s1,'%d');  
end
fclose(s1);
   

catch exception
    fclose(s1);                 % always, always want to close s1
    throw (exception);
end      
%%t = t(1:i);
%%p = p(1:i);
%%Vin = Vin(1:i);
%%plot(t,Vin,'r',t,p,'k','LineWidth',3); grid on;    

maxT = t(i);
save('Dados_angulo.mat');