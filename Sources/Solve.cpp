#include <Debug/Debug.hpp>
#include <format>
#include <nlohmann/json.hpp>

#include "Solve.hpp"
#include "Tools/Exec.hpp"

void Solve::operator()(express_cpp::HTTPRequest const& req,
                       express_cpp::HTTPResponse& res) noexcept {
    try {
        const auto json_from_body = nlohmann::json::parse(req.body);
        if (!json_from_body.contains("size")) {
            throw MissingKey("size");
        }
        if (!json_from_body.contains("grid")) {
            throw MissingKey("grid");
        }
        auto const grid_size = json_from_body["size"].get<int>();
        auto const grid = json_from_body["grid"].get<Grid>();
        nlohmann::json a = Solve::solve_grid(grid_size, grid);
        res.send(a.dump());
    } catch (nlohmann::json::type_error const& e) {
        nlohmann::json a = {
            {"message", std::format("Wrong type <{}> in the body", e.what())}};
        res.status(400).send(a.dump());
    } catch (nlohmann::json::exception const& e) {
        nlohmann::json a = {{"message", e.what()}};
        res.status(400).send(a.dump());
    } catch (MissingKey const& e) {
        nlohmann::json a = {
            {"message", std::format("Missing key <{}> in the body", e.what())}};
        res.status(400).send(a.dump());
    }
}
std::string Solve::grid_to_csv_string(const Grid& grid) {
    std::string result;

    std::for_each(grid.begin(), grid.end(), [&](const std::vector<int>& line) {
        auto i = 0;
        for (; i < line.size() - 1; ++i) {
            result += std::to_string(line[i]) + ",";
        }
        result += std::to_string(line[i + 1]) + "\n";
    });
    return "\"" + result + "\"";
}

nlohmann::json Solve::solve_grid(int size, const Grid& grid) {
    nlohmann::json a = {
        {"grid", nlohmann::json::parse(Exec::run(
                     std::format("docker run antwxne/sudocul_solver "
                                 "sudocul_solver {} --content {} --json-term",
                                 size, Solve::grid_to_csv_string(grid))))}};
    return a;
}