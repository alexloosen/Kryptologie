fid=fopen('data.txt');
data=textscan(fid,'%d %f');
fclose ( fid );
avgSteps_x=data{1};
avgSteps_y=data{2};

figure ;
title ('Average steps per number of digits');
xlabel('n [-]');
ylabel('t [s]');
hold on;
plot(avgSteps_x,avgSteps_y);
legend('avgSteps');