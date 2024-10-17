
#ifndef SOLVE_HPP_
#define SOLVE_HPP_

#include <exception>

#include <nlohmann/json.hpp>

#include <Network/HTTP.hpp>


class Solve {
    using Grid = std::vector<std::vector<int>>;

public:
    static void operator()(express_cpp::HTTPRequest const& req,
                           express_cpp::HTTPResponse& res) noexcept;

private:
    class MissingKey : public std::invalid_argument {
    public:
        MissingKey(char const* msg) : std::invalid_argument(msg) {}
    };

    static nlohmann::json solve_grid(int size,
                                     const Grid& grid);
    static std::string grid_to_csv_string(const Grid& grid);
};

#endif /* !SOLVE_HPP_ */
