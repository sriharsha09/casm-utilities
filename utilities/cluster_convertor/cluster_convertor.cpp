#include "casmutils/definitions.hpp"
#include "casmutils/exceptions.hpp"
#include "casmutils/handlers.hpp"
#include "casmutils/structure.hpp"
#include "casmutils/stage.hpp"
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

    // clusterconv_desc.add_options()("structure,s", po::value<fs::path>()->required(),
    //                                "POS.vasp like file that you want to apply strain to.");
    // clusterconv_desc.add_options()("mode,m", po::value<std::string>()->default_value("GL"),
    //                                "Accepts strain convention as mode ('GL' [Green-Lagrange, default], 'EA' "
    //                                "[Euler-Almansi], 'B' [Biot], or 'H' [Hencky])."
    //                                " Also accepts 'F' [Deformation] as an argument to apply a deformation tensor");
    // clusterconv_desc.add_options()("tensor,t", po::value<fs::path>()->required(),
    //                                "Path to a file with strain tensor."
    //                                " Unrolled strain should be provided for GL, B, H, EA modes."
    //                                " Ordered as E(0,0) E(1,1) E(2,2) E(1,2) E(0,2) E(0,1)."
    //                                " Takes a 3X3 matrix for F (Deformation) mode.");
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


    CASM::fs::path prim_path("files/prim.json");
    CASM::fs::path bspecs_path("files/bspecs.json");
    CASM::fs::path clust_path("files/clust.json");
    Simplicity::clust_convertor(prim_path, bspecs_path, clust_path);

        
    // auto struc_path = clusterconv_launch.fetch<fs::path>("structure");
    // auto strain_path = clusterconv_launch.fetch<fs::path>("tensor");
    // auto mode = clusterconv_launch.fetch<std::string>("mode");
    // Rewrap::Structure strained_struc(struc_path);


    // checks the output type and writes the strained structure to a output stream
    // if (clusterconv_launch.vm().count("output"))
    // {
    //     auto out_path = clusterconv_launch.fetch<fs::path>("output");
    //     Simplicity::write_poscar(strained_struc, out_path);
    // }

    // else
    // {
    //     Simplicity::print_poscar(strained_struc, std::cout);
    // }

    return 0;
}
