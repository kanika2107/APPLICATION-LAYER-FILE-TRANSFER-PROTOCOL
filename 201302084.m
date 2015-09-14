 Read = csvread('~/201302084',0,2,[0,2,99,5]);
 Mean = mean(Read');
 L = lpc(Mean,50);
 L = L(2:21)*-1;
 L = (flipud(L'));
 %B = A(80:99);
 for i=1:7
    B=A(79+i:79+19+i);
    A(1,99+i) = B*L;
 end
 stem(A','filled');
 ylabel('Average_Value');
 xlabel('Days');

 
 