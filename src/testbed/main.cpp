#include <Mahi/Gui.hpp>
#include <iostream>
#include <tuple>
#include <NTL/RR.h>
#include "OpmNum.hpp"

#include "NTL/ALL_FEATURES.h"
using namespace mahi::gui;

NTL::RR OpmToRR(const OpmNum& n)
{
    char tmp[128] = {};
    format(n, tmp, FormatMode::DebugRaw);

    return NTL::to_RR(tmp);
}

class Testbed final : public Application {
public:

    Testbed() : Application() { }

    void update() override {
        static bool open = true;
        ImGui::SetNextWindowSize(ImVec2(640, 480), ImGuiCond_Once);

        auto a2 = 1e0_opm;
        auto res2 = exp(a2).roundToNearest();
        print(res2);

        auto a = OpmToRR(res2);
        std::cout << a << std::endl;

        if (ImGui::Begin("Testbed", &open))
        {

        }
    	ImGui::End();
    }
};

int main(int argc, char const* argv[])
{
    NTL::RR::SetPrecision(2048);
    NTL::RR::SetOutputPrecision(64);

    Testbed demo;
    demo.set_vsync(true);
    demo.run();
    return 0;
}