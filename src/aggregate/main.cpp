#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <tuple>

#include <getopt.h>

#include "core/sphere.h"
#include "core/control.h"
#include "core/file.h"

#include "common/math_utils.cpp"

int main(int argc, char *argv[])
{

    static struct option long_options[] = {
        {"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},
        {"time", no_argument, NULL, 't'},
        {"filespawn", required_argument, NULL, 'f'},
        {"radroot", required_argument, NULL, 50},
        {"explrad", required_argument, NULL, 51},
        {"alpha", required_argument, NULL, 52},
        {"beta", required_argument, NULL, 53},
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0}};

    bool file_input_provided = false, do_help = false, do_time = false, angle_provided = false;
    std::string file_output{"Aggregate.txt"}, file_input{}, file_spawn{};
    double rad_root = 6.0, default_expl_rad = 50.0, alpha = 360.0, beta = 90.0;

    char c;
    while ((c = getopt_long(argc, argv, "f:i:s:o:rth", long_options, NULL)) !=
           -1)
    {
        switch (c)
        {
        case 't':
            do_time = 1;
            break;
        case 'i':
            file_input_provided = 1;
            file_input = optarg;
            break;
        case 'h':
            do_help = 1;
            break;
        case 'o':
            file_output = optarg;
            break;
        case 'f':
            file_spawn = optarg;
            break;
        case 50:
            rad_root = std::stod(optarg);
            break;
        case 51:
            default_expl_rad = std::stod(optarg);
            break;
        case 52:
            alpha = std::stod(optarg);
            angle_provided = true;
            break;
        case 53:
            beta = std::stod(optarg);
            angle_provided = true;
            break;
        default:
            std::cerr << "Use '--help' or '-h' for usage " << std::endl;
            return 1;
        }
    }

    if (do_help)
    {
        std::cout
            << "Options:\n"
            << "[--filespawn, -f FILE]    Filename for spheres to spawn\n"
            << "                          (see format in documentation)\n"
            << "[--time, -t]              Show computing time (optional)\n"

            << "[--input, -i FILE]        Filename for input aggregate file "
               "(optional)\n"
            << "[--output, -o FILE]       Filename for log file (default : "
               "Aggregat.txt)\n"
            << "[--radroot RADIUS]        Radius of root sphere (optional)\n"
            << "[--explrad RADIUS]        Default exploration radius if not \n"
            << "                          provided in the input file\n"
            << '\n';
        return 0;
    }

    if (file_spawn.empty())
    {
        std::cerr << "You should provide spheres to spawn (-f option)" << std::endl;
        return -1;
    }

    Agg::Control::Controller controller({{0.0, 0.0, 0.0}, rad_root}, 500.0);

    if (file_input_provided)
    {
        Agg::File::input(controller, file_input);
    }

    const auto spheres_input = Agg::File::read(file_spawn);

    time_t clkBegin;
    if (do_time)
        clkBegin = clock();

    auto spawn_policy = [&controller, &angle_provided, &alpha, &beta](double rad) {
        using Sphere = Agg::Object::Sphere<double>;

        auto begin = controller.agg.objects.cbegin();
        auto end = controller.agg.objects.cend();
        const auto max_rad = std::max_element(begin, end,
                                              [](const Sphere &lhs, const Sphere &rhs) { return lhs.coord.Length() < rhs.coord.Length(); });

        const auto new_radius = max_rad->coord.Length() + rad + controller.agg.root.radius + 2 * controller.dt;
        if (angle_provided)
        {
            return Math::rand_point_sphere_angle({0.0, 0.0, 0.0}, new_radius, alpha, beta);
        }
        return Math::rand_point_sphere({0.0, 0.0, 0.0}, new_radius);
    };

    for (const auto &s : spheres_input)
    {
        for (unsigned int j = 0; j < std::get<0>(s); j++)
        {
            const auto curr_radius = std::get<1>(s);
            if (curr_radius > rad_root)
            {
                std::cerr << "An input sphere cannot have a higher radius than the root sphere : " << rad_root << '\n';
                return -1;
            }
            else if (std::get<2>(s) == 0.0)
            {
                controller.spawn(spawn_policy(curr_radius), curr_radius, default_expl_rad);
            }
            else
            {
                controller.spawn(spawn_policy(curr_radius), curr_radius, std::get<2>(s));
            }
        }
    }

    if (do_time)
    {
        time_t clkEnd = clock();
        double elapsed_secs = double(clkEnd - clkBegin) / CLOCKS_PER_SEC;
        std::cout << "Time: " << elapsed_secs << std::endl;
    }

    Agg::File::write(controller.agg, file_output);

    return 0;
}