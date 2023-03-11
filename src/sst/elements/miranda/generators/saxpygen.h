

#ifndef _H_SST_MIRANDA_SAXPY_GEN
#define _H_SST_MIRANDA_SAXPY_GEN

#include <sst/elements/miranda/mirandaGenerator.h>
#include <sst/core/output.h>

#include <queue>

namespace SST {
namespace Miranda {

class SaxpyGenerator : public RequestGenerator {

public:
	SaxpyGenerator( ComponentId_t id, Params& params );
        void build(Params& params);
	~SaxpyGenerator();
	void generate(MirandaRequestQueue<GeneratorRequest*>* q);
	bool isFinished();
	void completed();

	SST_ELI_REGISTER_SUBCOMPONENT_DERIVED(
                SaxpyGenerator,
                "miranda",
                "SaxpyGenerator",
                SST_ELI_ELEMENT_VERSION(1,0,0),
		        "Creates traffic using SAXPY algorithm",
                SST::Miranda::RequestGenerator
        )

	SST_ELI_DOCUMENT_PARAMS(
		    { "verbose",          "Sets the verbosity output of the generator", "0" },
    		{ "n",                "Sets the number of elements in the arrays", "10000" },
    		{ "datasize",         "Sets the data size", "8" },
    		{ "start_x",          "Sets the start address of the array x", "0" },
    		{ "start_y",          "Sets the start address of the array y", "1024" },
    		{ "start_z",          "Sets the start address of the array z", "2048" }
       	)

private:
	uint64_t dataSize;

	uint64_t start_x;
	uint64_t start_y;
	uint64_t start_z;

	uint64_t n;
	uint64_t i;

	Output*  out;

};

}
}

#endif
