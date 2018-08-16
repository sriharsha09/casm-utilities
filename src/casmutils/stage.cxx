#include "casmutils/structure.hpp"
#include <boost/filesystem.hpp>
#include <casm/CASM_global_definitions.hh>
#include <casm/app/AppIO.hh>
#include <casm/clusterography/Orbitree.hh>
#include <casm/clex/PrimClex.hh>
#include <casm/crystallography/UnitCellCoord.hh>
#include "casmutils/exceptions.hpp"

namespace Simplicity
{
void clust_convertor(const Rewrap::fs::path& prim_path, const Rewrap::fs::path& bspecs_path,
                     const Rewrap::fs::path& clust_path)
{
    CASM::jsonParser bspecs(bspecs_path);
    CASM::Structure prim(CASM::read_prim(prim_path));
    CASM::SiteOrbitree tree(prim.lattice(), CASM::TOL);
    tree = CASM::make_orbitree(prim, bspecs, CASM::TOL);

    int count = 0;
    CASM::jsonParser clust(clust_path);
    std::cout << std::setw(3) << "old"
              << " ----> "
              << std::setw(3) << "new" << "\n";
    for (auto branch_it = clust["branches"].begin(); branch_it != clust["branches"].end(); ++branch_it)
    {
        auto branch = *branch_it;
        for (auto orbit_it = branch["orbits"].begin(); orbit_it != branch["orbits"].end(); ++orbit_it)
        {
            auto orbit = *orbit_it;
            auto sites = orbit["prototype"]["sites"];
            CASM::SiteCluster test_clust(prim.lattice());
            for (int i = 0; i < sites.size(); i++)
            {
                CASM::UnitCellCoord ucc(sites[i][0].get<int>(), sites[i][1].get<int>(), sites[i][2].get<int>(),
                                        sites[i][3].get<int>());
                auto site = prim.get_site(ucc);
                test_clust.push_back(site);
            }
            auto index = tree.find(test_clust);
            std::cout << std::setw(3) << count
                      << " ----> "
                      << std::setw(3) << index << "\n";
            // if(count == 24 || count == 26)
            // {
            //     auto test_orbit = tree.orbit(tree.index_to_row[index],
            //                                  tree.index_to_column[index]);
            //     auto siteclust_index = test_orbit.find(test_clust, CASM::TOL);
            //     std::cout << "original cluster \n" << test_clust << "\n";
            //     std::cout << "mapped cluster \n" << test_orbit[siteclust_index] << "\n";
            // }
            count++;
        }
    }
}
} // namespace Simplicity
