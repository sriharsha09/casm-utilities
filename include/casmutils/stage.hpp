#include "casmutils/structure.hpp"
#include <boost/filesystem.hpp>
#include <casm/CASM_global_definitions.hh>

namespace Simplicity
{
    void clust_convertor(const CASM::fs::path &prim_path, const CASM::fs::path &bspecs_path);
    void clust_convertor(const CASM::fs::path &prim_path, const CASM::fs::path &bspecs_path, const CASM::fs::path &clust_path);
}
