import decimal
import io
import mpmath

GROUPS = 9
GROUP_SIZE = 8
DIGITS = GROUPS * GROUP_SIZE

mpmath.mp.dps = DIGITS

def format_constant(n: mpmath.mpf):
    #print(n)
    s = mpmath.nstr(n, DIGITS, strip_zeros=False, min_fixed=5, max_fixed=4, show_zero_exponent=True).split('e')
    print("e".join(s))
    s[0] = s[0].replace('.', '').replace('-', '')

    digs = []
    for dn in range(GROUPS):
        strs = s[0][dn * 8:dn * 8 + 8]
        dgs = "0x" + "".join(strs)
        digs.append(dgs)

    return F"OpmNum::Constant<{','.join(digs)}>({'true' if n < 0 else 'false'}, {int(s[1])})"


def write_constant(file: io.TextIOBase, fcpp: io.TextIOBase, name, n: mpmath.mpf):
    file.write(F"extern const OpmNum {name};\n")
    fcpp.write(F"const OpmNum {name} = {format_constant(n)};")


def generate(file, op, name):
    nums = []
    for i in range(DIGITS):
        num = mpmath.mpf(1) + mpmath.mpf(10) ** mpmath.mpf(-i)

        res: mpmath.mpf = op(num)
        print(num)
        nums.append(format_constant(res))
        print()

    o = F"static const OpmNum {name}[{DIGITS}] = \n{{\n\t"
    o += ",\n\t".join(nums)
    o += "\n};\n\n"
    file.write(o)

with open("poly.txt", "r") as f2:
	nums = []
	lns = f2.read().split('\n')
	for i in lns:
		if (i == ""): continue
		num = mpmath.mpmathify(i)
		print(num)
		nums.append(format_constant(num))
		print()

	o = F"const OpmNum divPoly[{DIGITS + 1}] = \n{{\n\t"
	o += ",\n\t".join(nums)
	o += "\n};\n\n"
	print(o)

        # generate(f, lambda x: mpmath.ln(x), "lnTable")
        # generate(f, lambda x: mpmath.sqrt(x), "sqrtTable")
