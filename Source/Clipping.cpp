#include "Clipping.h"
#define OVERSAMPLING_ORDER 3

Clipping::Clipping() : oversampling(1, OVERSAMPLING_ORDER,
        dsp::Oversampling<float>::filterHalfBandPolyphaseIIR)
{
    waveshaper.functionToUse = waveshape;
}

Clipping::~Clipping() {}

void Clipping::process(dsp::AudioBlock<float> block)
{
    auto oversampledBlock = oversampling.processSamplesUp(block);

    dsp::ProcessContextReplacing<float> ctx(oversampledBlock);
    waveshaper.process(ctx);

    oversampling.processSamplesDown(block);
}
void Clipping::prepare(dsp::ProcessSpec spec)
{
    oversampling.initProcessing(spec.maximumBlockSize);
}

void Clipping::reset()
{
    oversampling.reset();
}
