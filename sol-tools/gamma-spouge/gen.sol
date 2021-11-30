#!/usr/bin/sollya

prec=4096!;
A = 80;

bashexecute("rm ./gamma.txt");

f = 1;
for i from 1 to A do {
	ck = (((-1) ^ (i-1)) / f) * ((A-i)^(i-(1/2))) * exp(A-i);
	f = f * i;
	print(~ck) >> "gamma.txt";
};
