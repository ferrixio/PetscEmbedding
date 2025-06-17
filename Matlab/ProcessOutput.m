function [x,y] = ProcessOutput()

data = readmatrix('~/Projects/PetscEmbedding/output/results.csv');

norm1 = data(:,3);
norm2 = data(:,4);

% figure(1);
% plot(norm1);
% grid on;
% 
% figure(2);
% plot(norm2);
% grid on;

x = mean(norm1);
y = mean(norm2);
end