#pragma once

#include <memory>
#include <string>

// Avoid including SCIP header
typedef struct Scip Scip;

namespace ecole {
namespace scip {

struct ScipDeleter {
	void operator()(Scip* scip);
};

std::unique_ptr<Scip, ScipDeleter> create();

class Model {
private:
	std::unique_ptr<Scip, ScipDeleter> scip;

public:
	Model();
	static Model from_file(const std::string& filename);

	void solve();
};

} // namespace scip
} // namespace ecole