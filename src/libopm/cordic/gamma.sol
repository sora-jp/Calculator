ChebCoeff = proc(n, m) {
	var res;
	res = NaN;
	if ((m == 1) && (n > 2)) then res = -ChebCoeff(n - 2, 1);
	if ((m == n) && (n > 2)) then res = (2 * ChebCoeff(n - 1, n - 1));
	if ((n > m) && (m > 1)) then res = (2 * ChebCoeff(n - 1, m - 1)) - ChebCoeff(n - 2, m);
	if ((n == 1) && (m == 1)) then res = 1;
	if ((n == 2) && (m == 2)) then res = 1;
	return res;
};

dblfact = proc(k) {
	var res;
	res = 1;
	for i from 0 to k do {
		if ((i > 0) && (mod(i, 2) == mod(k, 2))) then res = res * i;
	};
	return res;
};

fact = proc(n) {
	var x;
	x = (n + 1) * 2;
	return (sqrt(pi) * (dblfact(x - 2) / (2 ^ ((x-1)/2))));
};

pk = proc(k, g) {
	var s;
	s = 0;
	for i from 0 to k do {
		s = s + ChebCoeff(k * 2 + 1, i * 2 + 1) * fact(i - 0.5) * ((i + g + 0.5) ^ (-(i+0.5))) * exp(i + g + 0.5);
	};
	return ~(s * (sqrt(2) / pi));
};

q = 15;
for j from 0 to q do print(pk(j, q));
