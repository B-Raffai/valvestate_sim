#include "PluginProcessor.h"
#include "PluginEditor.h"

ValvestateAudioProcessor::ValvestateAudioProcessor() : parameters(*this,
        nullptr, "PARAMETERS", 
        {
        std::make_unique<AudioParameterBool>  ("od", "OD1/OD2", false),
        std::make_unique<AudioParameterFloat> ("gain", "Gain", 0, 1, 0.5),
        std::make_unique<AudioParameterFloat> ("bass", "Bass", 0, 1, 0.5),
        std::make_unique<AudioParameterFloat> ("middle" , "Middle", 0, 1, 0.5),
        std::make_unique<AudioParameterFloat> ("treble", "Treble", 0, 1, 0.5),
        std::make_unique<AudioParameterFloat> ("presence", "Presence", 0, 1, 0.5),
        std::make_unique<AudioParameterFloat> ("volume", "Volume", 0, 1, 0.5)
        })
#ifndef JucePlugin_PreferredChannelConfigurations
     ,AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{

    od = parameters.getRawParameterValue("od");
    gain = parameters.getRawParameterValue("gain");
    bass = parameters.getRawParameterValue("bass");
    middle = parameters.getRawParameterValue("middle");
    treble = parameters.getRawParameterValue("treble");
    presence = parameters.getRawParameterValue("presence");
    volume = parameters.getRawParameterValue("volume");
}

ValvestateAudioProcessor::~ValvestateAudioProcessor()
{
}

//==============================================================================
const String ValvestateAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ValvestateAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ValvestateAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ValvestateAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ValvestateAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ValvestateAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ValvestateAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ValvestateAudioProcessor::setCurrentProgram (int index)
{
}

const String ValvestateAudioProcessor::getProgramName (int index)
{
    return {};
}

void ValvestateAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ValvestateAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 1;

    clipping.prepare(spec);
}

void ValvestateAudioProcessor::releaseResources()
{
    clipping.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ValvestateAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ValvestateAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;

    dsp::AudioBlock<float> block(buffer);

    clipping.process(block);
}

//==============================================================================
bool ValvestateAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ValvestateAudioProcessor::createEditor()
{
    //return new ValvestateAudioProcessorEditor (*this);
    return new GenericAudioProcessorEditor(this);
}

//==============================================================================
void ValvestateAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void ValvestateAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ValvestateAudioProcessor();
}
