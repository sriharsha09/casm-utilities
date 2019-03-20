#include "casmutils/definitions.hpp"
#include "casmutils/exceptions.hpp"
#include "casmutils/handlers.hpp"
#include "casmutils/stage.hpp"
#include "casmutils/structure.hpp"
#include <boost/program_options.hpp>
#include <casm/crystallography/Structure.hh>
#include <fstream>
#include <iostream>

namespace Utilities
{

void clusterconv_initializer(po::options_description& clusterconv_desc)
{
    UtilityProgramOptions::add_help_suboption(clusterconv_desc);
    UtilityProgramOptions::add_output_suboption(clusterconv_desc);

    clusterconv_desc.add_options()("prim,p", po::value<fs::path>()->required(), "Path to prim.json file.");
    clusterconv_desc.add_options()(
        "bspecs,b", po::value<fs::path>()->required(),
        "Path to bspecs.json file. The orbits are enumerated using the structure in the prim.json and specifications"
        " provided in bspecs");
    clusterconv_desc.add_options()(
        "clust,c", po::value<fs::path>()->required(),
        "Path to clust.json type file. It should have prototypes of the clusters being mapped."
        " Currently it takes legacy format of clust.json where clusters are ordered"
        " using branches --> orbits --> prototype format");
    return;
}
} // namespace Utilities

using namespace Utilities;

int main(int argc, char* argv[])
{
    Handler clusterconv_launch(argc, argv, clusterconv_initializer);

    if (clusterconv_launch.count("help"))
    {
        std::cout << clusterconv_launch.desc() << std::endl;
        return 1;
    }

    try
    {
        clusterconv_launch.notify();
    }

    catch (po::required_option& e)
    {
        std::cerr << e.what() << std::endl;
        return 2;
    }

    // get paths from input
    auto prim_path = clusterconv_launch.fetch<fs::path>("prim");
    auto bspecs_path = clusterconv_launch.fetch<fs::path>("bspecs");
    auto clust_path = clusterconv_launch.fetch<fs::path>("clust");

    // Read prim, make orbits from bspecs.
    auto prim = Simplicity::read_prim(prim_path);
    auto orbits = Simplicity::make_prim_periodic_orbits(prim, bspecs_path);
    // Read cluster from clust.json file
    auto integral_clusters = Legacy::get_integral_clusters_from_clust(prim, clust_path);

    // Make the cluster map std::vector<old_index, new_index>
    auto cluster_map = Simplicity::cluster_finder(integral_clusters, orbits);

    // Checks the output type and make a output stream
    // if (clusterconv_launch.vm().count("output"))
    // {
    //     output to file
    // }

    // else
    // {
    //     print to screen
    // }

    // output printing
    std::cout << std::setw(12) << "clust index"
              << " ----> " << std::setw(12) << "mapped index"
              << "\n";
    for (const auto& index_pair : cluster_map)
    {
        if (index_pair.second != -1)
        {
            std::cout << std::setw(4) << index_pair.first << " ---->" << std::setw(4) << index_pair.second << "\n";
        }
        else
        {
            std::cout << std::setw(4) << index_pair.first << " ---->" << std::setw(4) << "N/A"
                      << "\n";
        }
    }

    return 0;
}
