#include "Algorithm.h"

struct IntSettings
{
    const NCompiledExpression& expr;
    NExpressionContext ctx;
    OpmNum eps;
    std::string var;

    OpmNum eval(const OpmNum& inp)
    {
        ctx.set(inp, var);
        //FIXME
        auto res = wrap(1e0_opm);//expr.exec(ctx);
        if (res.type() == ValueType::Real)
        {
            auto rt = *unwrap<OpmNum>(res);
            return rt;
        }
        abort();
    }
};

struct ASRMem
{
    OpmNum simpson, m, fm;
};

ASRMem quadMem(IntSettings& s, const OpmNum& a, const OpmNum& fa, const OpmNum& b, const OpmNum& fb)
{
    ASRMem ret;
    ret.m = (a + b) / 2;
    ret.fm = s.eval(ret.m).roundToNearest();
    ret.simpson = (abs(b - a) / 6e0_opm) * (fa + 4e0_opm * ret.fm + fb);
    return ret;
}

OpmNum quadAsr(IntSettings& s, const OpmNum& a, const OpmNum& fa, const OpmNum& b, const OpmNum& fb, const OpmNum& m, const OpmNum& fm, const OpmNum& eps, const OpmNum& whole, int32_t maxR)
{
    auto l = quadMem(s, a, fa, m, fm);
    auto r = quadMem(s, m, fm, b, fb);
    auto d = l.simpson + r.simpson - whole;
    if (maxR <= 0 || abs(d) <= eps * 15) return l.simpson + r.simpson + d / 15;
    return quadAsr(s, a, fa, m, fm, l.m, l.fm, eps * 5e-1_opm, l.simpson, maxR - 1) + quadAsr(s, m, fm, b, fb, r.m, r.fm, eps * 5e-1_opm, r.simpson, maxR - 1);
}

OpmValue Algorithm::adaptiveSimpson(const NCompiledExpression& expr, const OpmNum& left, const OpmNum& right, const OpmNum& tolerance)
{
    IntSettings s {expr, NExpressionContext(), tolerance, "x"};
    const auto fa = s.eval(left), fb = s.eval(right);
    const auto m = quadMem(s, left, fa, right, fb);
    return wrap(quadAsr(s, left, fa, right, fb, m.m, m.fm, tolerance, m.simpson, 15));
}