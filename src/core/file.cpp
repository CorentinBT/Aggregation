#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <tuple>

#include "file.h"
#include "sphere.h"

namespace Agg::File
{

std::vector<std::tuple<unsigned int, double, double>>
read(const std::string &fileName)
{
    std::vector<std::tuple<unsigned int, double, double>> spheres_input{};
    std::ifstream myfile;
    myfile.open(fileName);
    if (!myfile.is_open())
    {
        std::cerr << "Cannot read spheres input in " << fileName << std::endl;
        exit(EXIT_FAILURE);
    }
    unsigned int number = 0;
    double radius = 0.0, expl_rad = 0.0;
    std::string input{};
    while (getline(myfile, input))
    {
        std::stringstream iss{input};
        iss >> number >> radius >> expl_rad;
        if (number == 0 || radius == 0.0)
        {
            myfile.close();
            std::cerr << "Bad input" << std::endl;
            exit(EXIT_FAILURE);
        }
        spheres_input.push_back(std::make_tuple(number, radius, expl_rad));
    }

    myfile.close();

    return spheres_input;
}

int input(Agg::Control::Controller &controller, const std::string &fileName)
{
    std::ifstream myFile;
    myFile.open(fileName);
    if (!myFile)
    {
        std::cerr << "Empty file !" << std::endl;
        exit(EXIT_FAILURE);
    }
    double file_x, file_y, file_z, file_rad, i;
    myFile >> i >> file_x >> file_y >> file_z >> file_rad;
    controller.agg.root = Agg::Object::Sphere<double>({file_x, file_y, file_z}, file_rad);
    while (myFile)
    {
        myFile >> i >> file_x >> file_y >> file_z >> file_rad;
        const Agg::Object::Sphere<double> new_sphere{{file_x, file_y, file_z}, file_rad};
        controller.putSphere(new_sphere);
    }
    myFile.close();
    return 0;
} // namespace Agg::File

template <>
int write(const Aggregate<Agg::Object::Sphere<double>> &agg, const std::string &fileName)
{
    std::ofstream myfile;
    myfile.open(fileName);
    if (!myfile.is_open())
    {
        std::cerr << "Cannot write the aggregate in " << fileName << std::endl;
        exit(EXIT_FAILURE);
    }

    int i = 0;
    for (const auto &s : agg.objects)
    {
        myfile << i << ' ' << s.coord[0] << ' ' << s.coord[1] << ' '
               << s.coord[2] << ' ' << s.radius << '\n';
        i += 1;
    }
    myfile.close();
    std::cout << "Log written in : " << fileName << std::endl;
    return 0;
}

} // namespace Agg::File