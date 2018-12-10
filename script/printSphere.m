
tic;
[x,y,z] = sphere;
xPos = [];
yPos = [];
zPos = [];
radius = [];

file = fopen('../build/Aggregate.txt','r');
while ~feof(file)
    tline = str2num(fgetl(file));
    xPos(end+1) = tline(2);
    yPos(end+1) = tline(3);
    zPos(end+1) = tline(4);
    radius(end+1) = tline(5);
end
fclose(file);

surf(x,y,z)
hold on
for i=1:length(xPos)
  surf(x*radius(i)+xPos(i), y*radius(i)+yPos(i), z*radius(i)+zPos(i));
end
hold off
axis equal;
toc;
