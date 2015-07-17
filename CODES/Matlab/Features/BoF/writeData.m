function writeData(confMatrix,txtName)
fid=fopen(txtName,'wt');
[m,n]=size(confMatrix);
for i=1:1:m
    for j=1:1:n
        if j==n
            fprintf(fid,'%f\n',confMatrix(i,j));
        else
            fprintf(fid,'%f\t',confMatrix(i,j));
        end
    end
end
fclose(fid);