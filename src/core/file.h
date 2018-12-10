#pragma once

#include <string>
#include <fstream>

#include "aggregate.h"
#include "control.h"

namespace Agg::File
{

template <typename T>
int write(const Aggregate<T> &agg, const std::string &fileName);

int input(Agg::Control::Controller &controller, const std::string &fileName);

std::vector<std::tuple<unsigned int, double, double>>
read(const std::string &fileName);

} // namespace Agg::File