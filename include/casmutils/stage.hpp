#include "casmutils/structure.hpp"
#include <boost/filesystem.hpp>
#include <casm/CASM_global_definitions.hh>
#include <casm/clusterography/ClusterOrbits.hh>
#include <casm/clusterography/ClusterOrbits_impl.hh>
#include <casm/clusterography/IntegralCluster.hh>
#include <casm/symmetry/OrbitDecl.hh>

namespace Rewrap
{

class IntegralCluster : public CASM::IntegralCluster
{
public:
    /// Construct from parent CASM class
    IntegralCluster(const Rewrap::Structure& prim);

private:
};

class PrimPeriodicIntegralClusterOrbit : public CASM::PrimPeriodicIntegralClusterOrbit
{
public:
    /// Construct from parent CASM class
    PrimPeriodicIntegralClusterOrbit(const CASM::PrimPeriodicIntegralClusterOrbit& orbit);

private:
};
} // namespace Rewrap

namespace Simplicity
{

/// Constructs a prim Structure from json file at prim_path.
Rewrap::Structure read_prim(const Rewrap::fs::path& path);

/// Enumerates all the PrimPeriodicOrbits with the specification provided in the json file at bspecs_path.
std::vector<Rewrap::PrimPeriodicIntegralClusterOrbit> make_prim_periodic_orbits(const Rewrap::Structure& prim,
                                                                                const Rewrap::fs::path& bspecs_path);

/// Finds the index of the orbits that have the enumerated integral clusters.
std::vector<std::pair<int, int>> cluster_finder(std::vector<Rewrap::IntegralCluster>& integral_clusters,
                                                std::vector<Rewrap::PrimPeriodicIntegralClusterOrbit>& orbits);

} // namespace Simplicity

namespace Legacy
{

/// Goes through different branches and orbits provided in clust.json type file at clust_path and gathers prototypes.
/// Makes a IntegralCluster using each prototype.
std::vector<Rewrap::IntegralCluster> get_integral_clusters_from_clust(const Rewrap::Structure& prim,
                                                                      const Rewrap::fs::path& clust_path);
} // namespace Legacy
