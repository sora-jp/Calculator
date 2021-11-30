import decimal
import io
import mpmath

GROUPS = 9
GROUP_SIZE = 8
DIGITS = GROUPS * GROUP_SIZE

mpmath.mp.dps = DIGITS

def format_constant(n: mpmath.mpf):
    #print(n)
    s = mpmath.nstr(n, DIGITS + 1, strip_zeros=False, min_fixed=5, max_fixed=4, show_zero_exponent=True).split('e')
    print("e".join(s))
    s[0] = s[0].replace('.', '').lstrip("-")
    

    digs = []
    for dn in range(GROUPS):
        strs = s[0][dn * 8:dn * 8 + 8]
        dgs = "0x" + "".join(strs)
        dgs = dgs + "0" * (8 - len(strs))
        digs.append(dgs)

    return F"OpmNum::Constant<{','.join(digs)}>({'true' if n < 0 else 'false'}, {int(s[1])})"


def write_constant(file: io.TextIOBase, fcpp: io.TextIOBase, name, n: mpmath.mpf):
    file.write(F"extern const OpmNum {name};\n")
    fcpp.write(F"const OpmNum {name} = {format_constant(n)};")

def write_constant_raw(file: io.TextIOBase, fcpp: io.TextIOBase, name, n):
    file.write(F"extern const OpmNum {name};\n")
    fcpp.write(F"const OpmNum {name} = OpmNum({n});")

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


with open("Tables.hpp", "w") as f:
    with open("Tables.cpp", "w") as fc:
        f.write("\n".join(
            ["#pragma once",
             "#include \"../Config.h\"",
             "#include \"../OpmNum.hpp\"",
             "",
             "// THIS FILE WAS AUTOMATICALLY GENERATED",
             "// CHANGES WILL BE LOST UPON REGENERATION",
             "",
             ""])
        )

        fc.write("\n".join(
            ["#include \"Tables.hpp\"",
             "",
             "// THIS FILE WAS AUTOMATICALLY GENERATED",
             "// CHANGES WILL BE LOST UPON REGENERATION",
             "",
             ""])
        )

        f.write("namespace Constants {\n")
        fc.write("namespace Constants {\n")
        write_constant(f, fc, "ln10", mpmath.ln(mpmath.mpf(10)))
        write_constant(f, fc, "ln2", mpmath.ln(mpmath.mpf(2)))
        write_constant(f, fc, "e", mpmath.exp(mpmath.mpf(1)))
        write_constant(f, fc, "pi", mpmath.pi())
        write_constant(f, fc, "half_pi", mpmath.pi() / mpmath.mpf(2))
        write_constant(f, fc, "quart_pi", mpmath.pi() / mpmath.mpf(4))
        write_constant(f, fc, "tau", mpmath.pi() * mpmath.mpf(2))
        write_constant(f, fc, "one", mpmath.mpf(1))
        write_constant(f, fc, "one_half", mpmath.mpf(1) / mpmath.mpf(2))
        write_constant_raw(f, fc, "nan", "false, true, false")
        write_constant_raw(f, fc, "inf", "false, false, true")
        write_constant_raw(f, fc, "ninf", "true, false, true")
        f.write("}\n")
        fc.write("}\n")

        f.write("namespace Tables {\n")
        fc.write("namespace Tables {\n")
        with open("constants/ln.txt", "r") as f2:
            nums = []
            lns = f2.read().split('\n')
            for i in range(DIGITS + 1):
                num = mpmath.mpmathify(lns[i])
                print(num)
                nums.append(format_constant(num))
                print()

            o = F"const OpmNum lnTable[{DIGITS + 1}] = \n{{\n\t"
            o += ",\n\t".join(nums)
            o += "\n};\n\n"
            f.write("extern const OpmNum lnTable[];\n")
            fc.write(o)

        with open("constants/atan.txt", "r") as f2:
            nums = []
            lns = f2.read().split('\n')
            for i in range(DIGITS + 1):
                num = mpmath.mpmathify(lns[i])
                print(num)
                nums.append(format_constant(num))
                print()

            o = F"const OpmNum atanTable[{DIGITS + 1}] = \n{{\n\t"
            o += ",\n\t".join(nums)
            o += "\n};\n\n"
            f.write("extern const OpmNum atanTable[];\n")
            fc.write(o)
        
        with open("constants/gamma.txt", "r") as f3:
            nums = []
            lns = f3.read().split('\n')
            lns = list(filter(None, lns))
            for i in range(len(lns)):
                num = mpmath.mpmathify(lns[i])
                print(num)
                nums.append(format_constant(num))
                print()

            o = F"const OpmNum gammaTable[{len(lns)}] = \n{{\n\t"
            o += ",\n\t".join(nums)
            o += "\n};\n\n"
            f.write("extern const OpmNum gammaTable[];\n")
            fc.write(o)

        f.write("}\n")
        fc.write("}\n")

        # generate(f, lambda x: mpmath.ln(x), "lnTable")
        # generate(f, lambda x: mpmath.sqrt(x), "sqrtTable")
