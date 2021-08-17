prec=2048!;
display=decimal!;

for i from 0 to 80 do print(evaluate(log(1 + (10 ^ -i)), i)) >> "ln.txt";
for i from 0 to 80 do print(evaluate(atan(10 ^ -i), i)) >> "atan.txt";