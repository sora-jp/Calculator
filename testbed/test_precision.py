import math
import subprocess
import time

import matplotlib.pyplot as plt
import numpy as np
import mpmath
import multiprocessing
import itertools
import tqdm

proc = subprocess.Popen(["../bin/Release/Calculator.exe", "--info"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)

GROUP_SIZE = 8
GROUPS = int(proc.communicate()[0])
DIGITS = GROUPS * GROUP_SIZE
ULP = mpmath.mpf(10) ** mpmath.mpf(-DIGITS + 9)

mpmath.mp.dps = DIGITS


def gen_single(start: mpmath.mpf, norm_fac: mpmath.mpf, x: int):
    return start + norm_fac * x + norm_fac * mpmath.rand()


def calc_error(actual, expected):
    if expected == 0:
        return 0

    err = actual[0] - expected
    return err / (ULP * actual[1])


def test_thread(args):
    (fn_name, nums) = args
    proc_c = subprocess.Popen(["../bin/Release/Calculator.exe", "--test"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    proc_input = bytes(F"{fn_name}\n{len(nums)}\n" + "\n".join([str(s) for s in nums]), "ascii")
    o = proc_c.communicate(proc_input)[0]
    o = o.splitlines()

    data = []
    for i in range(0, len(o), 2):
        exp = mpmath.mpf(10) ** mpmath.mpf(int(o[i+1]))
        actual = mpmath.mpmathify(str(o[i], "ascii")) * exp
        data.append((actual, exp))

    return data


def test(fn_name: str, fn, count: int, min: mpmath.mpf, max: mpmath.mpf):
    t_start = time.time()
    norm_fac = (max - min) / mpmath.mpf(count)

    with multiprocessing.Pool() as mp_pool:
        print("Generating numbers... ", end='')
        xs = np.array(mp_pool.starmap(gen_single, [(min, norm_fac, i) for i in range(count)]))
        print("Done!")

        # print("Calculating ground truth...")
        ys = []
        for y in tqdm.tqdm(mp_pool.imap(fn, xs, 1000), total=len(xs), desc="Calculating ground truth"):
            ys.append(y)

        ys = np.array(ys)
        # print("Running test...")

        workitems = []
        wgroup_size = 2500
        workgroups = math.ceil(count / wgroup_size)

        for i in range(workgroups):
            workitems.append((fn_name, xs[i * wgroup_size: i * wgroup_size + wgroup_size]))

        calcres = []
        for r in tqdm.tqdm(itertools.chain.from_iterable(mp_pool.imap(test_thread, workitems)), total=count, desc="Running test"):
            calcres.append(r)

        #errs = np.array(mp_pool.starmap(calc_error, [(calcres[i], ys[i]) for i in range(count)]))
        errs = []
        mean = mpmath.mpf(0)
        sqrmean = mpmath.mpf(0)
        min_err = (mpmath.inf,)
        max_err = (mpmath.ninf,)

        for i in tqdm.trange(count, desc="Aggregating results"):
            e = calc_error(calcres[i], ys[i])
            errs.append(e)
            if e.__abs__() > max_err[0]:
                max_err = (e, xs[i], ys[i], calcres[i][0])
            elif e.__abs__() < min_err[0]:
                min_err = (e, xs[i], ys[i], calcres[i][0])
            mean = mean + e / count
            sqrmean = sqrmean + e * e / count


        print("Done!")
        print("RMS:  " + str(sqrmean.sqrt()))
        print("Mean: " + str(mean))
        print("Standard deviation: " + str((mean * mean - sqrmean).sqrt()))
        print()

        def pe(x):
            print("\tNum      : " + str(x[1]))
            print("\tExpected : " + str(x[2]))
            print("\tActual   : " + str(x[3]))

        print("Min error: " + str(min_err[0]))
        pe(min_err)
        print("Max error: " + str(max_err[0]))
        pe(max_err)

        t_diff = time.time() - t_start
        print(F"Test completed in {t_diff} seconds")

        plt.ioff()
        plt.plot(xs, errs)
        plt.plot(xs, ys)
        plt.show()


def lnn(x):
    return mpmath.sin(x)


if __name__ == "__main__":
    test("sin", lnn, 1000000, -mpmath.pi() * 2, mpmath.pi() * 2)
