#include <Debug/Debug.hpp>
#include <ExpressCPPApp.hpp>
#include <Network/HTTP.hpp>
#include <exception>
#include <format>
#include <nlohmann/json.hpp>
#include <string>

class MissingKey : public std::invalid_argument {
public:
    MissingKey(char const* msg) : std::invalid_argument(msg) {}
};

static void solve(express_cpp::HTTPRequest const& req,
                  express_cpp::HTTPResponse& res) {
    try {
        auto json_from_body = nlohmann::json::parse(req.body);
        if (!json_from_body.contains("size")) {
            throw MissingKey("size");
        }
        if (!json_from_body.contains("grid")) {
            throw MissingKey("grid");
        }
        auto const grid_size = json_from_body["size"].get<int>();
        auto const grid =
            json_from_body["grid"].get<std::vector<std::vector<int>>>();
        res.send(json_from_body.dump());
    } catch (nlohmann::json::type_error const& e) {
        nlohmann::json response_content = {
            {"message",
             std::format("Wrong type <{}> in the body", e.what())}};
        res.status(400).send(response_content.dump());
    } catch (nlohmann::json::exception const& e) {
        nlohmann::json response_content = {{"message", e.what()}};
        res.status(400).send(response_content.dump());
    } catch (MissingKey const& e) {
        nlohmann::json response_content = {
            {"message",
             std::format("Missing key <{}> in the body", e.what())}};
        res.status(400).send(response_content.dump());
    }
}

int main() {
    express_cpp::Config config;
    config.appName = "sudocul_solver_api";
    config.port = 8080;
    express_cpp::ExpressCPPApp<express_cpp::HTTP> app(config);
    app.Router().Post("/solve", solve);
    app.Start();
    return 0;
}
