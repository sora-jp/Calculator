#include <Mahi/Gui.hpp>
#include "imgui_internal.h"
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

struct TestData
{
    double x, y;
};

void PerformTest(std::vector<TestData>& out, double min, double max, int iters, std::function<OpmNum(const OpmNum&)> opmFunc, std::function<NTL::RR(const NTL::RR&)> ntlFunc)
{
    const auto minStr = std::to_string(min);
    const auto maxStr = std::to_string(max);
    const auto opmMin = parse(minStr.c_str());
    const auto opmMax = parse(maxStr.c_str());

    const auto opmStep = invert(OpmNum(iters - 1)) * (opmMax - opmMin);

    out.clear();
    out.resize(iters);

	//#pragma omp for
    for (int i = 0; i < iters; i++)
    {
        auto opmCur = opmMin + opmStep * OpmNum(i);
        auto rrCur = OpmToRR(opmCur);

        auto opmRes = opmFunc(opmCur);
        auto res = ntlFunc(rrCur) - OpmToRR(opmRes);

        out[i].x = NTL::to_double(rrCur);
        out[i].y = NTL::to_double(res);
    }
}

class Testbed final : public Application {
public:

    Testbed() : Application() { }

    void update() override {
        static bool open = true;
        static bool hasDock = false;

        //auto a2 = 1e0_opm;
        //auto res2 = exp(a2).roundToNearest();
        //print(res2);
        //
        //auto a = OpmToRR(res2);
        //std::cout << a << std::endl;

        if (!hasDock) 
        {
            hasDock = true;
            ImGuiID dockId = ImGui::DockBuilderAddNode(0, ImGuiDockNodeFlags_None);
            ImGuiID dockLeft, dockCenter;
            ImGui::DockBuilderSetNodeSize(dockId, ImVec2(1280, 720));
            ImGui::DockBuilderSplitNode(dockId, ImGuiDir_Left, 0.25f, &dockLeft, &dockCenter);
            ImGui::DockBuilderDockWindow("Settings", dockLeft);
            ImGui::DockBuilderDockWindow("Graph", dockCenter);
            ImGui::DockBuilderFinish(dockId);
        }

        static std::vector<TestData> data;
        static double min = 0, max = 10;
        if (ImGui::Begin("Settings"))
        {
            static int iters = 1000;
            
            ImGui::DragDoubleRange2("Test range", &min, &max);
            ImGui::InputInt("Number of iterations", &iters);
            if (ImGui::Button("Perform test"))
            {
                PerformTest(data, min, max, iters, invert, [](const NTL::RR& val) {return NTL::inv(val); });
            }
        }
    	ImGui::End();
        
        if (ImGui::Begin("Graph", &open))
        {
            ImPlot::SetNextPlotLimits(min, max, min, max);
            if (ImPlot::BeginPlot("plot"))
            {
                ImPlot::PlotLineG("error", [](void* d, int idx) { return ImPlotPoint(static_cast<TestData*>(d)[idx].x, static_cast<TestData*>(d)[idx].y); }, data.data(), data.size());
				ImPlot::EndPlot();
            }
        }
        ImGui::End();

        if (!open) quit();
    }
};

int main(int argc, char const* argv[])
{
    NTL::RR::SetPrecision(4096);
    NTL::RR::SetOutputPrecision(72);

    Testbed demo;
    demo.set_vsync(true);
    demo.run();
    return 0;
}