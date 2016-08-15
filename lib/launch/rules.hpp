#ifndef CASM_UTILS_RULES
#define CASM_UTILS_RULES

#include <vector>
#include <string>
#include <utility>
#include <casm/CASM_global_definitions.hh>

namespace casmUtilities
{
    /**
     * Defines whether the amount of --suboptions given to a particular
     * utility was underspecified (requires --more input), overspecified
     * (--conflicting --options were given), correctly specified, or
     * unspecified (no rule given).

    enum class RuleStatus {UNDERSPECIFIED, OVERSPECIFIED, SPECIFIED, UNSPECIFIED};
     */

    /**
     * Defines what kind of a rule the --suboption pair defines:
     *  -If the first string is given the second must ALSO be given
     *  -If the first string is given the second must NOT be given
     *  -NO strings should be given
     *  -At least ONE string must be given
     */

    enum class RuleType {INCLUSIVE, EXCLUSIVE, SILENT, REQUIRED};

    /**
     * After you've parsed the command line and constructed a po::variables_map,
     * you need to ensure that conflicting arguments haven't been given. This
     * class allows you to specify which --suboptions conflict with others, and
     * which ones must be simultaneously specified. 
     */

    class LaunchRule
    {
        public:

            /// \brief Explicitly declare everything needed
            LaunchRule(const std::string &target, const std::string &requirement, RuleType specification);

            /// \brief Only allowed for SILENT and REQUIRED
            LaunchRule(RuleType restricted_specification);

            /// \brief access what kind of rule *this is
            RuleType type() const;

            /// \brief check to see if the given variables map breaks the rule (false->invalid, true->valid)
            bool parse(const CASM::po::variables_map &ref_vm) const;

        private:

            /// \brief Default constructor is private
            LaunchRule();

            /// \brief a pair of --suboptions, that are either required or exclude each other
            std::pair<std::string, std::string> m_requirement_pair;

            /// \brief defines the basic type of rule
            RuleType m_type;

            /// \brief parse variables map when *this is INCLUSIVE
            bool _inclusive_parse(const CASM::po::variables_map &ref_vm) const;

            /// \brief parse variables map when *this is EXCLUSIVE
            bool _exclusive_parse(const CASM::po::variables_map &ref_vm) const;

            /// \brief parse variables map when *this is SILENT
            bool _silent_parse(const CASM::po::variables_map &ref_vm) const;

            /// \brief parse variables map when *this is REQUIRED
            bool _required_parse(const CASM::po::variables_map &ref_vm) const;

    };

    /**
     * A collection of LaunchRules that can be parsed. After building up
     * an instance you can then check to see whether the variables map you
     * have satisfies all the requirements.
     */

    class LaunchRuleList
    {
        public:

            /// \brief specify single --suboption that cannot go with another
            void add_exclusion(const std::string &target, const std::string &exclude);

            /// \brief specify single --suboption that must go with another
            void add_inclusion(const std::string &target, const std::string &include);



            /// \brief given a collection of --suboptions, require that if one of them is given, all of them must be given
            void add_requirement(const std::vector<std::string> &codependent_group);

            /// \brief given a --suboption, require non of the other --suboptions in the other group are given
            void add_constraint(const std::string &independent, const std::vector<std::string> &exclusion_group);

            /// \brief Using the loaded rules, determine whether the given variables map is good to go
            bool parse(const CASM::po::variables_map &ref_vm) const;

        private:

            /// \brief List of every rule
            std::vector<LaunchRule> m_rule_table;
            
            /// \brief List of every rule broken since the last ::parse
            mutable std::vector<int> m_broken_rules;
    };
}


#endif