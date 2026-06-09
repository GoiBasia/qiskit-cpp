/*
# This code is part of Qiskit.
#
# (C) Copyright IBM 2026.
#
# This code is licensed under the Apache License, Version 2.0. You may
# obtain a copy of this license in the LICENSE.txt file in the root directory
# of this source tree or at http://www.apache.org/licenses/LICENSE-2.0.
#
# Any modifications or derivative works of this code must retain this
# copyright notice, and modified files need to carry a notice indicating
# that they have been altered from the originals.
*/

// Test program for estimator

#include <cstdint>
#include <cstdlib>
#include <complex>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "circuit/quantumcircuit.hpp"
#include "compiler/transpiler.hpp"
#include "primitives/backend_estimator_v2.hpp"
#include "quantum_info/sparse_observable.hpp"
#include "service/qiskit_runtime_service_qrmi.hpp"

using namespace Qiskit;
using namespace Qiskit::circuit;
using namespace Qiskit::compiler;
using namespace Qiskit::primitives;
using namespace Qiskit::quantum_info;
using namespace Qiskit::service;

using Estimator = BackendEstimatorV2;

int main()
{
    QuantumCircuit circ(2, 0);
    circ.h(0);
    circ.cx(0, 1);

    std::vector<std::pair<std::string, std::complex<double>>> terms;
    terms.push_back(std::make_pair(std::string("ZZ"), std::complex<double>(1.0, 0.0)));
    terms.push_back(std::make_pair(std::string("XX"), std::complex<double>(0.5, 0.0)));

    auto service = QiskitRuntimeService();
    auto backend = service.backend("ibm_kingston");
    auto estimator = Estimator(backend);
    auto transpiled_circ = transpile(circ, backend);
    auto observable = SparseObservable::from_list(terms);
    auto mapped_observable = observable.apply_layout(transpiled_circ.get_qubit_map());

    auto job = estimator.run({EstimatorPub(transpiled_circ, mapped_observable)}, 0.02);
    if (job == nullptr) {
        return -1;
    }

    auto result = job->result();
    auto evs = result[0].evs();
    auto stds = result[0].stds();

    std::cout << " ===== estimator result for pub[0] =====" << std::endl;
    for (uint_t i = 0; i < evs.size(); i++) {
        std::cout << "ev[" << i << "] = " << evs[i];
        if (i < stds.size()) {
            std::cout << ", std[" << i << "] = " << stds[i];
        }
        std::cout << std::endl;
    }

    return 0;
}
