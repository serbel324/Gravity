#include <rengine/driver/driver.h>
#include "main_frame.h"

int main() {
    REngine::Driver::Promote(std::make_unique<REngine::SingleFrameDriver>(
            std::make_unique<MainFrame>(),
            REngine::SingleFrameDriver::Settings{ .minimumUpdateDelayMs = 0 } ));
    REngine::Driver::King()->Initialize();
    REngine::Driver::King()->Run();
}
