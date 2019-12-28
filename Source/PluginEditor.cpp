/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ValvestateAudioProcessorEditor::ValvestateAudioProcessorEditor (ValvestateAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), 
    title("titleLabel", "HYBRID 8100"), 
    gainLabel("gainLabel", "GAIN"), 
    buttonLabel("OD1/OD2"),
    bassLabel("bassLabel", "BASS"), 
    middleLabel("middleLabel", "MIDDLE"), 
    trebleLabel("trebleLabel", "TREBLE"), 
    contourLabel("contourLabel", "CONTOUR"), 
    volumeLabel("volumeLabel", "VOLUME")
{
    setLookAndFeel(&vsLookAndFeel);

    applySliderStyle(gain);
    applySliderStyle(bass);
    applySliderStyle(middle);
    applySliderStyle(treble);
    applySliderStyle(contour);
    applySliderStyle(volume);

    applyLabelStyle(title);
    title.setFont(Font(30));
    applyLabelStyle(gainLabel);
    applyLabelStyle(buttonLabel);
    applyLabelStyle(bassLabel);
    applyLabelStyle(middleLabel);
    applyLabelStyle(trebleLabel);
    applyLabelStyle(contourLabel);
    applyLabelStyle(volumeLabel);

    gainAttachment.reset(new SliderAttachment(processor.parameters, "gain", gain));
    bassAttachment.reset(new SliderAttachment(processor.parameters, "bass", bass));
    middleAttachment.reset(new SliderAttachment(processor.parameters, "middle", middle));
    trebleAttachment.reset(new SliderAttachment(processor.parameters, "treble", treble));
    contourAttachment.reset(new SliderAttachment(processor.parameters, "contour", contour));
    volumeAttachment.reset(new SliderAttachment(processor.parameters, "volume", volume));

    buttonAttachment.reset(new ButtonAttachment(processor.parameters, "od", button));

    addAndMakeVisible(button);
    addAndMakeVisible(gain);
    addAndMakeVisible(bass);
    addAndMakeVisible(middle);
    addAndMakeVisible(treble);
    addAndMakeVisible(contour);
    addAndMakeVisible(volume);

    addAndMakeVisible(title);
    addAndMakeVisible(buttonLabel);
    addAndMakeVisible(gainLabel);
    addAndMakeVisible(gainLabel);
    addAndMakeVisible(bassLabel);
    addAndMakeVisible(middleLabel);
    addAndMakeVisible(trebleLabel);
    addAndMakeVisible(contourLabel);
    addAndMakeVisible(volumeLabel);

    setSize (700, 300);
}

void ValvestateAudioProcessorEditor::applyLabelStyle(Label &l)
{
    l.setJustificationType(Justification(Justification::centred));
    l.setFont(Font(20));
}

void ValvestateAudioProcessorEditor::applySliderStyle(Slider &s)
{
    Slider::RotaryParameters p;
    p.startAngleRadians = 2*3.1415/12*7;
    p.endAngleRadians = 2*3.1415/12*17;
    p.stopAtEnd = true;

    s.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    s.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    s.setPopupDisplayEnabled(true, true, nullptr);
    s.setLookAndFeel(&vsLookAndFeel);
    s.setRotaryParameters(p);
}

ValvestateAudioProcessorEditor::~ValvestateAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void ValvestateAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void ValvestateAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    Rectangle<int> area = getLocalBounds();

    title.setBounds(area.removeFromTop(100));

    auto knobArea = area.removeFromTop(150);
    button.setBounds(knobArea.removeFromLeft(100));
    gain.setBounds(knobArea.removeFromLeft(100));
    bass.setBounds(knobArea.removeFromLeft(100));
    middle.setBounds(knobArea.removeFromLeft(100));
    treble.setBounds(knobArea.removeFromLeft(100));
    contour.setBounds(knobArea.removeFromLeft(100));
    volume.setBounds(knobArea.removeFromLeft(100));

    buttonLabel.setBounds(area.removeFromLeft(100));
    gainLabel.setBounds(area.removeFromLeft(100));
    bassLabel.setBounds(area.removeFromLeft(100));
    middleLabel.setBounds(area.removeFromLeft(100));
    trebleLabel.setBounds(area.removeFromLeft(100));
    contourLabel.setBounds(area.removeFromLeft(100));
    volumeLabel.setBounds(area.removeFromLeft(100));
}
