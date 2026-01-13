#include <juce_gui_extra/juce_gui_extra.h>
#include "TunerComponent.h"

class TunerApplication : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override { return "Rust Tuner"; }
    const juce::String getApplicationVersion() override { return "1.0.0"; }
    bool moreThanOneInstanceAllowed() override { return true; }

    void initialise(const juce::String &) override
    {
        mainWindow.reset(new MainWindow("Rust Tuner", new TunerComponent(), *this));
    }

    void shutdown() override
    {
        mainWindow = nullptr;
    }

    void systemRequestedQuit() override
    {
        quit();
    }

    class MainWindow : public juce::DocumentWindow
    {
    public:
        MainWindow(juce::String name, juce::Component *c, JUCEApplication &a)
            : DocumentWindow(name,
                             juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId),
                             DocumentWindow::allButtons),
              app(a)
        {
            setUsingNativeTitleBar(true);
            setContentOwned(c, true);
            centreWithSize(getWidth(), getHeight());
            setResizable(true, true);
            setVisible(true);
        }

        void closeButtonPressed() override { app.systemRequestedQuit(); }

    private:
        JUCEApplication &app;
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION(TunerApplication)
