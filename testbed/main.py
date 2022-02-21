import mpmath
import matplotlib.pyplot as plt
import test_precision

def sin(x): return mpmath.sin(x)
def cos(x): return mpmath.cos(x)
def tan(x): return mpmath.tan(x)

def asin(x): return mpmath.asin(x)
def acos(x): return mpmath.acos(x)
def atan(x): return mpmath.atan(x)

def exp(x): return mpmath.exp(x)
def ln(x): return mpmath.ln(x)

TESTS = [
    ("sin", sin, -mpmath.pi, mpmath.pi, 331),
    ("cos", cos, -mpmath.pi, mpmath.pi, 332),
    ("tan", tan, -mpmath.pi, mpmath.pi, 333),
    ("asin", asin, mpmath.mpf(-1), mpmath.mpf(1), 334),
    ("acos", acos, mpmath.mpf(-1), mpmath.mpf(1), 335),
    ("atan", atan, mpmath.mpf(-100), mpmath.mpf(100), 336),
    ("ln", ln, mpmath.mpf(0.1), mpmath.mpf(100), 337),
    ("exp", exp, mpmath.mpf(-100), mpmath.mpf(100), 338),
]

def run_tests():
    plt.ioff()
    for t in TESTS:
        test_precision.test(t[0], t[1], t[4], 10000, t[2], t[3])
    plt.show()

if __name__ == "__main__":
    run_tests()