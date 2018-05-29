#pragma once
#include "Blob.h"


class BlobADV : public Blob {
public :
	BlobADV(std::string name, int nlvl);  //new constructor: use round number to determine lvl and capacities(normal Blob start at lvl1)
	~BlobADV();
};