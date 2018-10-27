function res=kiks_fourbyte2ip(val) % fourbyte is expected to be a signed integer
setbits=find(bitget(val,(1:32)));
fourbyte=sum(bitset(0,setbits));

shift1=bitshift(bitshift(fourbyte,-8*3),8*3);
shift2=bitshift(bitshift(fourbyte,-8*2),8*2);
shift3=bitshift(bitshift(fourbyte,-8),8);

byte1=fourbyte-shift3;
byte2=bitshift(shift3-shift2,-8);
byte3=bitshift(shift2-shift1,-8*2);
byte4=bitshift(shift1,-8*3);

res=sprintf('%d.%d.%d.%d',byte4,byte3,byte2,byte1);