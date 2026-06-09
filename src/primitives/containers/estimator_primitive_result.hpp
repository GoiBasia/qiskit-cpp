/*
# This code is part of Qiskit.
#
# (C) Copyright IBM 2017, 2026.
#
# This code is licensed under the Apache License, Version 2.0. You may
# obtain a copy of this license in the LICENSE.txt file in the root directory
# of this source tree or at http://www.apache.org/licenses/LICENSE-2.0.
#
# Any modifications or derivative works of this code must retain this
# copyright notice, and modified files need to carry a notice indicating
# that they have been altered from the originals.
*/

// estimator primitive result class

#ifndef __qiskitcpp_primitives_estimator_result_hpp__
#define __qiskitcpp_primitives_estimator_result_hpp__

#include <vector>

#include "primitives/containers/estimator_pub_result.hpp"

namespace Qiskit {
namespace primitives {

/// @class EstimatorPrimitiveResult
/// @brief A container for multiple estimator pub results and global metadata.
class EstimatorPrimitiveResult {
protected:
    std::vector<EstimatorPubResult> pub_results_;

public:
    /// @brief Create a new EstimatorPrimitiveResult.
    EstimatorPrimitiveResult() {}

    /// @brief allocate pub results.
    /// @param num_results number of pub results to be allocated.
    void allocate(uint_t num_results)
    {
        pub_results_.resize(num_results);
    }

    /// @brief Return the number of PUBs in this result.
    /// @return The number of PUBs.
    uint_t size(void) const
    {
        return pub_results_.size();
    }

    /// @brief Return the pub result.
    /// @param i index of pub.
    /// @return The pub result.
    EstimatorPubResult& operator[](uint_t i)
    {
        return pub_results_[i];
    }

    /// @brief Return the pub result.
    /// @param i index of pub.
    /// @return The pub result.
    const EstimatorPubResult& operator[](uint_t i) const
    {
        return pub_results_[i];
    }

    /// @brief set pubs in the results.
    /// @param pubs a list of pubs to be set.
    void set_pubs(const std::vector<EstimatorPub>& pubs)
    {
        if (pubs.size() == pub_results_.size()) {
            for (uint_t i = 0; i < pub_results_.size(); i++) {
                pub_results_[i].set_pub(pubs[i]);
            }
        }
    }
};

} // namespace primitives
} // namespace Qiskit

#endif //__qiskitcpp_primitives_estimator_result_hpp__
