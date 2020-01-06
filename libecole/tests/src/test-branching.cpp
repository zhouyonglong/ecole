#include <memory>
#include <stdexcept>

#include <catch2/catch.hpp>

#include "ecole/branching.hpp"
#include "ecole/exception.hpp"
#include "ecole/observation.hpp"

#include "conftest.hpp"

using namespace ecole;

scip::Model get_model() {
	auto model = scip::Model::from_file(problem_file);
	model.disable_cuts();
	model.disable_presolve();
	return model;
}

TEST_CASE("BranchEnv") {
	using BranchEnv = branching::Env<obs::BasicObs, std::size_t>;
	auto env = BranchEnv(
		std::make_unique<obs::BasicObsSpace>(), std::make_unique<branching::Fractional>());
	auto const model = get_model();

	SECTION("reset, reset, and delete") {
		env.reset(model);
		env.reset(model);
	}

	SECTION("reset, step, and delete") {
		env.reset(model);
		env.step(0);
	}

	SECTION("run full trajectory") {
		auto run_trajectory = [](auto& env, auto& model) {
			auto obs_done = env.reset(model);
			auto done = std::get<bool>(obs_done);
			auto count = 0;
			while (!done) {
				auto obs_rew_done_info = env.step(0);
				done = std::get<bool>(obs_rew_done_info);
				++count;
			}
			REQUIRE(count > 0);
		};
		run_trajectory(env, model);

		SECTION("Run another trajectory") { run_trajectory(env, model); }
	}

	SECTION("manage errors") {
		auto guard = ScipNoErrorGuard{};
		env.reset(model);
		REQUIRE_THROWS_AS(env.step(-1), scip::Exception);
	}
}