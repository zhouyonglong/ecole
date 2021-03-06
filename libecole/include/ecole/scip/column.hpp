#pragma once

#include <nonstd/optional.hpp>
#include <scip/scip.h>

#include "ecole/scip/type.hpp"
#include "ecole/scip/variable.hpp"
#include "ecole/scip/view.hpp"

namespace ecole {
namespace scip {

using nonstd::optional;

class ColProxy : public Proxy<SCIP_Col> {
public:
	using Proxy::Proxy;

	optional<real> ub() const noexcept;
	optional<real> lb() const noexcept;
	real reduced_cost() const noexcept;
	real obj() const noexcept;
	real prim_sol() const noexcept;
	real prim_sol_frac() const noexcept;
	bool is_prim_sol_at_lb() const noexcept;
	bool is_prim_sol_at_ub() const noexcept;
	base_stat basis_status() const noexcept;
	int age() const noexcept;

	VarProxy var() const noexcept;
};

using ColView = View<ColProxy>;

}  // namespace scip
}  // namespace ecole
