#!/usr/bin/sollya

prec=2048!;
P = 72;

best = 100;
poly = 0;

for i from 0 to 10 do {
	p = remez(1/x, i, [1;10]);
	err = ~dirtyinfnorm(p - 1/x, [1;10]);
	iters = ceil(log2(-P/log10(err))/log2(3));
	adds = iters * 3 + i + 1;
	muls = iters * 3 + i + 1;
	print("Polynomial approximation grade", i, ", ops:", adds + muls, ", iters:", iters, ", err:", err);
	
	if (adds + muls <= best) then {
		best = adds + muls;
		poly = p;
	};
};

r = degree(poly);

bashexecute("rm poly.txt");
for j from 0 to r do {
	print(coeff(poly, j)) >> "poly.txt";
};