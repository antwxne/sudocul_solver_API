#include <Debug/Debug.hpp>
#include <ExpressCPPApp.hpp>
#include <Network/HTTP.hpp>
#include <exception>
#include <format>
#include <string>
#include <functional>

#include "Solve.hpp"

int main() {
    express_cpp::Config config;
    config.appName = "sudocul_solver_api";
    config.port = 8080;
    express_cpp::ExpressCPPApp<express_cpp::HTTP> app(config);
    app.Router().Post("/solve", &Solve::operator());
    app.Router().Post("/",
                      [](const auto &req, auto &res) { res.send("plop"); });

    app.Start();
    return 0;
}
