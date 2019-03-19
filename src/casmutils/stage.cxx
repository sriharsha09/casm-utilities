#include "casmutils/stage.hpp"
#include "casmutils/exceptions.hpp"
#include "casmutils/structure.hpp"
#include <boost/filesystem.hpp>
#include <casm/CASM_global_definitions.hh>
#include <casm/app/AppIO.hh>
#include <casm/casm_io/Log.hh>
#include <casm/clusterography/ClusterOrbits.hh>
#include <casm/clusterography/ClusterOrbits_impl.hh>
#include <casm/clusterography/IntegralCluster.hh>
#include <casm/crystallography/UnitCellCoord.hh>

namespace Rewrap
{

IntegralCluster::IntegralCluster(const Rewrap::Structure& prim) : CASM::IntegralCluster(prim) {}
PrimPeriodicIntegralClusterOrbit::PrimPeriodicIntegralClusterOrbit(const CASM::PrimPeriodicIntegralClusterOrbit& orbit)
    : CASM::PrimPeriodicIntegralClusterOrbit(orbit)
{
}

} // namespace Rewrap

namespace Simplicity
{

// std::vector<Rewrap::PrimPeriodicIntegralClusterOrbit> make_prim_periodic_orbits(const Rewrap::Structure& prim,
//                                                                                 const Rewrap::fs::path& bspecs_path)
// {
//     CASM::jsonParser bspecs(bspecs_path);
//     CASM::Log& log = CASM::null_log();
//     std::vector<CASM::PrimPeriodicIntegralClusterOrbit> orbits;
//     CASM::make_prim_periodic_orbits(prim, bspecs, CASM::alloy_sites_filter, CASM::TOL, std::back_inserter(orbits), log);

//     std::vector<Rewrap::PrimPeriodicIntegralClusterOrbit> rewrap_orbits;
//     for (const auto orbit : orbits)
//     {
//         Rewrap::PrimPeriodicIntegralClusterOrbit rewrap_orbit(orbit);
//         rewrap_orbits.push_back(rewrap_orbit);
//     }
//     // std::cout << "Number of orbits enumerated :" << rewrap_orbits.size() << "\n";
//     return rewrap_orbits;
// }

Rewrap::Structure read_prim(const Rewrap::fs::path& path)
{
    CASM::Structure prim(CASM::read_prim(path, CASM::TOL));
    Rewrap::Structure rewrap_prim(prim);
    return rewrap_prim;
}

// std::vector<std::pair<int, int>> cluster_finder(std::vector<Rewrap::IntegralCluster>& clusters,
//                                                 std::vector<Rewrap::PrimPeriodicIntegralClusterOrbit>& orbits)
// {

//     std::pair<int, int> index_pair;
//     std::vector<std::pair<int, int>> cluster_map;
//     CASM::PrimPeriodicSymCompare<CASM::IntegralCluster> sym_compare(CASM::TOL);

//     for (const auto& test_clust : clusters)
//     {
//         int cluster_index = &test_clust - &clusters[0];
//         index_pair.first = cluster_index;
//         for (const auto& orbit : orbits)
//         {
//             int orbit_index = &orbit - &orbits[0];
//             if (orbit.contains(sym_compare.prepare(test_clust)))
//             {
//                 index_pair.second = orbit_index;
//                 break;
//             }
//             else if (orbits.size() - orbit_index == 1)
//             {
//                 index_pair.second = -1;
//             }
//         }
//         cluster_map.push_back(index_pair);
//     }
//     return cluster_map;
// }
} // namespace Simplicity

namespace Legacy
{

// std::vector<Rewrap::IntegralCluster> get_integral_clusters_from_clust(const Rewrap::Structure& prim,
//                                                                       const Rewrap::fs::path& clust_path)
// {
//     std::vector<Rewrap::IntegralCluster> integral_clusters;
//     CASM::jsonParser clust(clust_path);

//     for (const auto& branch : clust["branches"])
//     {
//         for (const auto& orbit : branch["orbits"])
//         {
//             auto sites = orbit["prototype"]["sites"];
//             Rewrap::IntegralCluster clust(prim);
//             for (int i = 0; i < sites.size(); i++)
//             {
//                 CASM::UnitCellCoord ucc(prim, sites[i][0].get<int>(), sites[i][1].get<int>(), sites[i][2].get<int>(),
//                                         sites[i][3].get<int>());
//                 clust.elements().push_back(ucc);
//             }
//             integral_clusters.push_back(clust);
//         }
//     }
//     return integral_clusters;
// }

} // namespace Legacy
