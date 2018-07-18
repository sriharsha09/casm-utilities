#include <boost/program_options.hpp>
#include <casm/crystallography/Structure.hh>
#include <fstream>
#include <iostream>
#include "casmutils/definitions.hpp"
#include "casmutils/handlers.hpp"
#include "casmutils/stage.hpp"
#include "casmutils/structure.hpp"

namespace Utilities {

void inflate_initializer(po::options_description& inflate_desc) {
	UtilityProgramOptions::add_help_suboption(inflate_desc);
	UtilityProgramOptions::add_desc_suboption(inflate_desc);
	UtilityProgramOptions::add_output_suboption(inflate_desc);
	inflate_desc.add_options()("structure,s",
				      po::value<fs::path>()->required(),
				      "POS.vasp like file you want to "
				      "increase the boundaries of");
	inflate_desc.add_options()(
	    "length,l", po::value<std::vector<double>>()->multitoken()->required(),
	    "amount that each lattice vector will grow (three values "
	    "corresponding to a, b, and c)");
	return;
}
}

using namespace Utilities;

int main(int argc, char* argv[]) {
	Handler inflate_launch(argc, argv, inflate_initializer);

	if (inflate_launch.count("help")) {
		std::cout << inflate_launch.desc() << std::endl;
		return 1;
	}

	try {
		inflate_launch.notify();
	}

	catch (po::required_option& e) {
		std::cerr << e.what() << std::endl;
		return 2;
	}

	auto struc_path = inflate_launch.fetch<fs::path>("structure");
	auto struc = Rewrap::Structure(struc_path);
	auto out_struc = struc;
	auto lengths = inflate_launch.fetch<std::vector<double>>("length");
	out_struc=Frankenstein::inflate(struc,Eigen::Map<Eigen::Vector3d>(&lengths[0]));
	if (inflate_launch.vm().count("output")) {
		Simplicity::write_poscar(
		    out_struc, inflate_launch.fetch<fs::path>("output"));
		return 0;
	}
	Simplicity::print_poscar(out_struc, std::cout);
	return 0;
}
