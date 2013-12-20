// Copyright 2010-2013 Google
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include <string>
#include <vector>

#include "base/commandlineflags.h"
#include "base/commandlineflags.h"
#include "base/integral_types.h"
#include "base/logging.h"
#include "base/strtoint.h"
#include "base/file.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/message.h"
#include "google/protobuf/text_format.h"
#include "base/strutil.h"
// TODO(user): Move sat_cnf_reader.h and sat_runner.cc to examples?
#include "cpp/opb_reader.h"
#include "cpp/sat_cnf_reader.h"
#include "sat/boolean_problem.h"
#include "sat/sat_solver.h"

DEFINE_string(
    input,
    "",
    "Required: input file of the problem to solve. Many format are supported:"
    ".cnf (sat, max-sat, weighted max-sat), .opb (pseudo-boolean sat/optim) "
    "and by default the LinearBooleanProblem proto (binary or text).");

DEFINE_string(
    output,
    "",
    "If non-empty, write the input problem as a LinearBooleanProblem proto to "
    "this file. By default it uses the binary format except if the file "
    "extension is '.txt'. If the problem is SAT, a satisfiable assignment is "
    "also writen to the file.");

DEFINE_string(
    expected_result,
    "undefined",
    "Checks the result against expected. Possible values are undefined, "
    "sat, unsat");

DEFINE_string(
    params,
    "",
    "Parameters for the sat solver in a text format of the "
    "SatParameters proto, example: --params=use_conflicts:true.");

DEFINE_string(
    lower_bound,
    "",
    "If not empty, look for a solution with an objective value >= this bound.");

DEFINE_string(
    upper_bound,
    "",
    "If not empty, look for a solution with an objective value <= this bound.");

DEFINE_bool(
    search_optimal,
    false,
    "If true, search for the optimal solution. "
    "The algorithm is currently really basic.");

// TODO(user): Adds minisat to the mix.

namespace operations_research {
namespace sat {
namespace {
// To benefit from the operations_research namespace, we put all the main() code
// here.
int Run() {
  if (FLAGS_input.empty()) {
    LOG(FATAL) << "Please supply a data file with --input=";
  }

  SatParameters parameters;
  if (!FLAGS_params.empty()) {
    CHECK(google::protobuf::TextFormat::ParseFromString(FLAGS_params, &parameters))
        << FLAGS_params;
  }

  // Initialize the solver.
  SatSolver solver;
  solver.SetParameters(parameters);

  // Read the problem.
  LinearBooleanProblem problem;
  if (HasSuffixString(FLAGS_input, ".opb") ||
      HasSuffixString(FLAGS_input, ".opb.bz2")) {
    OpbReader reader;
    if (!reader.Load(FLAGS_input, &problem)) {
      LOG(FATAL) << "Cannot load file '" << FLAGS_input << "'.";
    }
  } else if (HasSuffixString(FLAGS_input, ".cnf")
          || HasSuffixString(FLAGS_input, ".wcnf")) {
    SatCnfReader reader;
    if (!reader.Load(FLAGS_input, &problem)) {
      LOG(FATAL) << "Cannot load file '" << FLAGS_input << "'.";
    }
  } else {
    file::ReadFileToProtoOrDie(FLAGS_input, &problem);
  }

  // Load the problem into the solver.
  if (!LoadBooleanProblem(problem, &solver)) {
    LOG(FATAL) << "Couldn't load problem '" << FLAGS_input << "'.";
  }
  if (!AddObjectiveConstraint(
      problem,
      !FLAGS_lower_bound.empty(), atoi64(FLAGS_lower_bound),
      !FLAGS_upper_bound.empty(), atoi64(FLAGS_upper_bound),
      &solver)) {
    LOG(FATAL) << "Issue when setting the objective bounds.";
  }

  // Basic search for the optimal value by calling multiple times the solver.
  if (FLAGS_search_optimal
      && problem.type() == LinearBooleanProblem::MINIMIZATION) {
    Coefficient objective = std::numeric_limits<Coefficient>::max();
    while (solver.Solve() == SatSolver::MODEL_SAT) {
      CHECK(IsAssignmentValid(problem, solver.Assignment()));
      const Coefficient old_objective = objective;
      objective = ComputeObjectiveValue(problem, solver.Assignment());
      CHECK_LT(objective, old_objective);
      solver.Backtrack(0);
      if (!AddObjectiveConstraint(
          problem, false, 0, true, objective - 1, &solver)) {
        LOG(INFO) << "UNSAT (when tightenning the objective constraint).";
        break;
      }
    }
    LOG(INFO) << "Optimal found! " << objective;
    return EXIT_SUCCESS;
  }

  // Solve.
  const SatSolver::Status result = solver.Solve();
  if (result == SatSolver::MODEL_SAT) {
    CHECK(IsAssignmentValid(problem, solver.Assignment()));
  }

  if (!FLAGS_output.empty()) {
    if (result == SatSolver::MODEL_SAT) {
      StoreAssignment(
          solver.Assignment(), problem.mutable_assignment());
    }
    if (HasSuffixString(FLAGS_output, ".txt")) {
      file::WriteProtoToASCIIFileOrDie(problem, FLAGS_output);
    } else {
      file::WriteProtoToFileOrDie(problem, FLAGS_output);
    }
  }

  CHECK(FLAGS_expected_result == "undefined" ||
        (FLAGS_expected_result == "sat" && result == SatSolver::MODEL_SAT) ||
        (FLAGS_expected_result == "unsat" && result == SatSolver::MODEL_UNSAT));
  return EXIT_SUCCESS;
}
}  // namespace
}  // namespace sat
}  // namespace operations_research

static const char kUsage[] =
    "Usage: see flags.\n"
    "This program solves a given sat problem.";

int main(int argc, char **argv) {
  google::SetUsageMessage(kUsage);
  google::ParseCommandLineFlags(&argc, &argv, true);
  return operations_research::sat::Run();
}