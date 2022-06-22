fid=fopen('data.txt');
data=textscan(fid,'%d %f');
fclose ( fid );
avgSteps_x=data{1};
avgSteps_y=data{2};

figure ;
title ('Average steps d to next Prime Number for n Digits');
xlabel('n');
ylabel('d');
hold on;
plot(avgSteps_x,avgSteps_y);
legend('avgDistance');