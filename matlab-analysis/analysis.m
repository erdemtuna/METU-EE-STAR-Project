sensor1 = importdata('sensor1.txt');
sensor2 = importdata('sensor2.txt');

difference = sensor2(:,2) - sensor1(:,2)

plot(sensor1(:,1),difference)