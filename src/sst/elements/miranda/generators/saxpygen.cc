
#include <sst_config.h>
#include <sst/core/params.h>
#include <sst/elements/miranda/generators/saxpygen.h>

using namespace SST::Miranda;


SaxpyGenerator::SaxpyGenerator( ComponentId_t id, Params& params ) :
    RequestGenerator(id, params) {
        build(params);
    }

void SaxpyGenerator::build(Params& params) {
	const uint32_t verbose = params.find<uint32_t>("verbose", 0);

	out = new Output("SaxpyGenerator[@p:@l]: ", verbose, 0, Output::STDOUT);

	n = params.find<uint64_t>("n", 10000);
	dataSize = params.find<uint64_t>("datasize", 8);

	start_x = params.find<uint64_t>("start_x", 0);

	const uint64_t def_y = start_x + (n * dataSize);
	start_y = params.find<uint64_t>("start_y", def_y);

	const uint64_t def_z = start_y + (n * dataSize);
	start_z = params.find<uint64_t>("start_z", def_z);

	i = 0;

	out->verbose(CALL_INFO, 1, 0, "Array size is %" PRIu64 "\n", n);
	out->verbose(CALL_INFO, 1, 0, "data size       %" PRIu64 "\n", dataSize);
	out->verbose(CALL_INFO, 1, 0, "Start of array x @ 0x%" PRIx64 "\n", start_x);
	out->verbose(CALL_INFO, 1, 0, "Start of array y @ 0x%" PRIx64 "\n", start_y);
	out->verbose(CALL_INFO, 1, 0, "Start of array z @ 0x%" PRIx64 "\n", start_z);
	out->verbose(CALL_INFO, 1, 0, "Array Length:      %" PRIu64 " bytes\n", (n * dataSize));
	out->verbose(CALL_INFO, 1, 0, "Total arrays length:      %" PRIu64 " bytes\n", (3 * n * dataSize));
}

SaxpyGenerator::~SaxpyGenerator() {
	delete out;
}

void SaxpyGenerator::generate(MirandaRequestQueue<GeneratorRequest*>* q) {
	for(uint64_t j = 0; j < n; ++j) {
		out->verbose(CALL_INFO, 4, 0, "Array index: %" PRIu64 "\n", i);

        // z[j] = c * x[j] + y[j]
        MemoryOpRequest* read_x  = new MemoryOpRequest(start_x + (i * dataSize), dataSize, READ);
        MemoryOpRequest* read_y  = new MemoryOpRequest(start_y + (i * dataSize), dataSize, READ);
        MemoryOpRequest* write_z = new MemoryOpRequest(start_z + (i * dataSize), dataSize, WRITE);

		write_z->addDependency(read_x->getRequestID());
		write_z->addDependency(read_y->getRequestID());

		out->verbose(CALL_INFO, 8, 0, "READ req for addr %" PRIu64 "\n", (start_x + (i * dataSize)));
		q->push_back(read_x);

		out->verbose(CALL_INFO, 8, 0, "READ req for addr %" PRIu64 "\n", (start_y + (i * dataSize)));
		q->push_back(read_y);

		out->verbose(CALL_INFO, 8, 0, "WRITE req for addr %" PRIu64 "\n", (start_z + (i * dataSize)));
		q->push_back(write_z);

		i++;
	}
}

bool SaxpyGenerator::isFinished() {
	return (i == n);
}

void SaxpyGenerator::completed() {

}
